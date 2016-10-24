//
// Created by Peter A. Kolski on 24.10.16.
//

#ifndef BLEEDINGEYE_FLOW_H
#define BLEEDINGEYE_FLOW_H

#include "ofMain.h"
#include "ofxFlowTools.h"
#include "FlowPoint.hpp"

namespace bildpeter {
    class Flow {

    public:
        void setup( ofColor color );
        void update( float fadeFlow, float strengthFlow, float a, float s, float b, float strengthSensor );
        void draw( float fadeFlow );

    private:
        flowTools::ftFluidSimulation fluidSimulation;
        vector< FlowPoint > flowPoints;
        ofVec2f posCurrent;
        ofVec2f posPrevious;
        ofVec2f posDelta;
        int flowWidth;
        int flowHeight;
        int drawWidth;
        int drawHeight;
        float flowSensorA;
        float flowSensorB;
        float flowSensorC;

    };

}
#endif //BLEEDINGEYE_FLOW_H
