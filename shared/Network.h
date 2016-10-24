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

    bool isPointDrawing_ = false;

private:
    bildpeter::NetworkVisual network_;
    float valMovement_;
    float valOpacity_;
    float movementMax_ = 500.0;
    float distanceMaxDifference_ = 500.0;
    float distanceMaxCenter_ = 500.0;
    float distanceDifference_;
    float distanceCenter_;
    float minDist_;
    float maxDist_;
    float netMoveSensor_;
    float netDiffSensor_;
    float netCenterSensor_;

};
}

#endif //BLEEDINGEYE_NETWORK_H
