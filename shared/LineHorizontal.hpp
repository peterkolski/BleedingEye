//
//  LineHorizontal.hpp
//  LacunaDance
//
//  Created by Peter A. Kolski on 19.04.16.
//
//

#ifndef LineHorizontal_hpp
#define LineHorizontal_hpp

#include "ofMain.h"

namespace bildpeter {
    class Line
    {
    public:
        bool    isMovingUp()        { return direction_ == 1.0 ? true : false;}
        void    setUpMovement()     { direction_ = 1.0; }
        void    setDownMovement()   { direction_ = -1.0; }
        float   yPos_;
        float   widthBase_;
        float   speedBase_;
        float   direction_ = 1.0;
        float   thickness_ = 1.0;
        
    private:
        
    };

} // namespace bildpeter


#endif /* LineHorizontal_hpp */
