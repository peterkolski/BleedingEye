//
//  LinesHorizontal.cpp
//  LacunaDance
//
//  Created by Peter A. Kolski on 18.04.16.
//
//

#include "LinesHorizontal.hpp"


namespace bildpeter {
    
    void LinesHorizontal::setup( int numLines, int speedMax, float thicknessMax, float yMin, float yMax )
    {
        if ( numLines > 1 ) {
            linesUp_    = vector< Line >( numLines / 2 );
            linesDown_  = vector< Line >( numLines / 2 );
        }
        else
        {
            linesUp_    = vector< Line >( 1 );
            linesDown_  = vector< Line >( 1 );
            ofLogWarning() << "Minimum of lines is 2. Two lines created";
        }
        
        setBounds( yMin, yMax );
        
        for ( auto &line : linesUp_ )
        {
            line.setUpMovement();
            line.speedBase_ = ofRandom( speedMax );
            line.yPos_      = ofRandom( yMin, yMax );
            line.thickness_ = ofRandom( thicknessMax );
        }

        for ( auto &line : linesDown_ )
        {
            line.setDownMovement();
            line.speedBase_ = ofRandom( speedMax );
            line.yPos_      = ofRandom( yMin, yMax );
            line.thickness_ = ofRandom( thicknessMax );
        }
    }
    
    void LinesHorizontal::update()
    {
        for ( auto &line : linesUp_ )
        {
            line.yPos_ -= line.speedBase_ * speedFactor_ * line.direction_;
            if ( line.yPos_ <= yBoundMin_ ) {
                line.yPos_ = yBoundMax_;
            }
        }
        
        for ( auto &line : linesDown_ )
        {
            line.yPos_ -= line.speedBase_ * speedFactor_ * line.direction_;
            if ( line.yPos_ >= yBoundMax_ ) {
                line.yPos_ = yBoundMin_;
            }
        }
    }
    
    void LinesHorizontal::draw()
    {
        ofPushStyle();
        ofPushMatrix();
        {
            ofSetColor( color_ );
            for( auto line : linesUp_ )
            {
                ofSetLineWidth( line.thickness_ );
                ofDrawLine( 0.0, line.yPos_, ofGetWidth(), line.yPos_ );
            }

            for( auto line : linesDown_ )
            {
                ofSetLineWidth( line.thickness_ );
                ofDrawLine( 0.0, line.yPos_, ofGetWidth(), line.yPos_ );
            }
        }
        ofPopMatrix();
        ofPopStyle();
    }
    
}