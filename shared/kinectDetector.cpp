//
//  kinectDetector.cpp
//  Detector
//
//  Created by Peter A. Kolski on 08.03.16.
//
//

#include "kinectDetector.hpp"

namespace bildpeter {

    KinectDetector::KinectDetector()
    {
//        sensorKinect_.setRegistration(true);	// enable depth->video image calibration
        sensorKinect_.init(false, false); // disable video image (faster fps)
        sensorKinect_.open();
        sensorKinect_.update();
        ofLogNotice() << "Kinect Width: "<< sensorKinect_.getWidth() << " Height: " << sensorKinect_.getHeight();

        numPixels_      = sensorKinect_.getWidth() * sensorKinect_.getHeight();
        
        colorImg.allocate( sensorKinect_.width, sensorKinect_.height);
        grayImage.allocate( sensorKinect_.width, sensorKinect_.height);
        grayThreshNear.allocate( sensorKinect_.width, sensorKinect_.height);
        grayThreshFar.allocate( sensorKinect_.width, sensorKinect_.height);
        nearThreshold   = 230;
        farThreshold    = 70;
    }
    
    // ------------------------------------------------------------------------------------------
    
    void    KinectDetector::update()
    {
        sensorKinect_.update();
        distanceArrayPtr_  = sensorKinect_.getDistancePixels();
        
        calcualteClosestDistance();
        applyNearFarSubtraction();
        applyBlobDetection();   // Should be applied after subtraction
        calculateNonBlackPixels();
    }
    
    // ------------------------------------------------------------------------------------------
    

    void    KinectDetector::setPixelRestrictionLeftRight( int maxPixel )
    {
        maxPixelX_ = maxPixel;
    }

    void    KinectDetector::setPixelRestrictionTopBottom( int maxPixel )
    {
        maxPixelY_ = maxPixel;
    }
    // ------------------------------------------------------------------------------------------
    
    
    // ------------------------------------------------------------------------------------------
    // --------------------------------------- PRIVATE ------------------------------------------
    // ------------------------------------------------------------------------------------------
    
    void    KinectDetector::calcualteClosestDistance()
    {
        nearestDistance_ = 10000000000;
        int     TopBottomIgnore  = sensorKinect_.getWidth() * maxPixelY_;
        
        for ( int i = TopBottomIgnore; i < numPixels_ - TopBottomIgnore; i++ )
        {
            if (   ( (i % (int)sensorKinect_.getWidth() ) > maxPixelX_ )
                 &&( (i % (int)sensorKinect_.getWidth()) < sensorKinect_.getWidth() - maxPixelX_ ) )
            {
                if ( distanceArrayPtr_[ i ] > 100 )
                {
                    nearestDistance_ = ( distanceArrayPtr_[i] < nearestDistance_ ) ? distanceArrayPtr_[i] : nearestDistance_;
                }
            
            }
        }
    }

    // ------------------------------------------------------------------------------------------
    
    void    KinectDetector::calculateNonBlackPixels()
    {
        auto pixels = grayImage.getPixels();
        numPixelsNotBlack_ = 0;
        
        for ( int i = 0; i < numPixels_; ++i )
        {
            if ( pixels[ i ] != 0 )
            {
                ++numPixelsNotBlack_;
            }
        }
    }
    
    // ------------------------------------------------------------------------------------------
    
    void    KinectDetector::applyBlobDetection()
    {
        grayImage.setFromPixels( sensorKinect_.getDepthPixels() );
        contourFinder.findContours(grayImage, 10, ( sensorKinect_.width * sensorKinect_.height)/2, 20, false);
        
        if ( contourFinder.blobs.size() )
        {
            blobLargest = contourFinder.blobs[ 1 ];
        }
        
        // --- find largest blob
        for ( auto &blobCurrent : contourFinder.blobs )
        {
            blobLargest = blobLargest.area > blobCurrent.area ? blobLargest : blobCurrent;
        }
    }
    
    // ------------------------------------------------------------------------------------------
    
    void    KinectDetector::applyNearFarSubtraction()
    {
        grayThreshNear = grayImage;
        grayThreshFar = grayImage;
        grayThreshNear.threshold( nearThreshold, true);
        grayThreshFar.threshold( farThreshold);
        cvAnd(grayThreshNear.getCvImage(), grayThreshFar.getCvImage(), grayImage.getCvImage(), NULL);
    }
    
}   // --- namespace bildpeter
