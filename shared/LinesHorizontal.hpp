//
//  LinesHorizontal.hpp
//  LacunaDance
//
//  Created by Peter A. Kolski on 18.04.16.
//
//

#ifndef LinesHorizontal_hpp
#define LinesHorizontal_hpp

#include "LineHorizontal.hpp"
#include "ofMain.h"

namespace bildpeter {

    class LinesHorizontal
    {
    public:
        void    setup( int numLines, int speedMax, float thicknessMax, float yMin, float yMax );
        void    update();
        void    draw();
        
        void    setBounds( float min, float max )   { yBoundMin_ = min; yBoundMax_ = max; }
        void    setSpeedFactor( float factor )      { speedFactor_ = factor; }
        void    setFade( float fade )               { color_.a = fade * 255; }
        void    setColor( ofColor _color )          { color_ = _color; }
        void    setScale( float _scaleY )           { scaleY_ = ofClamp( _scaleY, 0.0, 1.0 ); }
        
    private:
        vector< Line >          linesUp_, linesDown_;
        ofColor color_          = ofColor::white;
        float   scaleY_         = 0.5;
        float   speedFactor_    = 0.0;
        float   widthGlobal_    = 0.0;
        float   yBoundMin_      = 0.0;
        float   yBoundMax_      = 0.0;
    };
}

#endif /* LinesHorizontal_hpp */
