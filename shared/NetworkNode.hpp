//
//  NetworkNode.hpp
//  NetworkDev
//
//  Created by Peter A. Kolski on 11.04.16.
//
//

#ifndef NetworkNode_hpp
#define NetworkNode_hpp

#include "ofMain.h"

namespace bildpeter {

    class Node
    {
    public:
        Node( int _id )     { id_ = _id; }
        void        update();
        void        enableMovement()    { isMoving_ = true; }
        void        disableMovement()   { isMoving_ = false; }
        
        ofVec3f     getPosition()   { return positionCurrent_; }
        int         getId()         { return id_; }

        void        setMovementShift( float _shift )        { movementTimeShift_ = _shift; }
        void        setCorrelation( float _correlation )    { noiseCorrelation_ = _correlation; }
        void        setId( int _id )    { id_ = _id; }
        void        setRandomPosition( int _xMin, int _xMax, int _yMin, int _yMax, int _zMin, int _zMax );
        void        setMaxMovement( float _max ) { positionShiftMax_ = _max; }
        
    private:
        void        updateMovement();
        
        float       movementTimeShift_  = 0.0;
        float       movementSpeed_      = 3.0;
        float       noiseCorrelation_   = 1000.0;
        int         id_;
        bool        isMoving_   = true;
        float       positionShiftMax_   = 100.0;
        ofVec3f     positionRoot_       = ofVec3f( 0.0, 0.0, 0.0 );
        ofVec3f     positionCurrent_    = ofVec3f( 0.0, 0.0, 0.0 );
        ofVec3f     positionShift_      = ofVec3f( 0.0, 0.0, 0.0 );
        
    };
    
} // namespace bildpeter


#endif /* NetworkNode_hpp */
