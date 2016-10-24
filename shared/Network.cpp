//
// Created by Peter A. Kolski on 25.10.16.
//

#include "Network.h"

namespace bildpeter
{

void Network::networkSetup( int numPoints )
{
    network.setCorrelation( 777 );

    setRandomPositions( numPoints );

}

void Network::setRandomPositions( int _num )
{
    ofLogVerbose( ) << "Setting random node position";
    network.nodes_.clear( );
    for ( int i = 0; i < _num; ++i ) {
        network.nodes_.emplace_back( i );
        network.nodes_.back( ).setRandomPosition( -( ofGetWidth( ) / 2 ), ofGetWidth( ) / 2,
                                                  -( ofGetWidth( ) / 2 ), ofGetWidth( ) / 2,
                                                  -( ofGetWidth( ) / 2 ), ofGetWidth( ) / 2 );

        ofLogVerbose( ) << "node ID: " << network.nodes_.back( ).getId( ) << " ( "
                        << network.nodes_.back( ).getPosition( ).x << ", "
                        << network.nodes_.back( ).getPosition( ).y << ", "
                        << network.nodes_.back( ).getPosition( ).z << " )";
    }
}

void Network::networkUpdate( float fade, float movement, float distCenter, float distDiff, float arm, float back,
                             float shoulder, float movementSensor, float distCenterSensor, float distDiffSensor )
{
    netMoveSensor = ( 1 - arm ) * movementSensor;
    netDiffSensor = ( 1 - back ) * distDiffSensor;
    netCenterSensor = ( 1 - shoulder ) * distCenterSensor;

    if ( fade ) {
        // TODO get rid of copying
        auto opacityMain = fade;
//        auto    opacityFromSensor   = midiUC.getValue("networkFadeSensor" ) * oscData[ 2 ];
        auto movementMain = movement;
//        auto    movementFromSensor  = midiUC.getValue("networkMovementSensor") * oscData[ 0 ];
        auto distanceCenterMain = distCenter;
//        auto    distanceCenterSensor = midiUC.getValue("networkDistCenterSensor") * oscData[ 4 ];
        auto distanceDiffMain = distDiff;
//        auto    distanceDiffSensor  = midiUC.getValue("networkDistDiffSensor") * oscData[ 6 ];

        distanceCenter = ofClamp( distanceCenterMain - netCenterSensor, 0.0, 1.0 ) * distanceMaxCenter;
        distanceDifference = ofClamp( distanceDiffMain - netDiffSensor, 0.0, 1.0 ) * distanceMaxDifference;
        minDist = distanceCenter - distanceDifference / 2;
        maxDist = distanceCenter + distanceDifference / 2;
        valOpacity = ofClamp( opacityMain, 0.0, 1.0 );
        valMovement = ofClamp( movementMain - netMoveSensor, 0.0, 1.0 ) * movementMax;

        // --- NETWORK
        network.setMaxMovement( valMovement );
        network.update( );
    }
}

void Network::networkDraw( float fade )
{
    if ( fade ) {
        if ( isPointDrawing ) network.drawPoints( 2, ofColor::gray );

        ofPushMatrix( );
        {
            ofTranslate( ofGetWidth( ) / 2, ofGetHeight( ) / 2, -1000 );
            network.draw( minDist, maxDist, valOpacity );
        }
        ofPopMatrix( );
    }
}

}