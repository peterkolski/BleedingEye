//
// Created by Peter A. Kolski on 24.10.16.
//

#ifndef BLEEDINGEYE_RIBBON_H
#define BLEEDINGEYE_RIBBON_H

#include "ofMain.h"
#include "ofxMidi.h"
#include "ofxTwistedRibbon.h"
#include "MidiValues.hpp"

namespace bildpeter
{
class Ribbon
{

public:
    Ribbon();

    Ribbon( int ribbonLength, const ofColor &ribbonColor, float ribbonThickness );

    // TODO extract Midi
    void update( bildpeter::MidiValues midiValues, string sizeTxt, string fadeTxt, double x, double y, double z );
    void    draw( bildpeter::MidiValues &midiValues, string nameDev );

private:
    ofxTwistedRibbon        *ribbonLeft, *ribbonRight;
    int                     ribbonLength    = 200;
    ofColor                 ribbonColor     = ofColor::black;
    float                   ribbonThickness = 10.0;
    float                   ribbonRadius    = 600;
    float                   ribbonRadiusMax = 1000;

};

}



#endif //BLEEDINGEYE_RIBBON_H
