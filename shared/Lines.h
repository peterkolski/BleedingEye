//
// Created by Peter A. Kolski on 25.10.16.
//

#ifndef BLEEDINGEYE_LINES_H
#define BLEEDINGEYE_LINES_H


#include "ofMain.h"
#include "LinesHorizontal.hpp"


namespace bildpeter
{

class Lines
{

public:
    void setup();

    void update( float fade, float speed, float speedSensor, float arm );

    void draw( float fade, float brightness );

private:
    bildpeter::LinesHorizontal lines_;
    float linesSensor_;
};

}


#endif //BLEEDINGEYE_LINES_H
