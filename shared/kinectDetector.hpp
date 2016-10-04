//
//  kinectDetector.hpp
//  Detector
//
//  Created by Peter A. Kolski on 08.03.16.
//
//

#ifndef kinectDetector_hpp
#define kinectDetector_hpp

#include "ofxKinect.h"
#include "ofxOpenCv.h"
#include "ofMain.h"
#include <iostream>

namespace bildpeter {

    class   KinectDetector
    {
    public:
        KinectDetector();
        void        update();
        
        void        setPixelRestrictionLeftRight( int maxPixel );
        void        setPixelRestrictionTopBottom( int maxPixel );
        void        drawSubtacted( float x, float y, float w, float h  ) { grayImage.draw( x, y, w, h ); }
        
        int         getPixelsAmount()       { return numPixels_; }
        int         getPixelsNotWhite()     { return numPixelsNotBlack_; }
        int         getPixelMaxLeftRight()  { return maxPixelX_; }
        int         getPixelMaxTopBottom()  { return maxPixelY_; }
        float       getNearestDistanceCM()  { return nearestDistance_; }
        float       getLargestBlobArea()    { return blobLargest.area; }
        
        ofxKinect           sensorKinect_;
        ofxCvContourFinder  contourFinder;
        ofxCvBlob           blobLargest;
        
    private:
        void        calcualteClosestDistance();
        void        calculateNonBlackPixels();
        void        applyBlobDetection();
        void        applyNearFarSubtraction();
        
        int         maxPixelX_, maxPixelY_;
        float      *distanceArrayPtr_;
        float       nearestDistance_;
        int         numPixels_;
        int         numPixelsNotBlack_;
        
        // --- OpenCV

        ofxCvColorImage     colorImg;
        ofxCvGrayscaleImage grayImage; // grayscale depth image
        ofxCvGrayscaleImage grayThreshNear; // the near thresholded image
        ofxCvGrayscaleImage grayThreshFar; // the far thresholded image
        int nearThreshold;
        int farThreshold;

    };
    
} // --- namespace bildpeter

#endif /* kinectDetector_hpp */


/*
 
 Acceleration
 if(kinect.hasAccelControl()) {
 reportStream << "accel is: " << ofToString(kinect.getMksAccel().x, 2) << " / "
 << ofToString(kinect.getMksAccel().y, 2) << " / "
 << ofToString(kinect.getMksAccel().z, 2) << endl;
 }

 
 */