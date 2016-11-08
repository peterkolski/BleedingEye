//
//  SensorOSC.hpp
//  RibbonDev
//
//  Created by Peter A. Kolski on 15.04.16.
//
//

#ifndef SensorOSC_hpp
#define SensorOSC_hpp

#include "ofMain.h"
#include "ofxOsc.h"
#include "ofxOneEuroFilter.h"

namespace bildpeter{


class SensorOSC {
public:
    void                setup( int _oscPort, string _adress, int _values );
    void                update();
    void                update( int _frequency, int _mincutoff, int _beta, int _derivedCutoff );

    vector< float >     getData()                           { return data_; }
    void                setFilter( bool _filterOn )         { useFilter_ = _filterOn; }
    void                enableRandomValues( bool _switch )  { useRandomValues_ = _switch; }
    bool                hasNewData()                        { return newDataReceived_; }
    
    
private:
    void                processData();
    void                getOscData();
    void                generateNoise();
    
    ofxOscReceiver              receiver_;
    ofxOscMessage               oscMessage_, oscMessageUndecided_;
    vector< float >             data_;
    string                      oscAdress_          = "";
    bool                        newDataReceived_    = false;
    bool                        useRandomValues_    = false;
    bool                        useFilter_          = true;
    vector< ofxOneEuroFilter >  filters_;
};
    
    
} // --- namespace bildpeter


#endif /* SensorOSC_hpp */
