//
// Created by Peter A. Kolski on 25.10.16.
//

#ifndef BLEEDINGEYE_VIDEO_H
#define BLEEDINGEYE_VIDEO_H


#include "ofMain.h"
#include "videoDirectory.hpp"

namespace bildpeter
{
class Video
{

public:
    void setup( string pathA, string pathB );

    void update( float faderA, float faderB, float sensorA, float sensorB, float arm, float back );

    void draw( float faderA, float faderB );

    void next();

private:
    float sensorValA;
    float sensorValB;
    VideoDirectoryPlayer videoA;
    VideoDirectoryPlayer videoB;
};

} // namespace bildpeter


#endif //BLEEDINGEYE_VIDEO_H
