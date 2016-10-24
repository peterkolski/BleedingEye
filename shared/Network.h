//
// Created by Peter A. Kolski on 25.10.16.
//

#ifndef BLEEDINGEYE_NETWORK_H
#define BLEEDINGEYE_NETWORK_H

#include "NetworkVisual.hpp"

namespace bildpeter
{

// TODO comments

class Network
{
public:
    void setup( int numPoints );

    void update( float fade, float movement, float distCenter, float distDiff, float arm, float back,
                 float shoulder, float movementSensor, float distCenterSensor, float distDiffSensor );

    void draw( float fade );

    void setRandomPositions( int _num );

    bool isPointDrawing = false;

private:
    bildpeter::NetworkVisual network;
    float valMovement;
    float valOpacity;
    float movementMax = 500.0;
    float distanceMaxDifference = 500.0;
    float distanceMaxCenter = 500.0;
    float distanceDifference;
    float distanceCenter;
    float minDist;
    float maxDist;
    float netMoveSensor;
    float netDiffSensor;
    float netCenterSensor;

};
}

#endif //BLEEDINGEYE_NETWORK_H
