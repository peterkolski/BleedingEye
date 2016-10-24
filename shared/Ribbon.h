//
// Created by Peter A. Kolski on 24.10.16.
//

#ifndef BLEEDINGEYE_RIBBON_H
#define BLEEDINGEYE_RIBBON_H

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxTwistedRibbon.h"
#include "MidiValues.hpp"


class Ribbon {

public:

    void    ribbonUpdate();
    void    ribbonDraw( bildpeter::MidiValues &midiValues, string nameDev );

    ofxTwistedRibbon        *ribbonLeft, *ribbonRight;
    int                     ribbonLength    = 200;
    ofColor                 ribbonColor     = ofColor::black;
    float                   ribbonThickness = 10.0;
    float                   ribbonRadius    = 600;
    float                   ribbonRadiusMax = 1000;


};


#endif //BLEEDINGEYE_RIBBON_H
