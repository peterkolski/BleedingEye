//
// Created by Peter A. Kolski on 25.10.16.
//

#include "Network.h"

namespace bildpeter
{

void Network::setup( int numPoints )
{
    network_.setCorrelation( 777 );

    setRandomPositions( numPoints );

}

void Network::setRandomPositions( int _num )
{
    ofLogVerbose( ) << "Setting random node position";
    network_.nodes_.clear( );
    for ( int i = 0; i < _num; ++i ) {
        network_.nodes_.emplace_back( i );
        network_.nodes_.back( ).setRandomPosition( -( ofGetWidth( ) / 2 ), ofGetWidth( ) / 2,
                                                  -( ofGetWidth( ) / 2 ), ofGetWidth( ) / 2,
                                                  -( ofGetWidth( ) / 2 ), ofGetWidth( ) / 2 );

        ofLogVerbose( ) << "node ID: " << network_.nodes_.back( ).getId( ) << " ( "
                        << network_.nodes_.back( ).getPosition( ).x << ", "
                        << network_.nodes_.back( ).getPosition( ).y << ", "
                        << network_.nodes_.back( ).getPosition( ).z << " )";
    }
}

void Network::update( float fade, float movement, float distCenter, float distDiff, float arm, float back,
                      float shoulder, float movementSensor, float distCenterSensor, float distDiffSensor )
{
    netMoveSensor_ = ( 1 - arm ) * movementSensor;
    netDiffSensor_ = ( 1 - back ) * distDiffSensor;
    netCenterSensor_ = ( 1 - shoulder ) * distCenterSensor;

    if ( fade ) {
        distanceCenter_ = ofClamp( distCenter - netCenterSensor_, 0.0, 1.0 ) * distanceMaxCenter_;
        distanceDifference_ = ofClamp( distDiff - netDiffSensor_, 0.0, 1.0 ) * distanceMaxDifference_;
        minDist_ = distanceCenter_ - distanceDifference_ / 2;
        maxDist_ = distanceCenter_ + distanceDifference_ / 2;
        valOpacity_ = ofClamp( fade, 0.0, 1.0 );
        valMovement_ = ofClamp( movement - netMoveSensor_, 0.0, 1.0 ) * movementMax_;

        network_.setMaxMovement( valMovement_ );
        network_.update( );
    }
}

void Network::draw( float fade )
{
    if ( fade ) {
        if ( isPointDrawing_ ) network_.drawPoints( 2, ofColor::gray );

        ofPushMatrix( );
        {
            ofTranslate( ofGetWidth( ) / 2, ofGetHeight( ) / 2, -1000 );
            network_.draw( minDist_, maxDist_, valOpacity_ );
        }
        ofPopMatrix( );
    }
}

}