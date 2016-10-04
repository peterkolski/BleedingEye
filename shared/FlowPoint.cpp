//
//  FlowPoint.cpp
//  Flow
//
//  Created by Peter A. Kolski on 19.04.16.
//
//

#include "FlowPoint.hpp"


void FlowPoint::setup( int _flowWidth, int _flowHeight )
{
    force_ = vector< flowTools::ftDrawForce >(2);
    force_[ 0 ].setup( _flowWidth, _flowHeight, flowTools::FT_VELOCITY, true );
    force_[ 1 ].setup( _flowWidth, _flowHeight, flowTools::FT_DENSITY, true );
    
    for ( auto &_force : force_ )
    {
//        _force.setRadius( 0.02 );
        _force.setStrength( 0.01 );
    }
    force_[ 0 ].setRadius( 0.02 );
    force_[ 1 ].setRadius( 0.01 );
}