//
//  FlowPoint.hpp
//  Flow
//
//  Created by Peter A. Kolski on 19.04.16.
//
//

#ifndef FlowPoint_hpp
#define FlowPoint_hpp

#include "ofxFlowTools.h"


class FlowPoint {
public:
    void            setup( int _flowWidth, int _flowHeight );
    ofTexture      &getVelocityTexture()    { return force_[ 0 ].getTexture(); }
    ofTexture      &getDensityTexture()     { return force_[ 1 ].getTexture(); }
    
    void    applyForce( ofVec2f pos )       {   force_[ 0 ].applyForce( pos );
                                                force_[ 1 ].applyForce( pos ); }
    void    setColor( ofColor _color )      {   force_[ 1 ].setForce( _color ); }
    void    setDirection( ofVec2f pos )     {   force_[ 0 ].setForce( pos ); }
    void    setStrength( float _strength )  {   force_[ 0 ].setStrength( _strength );
                                                force_[ 1 ].setStrength( _strength  / 10.0 ); }
    void    setRadius( float rad )          {   force_[ 0 ].setRadius( rad * 0.03 );
                                                force_[ 1 ].setRadius( rad * 0.02 );
}
    
    void    update()    { force_[ 0 ].update();
                          force_[ 1 ].update(); }
    
    
    
    
    vector< flowTools::ftDrawForce >      force_;
    ofVec2f                     posCurrent, posPrevious, posDelta;
    
};

#endif /* FlowPoint_hpp */
