//
// Created by Peter A. Kolski on 24.10.16.
//

#include "Ribbon.h"

namespace bildpeter {

    void
    Ribbon::update( bildpeter::MidiValues midiValues, string sizeTxt, string fadeTxt, double x, double y, double z ) {
        ofVec3f nullVec;
        ofVec3f posLeft, posRight;

        ribbonRadius = midiValues.getValue( sizeTxt ) * ribbonRadiusMax;
        auto fade = ofMap( midiValues.getValue( fadeTxt ), 0.2, 1.0, 0.0, 255.0, true );
//    fade += 50.0;// add value, so I can fade out

        ribbonColor = ofColor( fade, fade, fade, 255 );

        posLeft.x = ( x - 0.5 ) * ribbonRadius;
        posLeft.y = ( y - 0.5 ) * ribbonRadius;
        posLeft.z = ( z - 0.5 ) * ribbonRadius;

        posRight.x = ( (1 - x) - 0.5 ) * ribbonRadius;
        posRight.y = ( y - 0.5 ) * ribbonRadius;
        posRight.z = ( z - 0.5 ) * ribbonRadius;

        if ( posLeft.length( ) != 0 ) {
            ribbonLeft->update( posLeft, ribbonColor );
        }

        if ( posRight.length( ) != 0 ) {
            ribbonRight->update( posRight, ribbonColor );
        }
    }

    void Ribbon::draw( bildpeter::MidiValues &midiValues, string nameDev ) {
        if ( midiValues.getValue( nameDev ) ) {
            ofPushStyle( );
            ofSetColor( 255 );

            ofPushMatrix( );
            {
                ofTranslate( ofGetWidth( ) * 1 / 3, ofGetHeight( ) / 2 );
                ofRotate( -ofGetElapsedTimef( ) * 10, 0, 1, 0 );
                ribbonLeft->draw( );
            }
            ofPopMatrix( );
            ofPushMatrix( );
            {
                ofTranslate( ofGetWidth( ) * 2 / 3, ofGetHeight( ) / 2 );
                ofRotate( ofGetElapsedTimef( ) * 10, 0, 1, 0 );
                ribbonRight->draw( );
            }
            ofPopMatrix( );

            ofPopStyle( );
        }
    }

    Ribbon::Ribbon( int ribbonLength, const ofColor &ribbonColor, float ribbonThickness ) :
            ribbonLength( ribbonLength ),
            ribbonColor( ribbonColor ),
            ribbonThickness( ribbonThickness )
    {
        ribbonLeft  = new ofxTwistedRibbon( ribbonLength, ribbonColor, ribbonThickness );
        ribbonRight = new ofxTwistedRibbon( ribbonLength, ribbonColor, ribbonThickness );
    }

    Ribbon::Ribbon()
    {
        ribbonLeft  = new ofxTwistedRibbon( ribbonLength, ribbonColor, ribbonThickness );
        ribbonRight = new ofxTwistedRibbon( ribbonLength, ribbonColor, ribbonThickness );
    }

}