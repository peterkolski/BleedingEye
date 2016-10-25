//
// Created by Peter A. Kolski on 25.10.16.
//

#ifndef BLEEDINGEYE_VIDEO_H
#define BLEEDINGEYE_VIDEO_H


#include "ofMain.h"
#include "ofxMidi.h"
#include "videoDirectory.hpp"

namespace bildpeter
{
class Video
{

public:
    void videoSetup( string pathA, string pathB );

    void videoUpdate( float faderA, float faderB, float sensorA, float sensorB, float arm, float back );

    void videoDraw( float videoFaderA, float videoFaderB );

    void videoNext();

private:
    float videoASensor;
    float videoBSensor;
    VideoDirectoryPlayer videoA;
    VideoDirectoryPlayer videoB;
};

} // namespace bildpeter


#endif //BLEEDINGEYE_VIDEO_H
