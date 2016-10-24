//
// Created by Peter A. Kolski on 25.10.16.
//

#ifndef BLEEDINGEYE_LINES_H
#define BLEEDINGEYE_LINES_H


#include "ofMain.h"
#include "ofxMidi.h"
#include "LinesHorizontal.hpp"

class Lines
{

public:
    void    linesSetup();

    void linesUpdate( float fade, float speed, float speedSensor, float arm );

    void linesDraw( float fade, float brightness );

private:
    bildpeter::LinesHorizontal  lines;
    float   linesSensor;
};


#endif //BLEEDINGEYE_LINES_H
