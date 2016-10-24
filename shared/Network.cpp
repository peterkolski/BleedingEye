//
// Created by Peter A. Kolski on 25.10.16.
//

#include "Network.h"

namespace bildpeter
{

void Network::setup( int numPoints )
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

void Network::update( float fade, float movement, float distCenter, float distDiff, float arm, float back,
                      float shoulder, float movementSensor, float distCenterSensor, float distDiffSensor )
{
    netMoveSensor = ( 1 - arm ) * movementSensor;
    netDiffSensor = ( 1 - back ) * distDiffSensor;
    netCenterSensor = ( 1 - shoulder ) * distCenterSensor;

    if ( fade ) {
        distanceCenter = ofClamp( distCenter - netCenterSensor, 0.0, 1.0 ) * distanceMaxCenter;
        distanceDifference = ofClamp( distDiff - netDiffSensor, 0.0, 1.0 ) * distanceMaxDifference;
        minDist = distanceCenter - distanceDifference / 2;
        maxDist = distanceCenter + distanceDifference / 2;
        valOpacity = ofClamp( fade, 0.0, 1.0 );
        valMovement = ofClamp( movement - netMoveSensor, 0.0, 1.0 ) * movementMax;

        network.setMaxMovement( valMovement );
        network.update( );
    }
}

void Network::draw( float fade )
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