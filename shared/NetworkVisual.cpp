//
//  NetworkVisual.cpp
//  NetworkDev
//
//  Created by Peter A. Kolski on 14.04.16.
//
//

#include "NetworkVisual.hpp"

namespace bildpeter {

    NetworkVisual::NetworkVisual( int nodesAmount )
    {
    
    }
    
    // ----------------------------------------------------------------------
    
    void NetworkVisual::update()
    {
        for ( auto &_node : nodes_ )
        {
            _node.update();
        }
    }

    // ----------------------------------------------------------------------
    
    void NetworkVisual::draw( float _distMin, float _distMax, float _alpha )
    {
        for ( auto &nodeSrc : nodes_ )
        {
            for ( auto &nodeTrg : nodes_ )
            {
                auto dist   = nodeSrc.getPosition().distance( nodeTrg.getPosition() );
                
                if (    (nodeSrc.getId() != nodeTrg.getId() )
                    && ( dist > _distMin )
                    && ( dist < _distMax)
                    //                && ( dist < (nodeTrg.pos.x/(float)ofGetWidth() * maxDist ) )
                    )
                {
                    auto alpha = ofMap( dist, _distMin, _distMax, 0.0, 255.0, true ) ;
                    alpha *= _alpha;
                    auto col = ofColor( 255, 255, 255, alpha );
                    
                    ofSetColor( col );
                    ofDrawLine( nodeSrc.getPosition(), nodeTrg.getPosition() );
                }
            }
        }

    }
    
    // ----------------------------------------------------------------------
    
    void NetworkVisual::setMaxMovement( float _max )
    {
        for ( auto &_node : nodes_ )
        {
            _node.setMaxMovement( _max );
        }
    }

    // ----------------------------------------------------------------------
    
    
    void NetworkVisual::setCorrelation( float _correlation )
    {
        for ( auto &_node : nodes_ )
        {
            _node.setCorrelation( _correlation );
        }
    }

    // ----------------------------------------------------------------------
    
    void NetworkVisual::setMovementShift( float _shift )
    {
        for ( auto &_node : nodes_ )
        {
            _node.setMovementShift( _shift );
        }
    }

    // ----------------------------------------------------------------------
    
    void NetworkVisual::drawPoints( float _size, ofColor _color )
    {
        ofSetColor( _color );
        for ( auto &node : nodes_ )
        {
            ofDrawCircle( node.getPosition(), _size );
        }
    }
    
} // namespace bildpeter