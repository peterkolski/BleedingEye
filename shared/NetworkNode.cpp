//
//  NetworkNode.cpp
//  NetworkDev
//
//  Created by Peter A. Kolski on 11.04.16.
//
//

#include "NetworkNode.hpp"

namespace bildpeter {
    
void Node::update()
{
    if ( isMoving_ )
        updateMovement();
}

    
void Node::updateMovement()
{
    auto time = ofGetElapsedTimef() / movementSpeed_ + movementTimeShift_;
    
    positionShift_.x  = positionShiftMax_ * ofSignedNoise( time + id_ * noiseCorrelation_ );
    positionShift_.y  = positionShiftMax_ * ofSignedNoise( time + id_ * noiseCorrelation_ * 1/3 );
    positionShift_.z  = positionShiftMax_ * ofSignedNoise( time + id_ * noiseCorrelation_ * 2/3 );
    
    positionCurrent_    = positionShift_ + positionRoot_;
}
    
void    Node::setRandomPosition( int _xMin, int _xMax, int _yMin, int _yMax, int _zMin, int _zMax )
{
    positionRoot_ = ofVec3f{ ofRandom( _xMin, _xMax ), ofRandom( _yMin, _yMax ), ofRandom( _zMin, _zMax ) };
    positionCurrent_ = positionRoot_;
}
    
    
} // namespace bildpeter
