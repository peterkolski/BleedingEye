//
// Created by Peter A. Kolski on 24.10.16.
//

#include "Flow.h"

namespace bildpeter
{
    void Flow::setup( ofColor color ) {
        drawWidth_ = ofGetWidth( );
        drawHeight_ = ofGetHeight( );
        flowWidth_ = drawWidth_ / 4;
        flowHeight_ = drawHeight_ / 4;

        fluidSimulation_.setup( flowWidth_, flowHeight_, drawWidth_, drawHeight_ );

        flowPoints_ = vector< FlowPoint >( 3 );
        for ( auto &_point : flowPoints_ ) {
            _point.setup( flowWidth_, flowHeight_ );
        }

        flowPoints_[ 0 ].setColor( color );
        flowPoints_[ 1 ].setColor( color );
        flowPoints_[ 2 ].setColor( color );
    }

    void Flow::update( float fadeFlow, float strengthFlow, float a, float s, float b, float strengthSensor ) {
        flowSensorA_ = ( 1 - a ) * strengthSensor;
        flowSensorB_ = ( 1 - s ) * strengthSensor;
        flowSensorC_ = ( 1 - b ) * strengthSensor;


        if ( fadeFlow ) {
            auto strength = strengthFlow / 10.0;
            auto radius = 3.0;

            int i = 1;

            for ( auto &_point : flowPoints_ ) {

                posCurrent_ = ofVec2f( ofNoise( ofGetElapsedTimef( ) / 10.0, i++ ),
                                      ofNoise( ofGetElapsedTimef( ) / 10.0 + 1000, i ) );
                ofVec2f( posPrevious_.x - posCurrent_.x, posPrevious_.y - posCurrent_.y );
                posPrevious_ = posCurrent_;
                _point.applyForce( ofVec2f( ( float ) ( i - 1 ) / 4.0, 0.8 ) );
                _point.setStrength( strength );
                _point.setDirection( ofVec2f( 0.0, -1.0 ) * strength / 20.0 );
                _point.update( );

                fluidSimulation_.addVelocity( _point.getVelocityTexture( ) );
                fluidSimulation_.addDensity( _point.getDensityTexture( ) );
            }

            flowPoints_[ 0 ].setRadius( ofClamp( strengthFlow - flowSensorA_, 0.0, 1.0 ) * radius );
            flowPoints_[ 1 ].setRadius( ofClamp( strengthFlow - flowSensorB_, 0.0, 1.0 ) * radius );
            flowPoints_[ 2 ].setRadius( ofClamp( strengthFlow - flowSensorC_, 0.0, 1.0 ) * radius );

            fluidSimulation_.update( );
        }
//    else
//        fluidSimulation.resetBackground();

    }

    void Flow::draw( float fadeFlow ) {
        if ( fadeFlow ) {
            ofPushStyle( );
            {
                ofEnableBlendMode( OF_BLENDMODE_ADD );
                ofSetColor( 255, 255, 255, 255 * fadeFlow );
                fluidSimulation_.draw( 0, 0, ofGetWidth( ), ofGetHeight( ) );
            }
            ofPopStyle( );
        }
    }

}