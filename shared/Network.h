//
// Created by Peter A. Kolski on 25.10.16.
//

#ifndef BLEEDINGEYE_NETWORK_H
#define BLEEDINGEYE_NETWORK_H

#include "NetworkVisual.hpp"

class Network {

public:
    // --- Network
    void networkSetup( int numPoints );

    bildpeter::NetworkVisual    network;
    // --- VALUES
    float           valMovement;
    float           valOpacity;
    float           movementMax             = 500.0;
    float           distanceMaxDifference   = 500.0;
    float           distanceMaxCenter       = 500.0;
    float           distanceDifference;
    float           distanceCenter;
    float minDist;
    float maxDist;
    float netMoveSensor;
    float netConnectionSensor;
    float netDiffSensor;
    float netCenterSensor;
    bool                isPointDrawing  = false;

    void                setRandomPositions( int _num );

    void networkUpdate( float fade, float movement, float distCenter, float distDiff, float arm, float back,
                        float shoulder, float movementSensor, float distCenterSensor, float distDiffSensor );

    void networkDraw( float fade );
};


#endif //BLEEDINGEYE_NETWORK_H
