//
// Created by Peter A. Kolski on 24.10.16.
//

#include "Ribbon.h"

namespace bildpeter {

    void
    Ribbon::update( bildpeter::MidiValues midiValues, string sizeTxt, string fadeTxt, double x, double y, double z )
    {
        ofVec3f nullVec;
        ofVec3f posLeft, posRight;

        ribbonRadius_ = midiValues.getValue( sizeTxt ) * ribbonRadiusMax_;
        auto fade = ofMap( midiValues.getValue( fadeTxt ), 0.2, 1.0, 0.0, 255.0, true );
//    fade += 50.0;// add value, so I can fade out

        ribbonColor_ = ofColor( fade, fade, fade, 255 );

        setPostion( x, y, z, posLeft, posRight );

        if ( posLeft.length( ) != 0 ) {
            ribbonLeft_->update( posLeft, ribbonColor_ );
        }

        if ( posRight.length( ) != 0 ) {
            ribbonRight_->update( posRight, ribbonColor_ );
        }
    }

    void Ribbon::setPostion( double x, double y, double z, ofVec3f &posLeft, ofVec3f &posRight ) const
    {
        posLeft.x = ( x - 0.5 ) * ribbonRadius_;
        posLeft.y = ( y - 0.5 ) * ribbonRadius_;
        posLeft.z = ( z - 0.5 ) * ribbonRadius_;

        posRight.x = ( (1 - x) - 0.5 ) * ribbonRadius_;
        posRight.y = ( y - 0.5 ) * ribbonRadius_;
        posRight.z = ( z - 0.5 ) * ribbonRadius_;
    }

    void Ribbon::draw( bildpeter::MidiValues &midiValues, string nameDev, float fade )
    {
        if ( fade )
        {
            ofPushStyle( );
            ofSetColor( 255 );

            ofPushMatrix( );
            {
                ofTranslate( ofGetWidth( ) * 1 / 3, ofGetHeight( ) / 2 );
                ofRotate( -ofGetElapsedTimef( ) * 10, 0, 1, 0 );
                ribbonLeft_->draw( );
            }
            ofPopMatrix( );

            ofPushMatrix( );
            {
                ofTranslate( ofGetWidth( ) * 2 / 3, ofGetHeight( ) / 2 );
                ofRotate( ofGetElapsedTimef( ) * 10, 0, 1, 0 );
                ribbonRight_->draw( );
            }
            ofPopMatrix( );

            ofPopStyle( );
        }
    }

    Ribbon::Ribbon( int ribbonLength, const ofColor &ribbonColor, float ribbonThickness ) :
            ribbonLength_( ribbonLength ),
            ribbonColor_( ribbonColor ),
            ribbonThickness_( ribbonThickness )
    {
        ribbonLeft_  = new ofxTwistedRibbon( ribbonLength, ribbonColor, ribbonThickness );
        ribbonRight_ = new ofxTwistedRibbon( ribbonLength, ribbonColor, ribbonThickness );
    }

    Ribbon::Ribbon()
    {
        ribbonLeft_  = new ofxTwistedRibbon( ribbonLength_, ribbonColor_, ribbonThickness_ );
        ribbonRight_ = new ofxTwistedRibbon( ribbonLength_, ribbonColor_, ribbonThickness_ );
    }

}