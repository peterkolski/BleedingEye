//
// Created by Peter A. Kolski on 24.10.16.
//

#include "ofApp.h"
#include "Ribbon.h"

void Ribbon::ribbonUpdate()
{
    ofVec3f nullVec;
    ofVec3f posLeft, posRight;

    ribbonRadius    = ofApp::midiUC.getValue( "ribbonSize") * ribbonRadiusMax;
    auto    fade    = ofMap( ofApp::midiUC.getValue( "ribbonFade" ), 0.2, 1.0, 0.0, 255.0, true );
//    fade += 50.0;// add value, so I can fade out

    ribbonColor = ofColor( fade, fade, fade, 255 );

    posLeft.x = ( ofApp::ribbonLeftX - 0.5) * ribbonRadius;
    posLeft.y = ( ofApp::ribbonLeftY - 0.5) * ribbonRadius;
    posLeft.z = ( ofApp::ribbonLeftZ - 0.5) * ribbonRadius;

    posRight.x = ( ofApp::ribbonRightX - 0.5) * ribbonRadius;
    posRight.y = ( ofApp::ribbonRightY - 0.5) * ribbonRadius;
    posRight.z = ( ofApp::ribbonRightZ - 0.5) * ribbonRadius;

    if ( posLeft.length() != 0 ) {
        ribbonLeft->update( posLeft, ribbonColor );
    }

    if ( posRight.length() != 0 ) {
        ribbonRight->update( posRight, ribbonColor );
    }
}

void Ribbon::ribbonDraw( bildpeter::MidiValues &midiValues, string nameDev )
{
    if ( midiValues.getValue( nameDev ) )
    {
        ofPushStyle();
        ofSetColor( 255 );

        ofPushMatrix();
        {
            ofTranslate( ofGetWidth() * 1/3, ofGetHeight() / 2 );
            ofRotate( -ofGetElapsedTimef() * 10, 0, 1, 0 );
            ribbonLeft->draw();
        }
        ofPopMatrix();
        ofPushMatrix();
        {
            ofTranslate( ofGetWidth() * 2/3, ofGetHeight() / 2 );
            ofRotate( ofGetElapsedTimef() * 10, 0, 1, 0 );
            ribbonRight->draw();
        }
        ofPopMatrix();

        ofPopStyle();
    }
}