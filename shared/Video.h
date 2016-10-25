//
// Created by Peter A. Kolski on 25.10.16.
//

#ifndef BLEEDINGEYE_VIDEO_H
#define BLEEDINGEYE_VIDEO_H


#include "ofMain.h"
#include "ofxMidi.h"
#include "videoDirectory.hpp"

class Video
{

public:
    float videoASensor;
    float videoBSensor;
    bildpeter::VideoDirectoryPlayer videoA;
    bildpeter::VideoDirectoryPlayer videoB;

    // --- Video
    void videoSetup( string pathA, string pathB );

    void videoUpdate( float faderA, float faderB, float sensorA, float sensorB, float arm, float back );

    void videoDraw( float videoFaderA, float videoFaderB );

    void    videoNext();
};


#endif //BLEEDINGEYE_VIDEO_H
