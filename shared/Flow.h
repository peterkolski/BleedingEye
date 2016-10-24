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
        flowTools::ftFluidSimulation fluidSimulation_;
        vector< FlowPoint > flowPoints_;
        ofVec2f posCurrent_;
        ofVec2f posPrevious_;
        int flowWidth_;
        int flowHeight_;
        int drawWidth_;
        int drawHeight_;
        float flowSensorA_;
        float flowSensorB_;
        float flowSensorC_;

    };

}
#endif //BLEEDINGEYE_FLOW_H
