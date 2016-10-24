//
// Created by Peter A. Kolski on 24.10.16.
//

#include "ofApp.h"
#include "Flow.h"

namespace bildpeter
{
    void Flow::flowSetup( ofColor color ) {
        drawWidth = ofGetWidth( );
        drawHeight = ofGetHeight( );
        flowWidth = drawWidth / 4;
        flowHeight = drawHeight / 4;

        fluidSimulation.setup( flowWidth, flowHeight, drawWidth, drawHeight );

        flowPoints = vector< FlowPoint >( 3 );
        for ( auto &_point : flowPoints ) {
            _point.setup( flowWidth, flowHeight );
        }

        flowPoints[ 0 ].setColor( color );
        flowPoints[ 1 ].setColor( color );
        flowPoints[ 2 ].setColor( color );
    }

    void Flow::flowUpdate( float fadeFlow, float strengthFlow, float a, float s, float b, float strengthSensor ) {
        flowSensorA = ( 1 - a ) * strengthSensor;
        flowSensorB = ( 1 - s ) * strengthSensor;
        flowSensorC = ( 1 - b ) * strengthSensor;


        if ( fadeFlow ) {
            auto strength = strengthFlow / 10.0;
            auto radius = 3.0;

            int i = 1;

            for ( auto &_point : flowPoints ) {

                posCurrent = ofVec2f( ofNoise( ofGetElapsedTimef( ) / 10.0, i++ ),
                                      ofNoise( ofGetElapsedTimef( ) / 10.0 + 1000, i ) );
                posDelta = ofVec2f( posPrevious.x - posCurrent.x, posPrevious.y - posCurrent.y );
                posPrevious = posCurrent;
                _point.applyForce( ofVec2f( ( float ) ( i - 1 ) / 4.0, 0.8 ) );
                _point.setStrength( strength );
                _point.setDirection( ofVec2f( 0.0, -1.0 ) * strength / 20.0 );
                _point.update( );

                fluidSimulation.addVelocity( _point.getVelocityTexture( ) );
                fluidSimulation.addDensity( _point.getDensityTexture( ) );
            }

            flowPoints[ 0 ].setRadius( ofClamp( strengthFlow - flowSensorA, 0.0, 1.0 ) * radius );
            flowPoints[ 1 ].setRadius( ofClamp( strengthFlow - flowSensorB, 0.0, 1.0 ) * radius );
            flowPoints[ 2 ].setRadius( ofClamp( strengthFlow - flowSensorC, 0.0, 1.0 ) * radius );

            fluidSimulation.update( );
        }
//    else
//        fluidSimulation.resetBackground();

    }

    void Flow::flowDraw( float fadeFlow ) {
        if ( fadeFlow ) {
            ofPushStyle( );
            {
                ofEnableBlendMode( OF_BLENDMODE_ADD );
                ofSetColor( 255, 255, 255, 255 * fadeFlow );
                fluidSimulation.draw( 0, 0, ofGetWidth( ), ofGetHeight( ) );
            }
            ofPopStyle( );
        }
    }

}