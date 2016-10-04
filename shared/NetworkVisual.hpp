//
//  NetworkVisual.hpp
//  NetworkDev
//
//  Created by Peter A. Kolski on 14.04.16.
//
//

#ifndef NetworkVisual_hpp
#define NetworkVisual_hpp

#include "ofMain.h"
#include <NetworkNode.hpp>

namespace bildpeter {
    
    class NetworkVisual{
    public:
        NetworkVisual() {}
        ~NetworkVisual() {}
        NetworkVisual( int nodesAmount );
        
        
        void    update();
        void    draw( float _distMin, float _distMax, float _alpha );
        
        void    drawPoints( float _size, ofColor _color );
        void    setMovementShift( float _shift );
        void    setCorrelation( float _correlation );
        void    setMaxMovement( float _max );
        
//    private:
        vector< bildpeter::Node >   nodes_;
        
    };
    
    
    
} // namespace bildpeter

#endif /* NetworkVisual_hpp */
