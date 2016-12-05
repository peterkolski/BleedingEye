//
//  SensorOSC.cpp
//  RibbonDev
//
//  Created by Peter A. Kolski on 15.04.16.
//
//

#include "SensorOSC.hpp"

namespace bildpeter {
    
    
    void SensorOSC::setup( int _oscPort, string _adress, int _values )
    {
        receiver_.setup( _oscPort );
        data_           = vector< float >( _values );
        filters_        = vector< ofxOneEuroFilter >( _values );
        oscAdress_      = _adress;
        
        // init filter value
        double frequency    = 60 ;  // Hz
        double mincutoff    = 1.0 ; // fixed
        double beta         = 1.0 ; // fixed
        double dcutoff      = 1.0 ; // this one should be ok

        for ( auto &filter : filters_ )
        {
            filter.setup( frequency, mincutoff, beta, dcutoff );
        }
    }
    
    // ------------------------------------------------------------
    
    void SensorOSC::update()
    {
        if ( useRandomValues_ )
        {
            generateNoise();
            newDataReceived_ = true;
        }
        else
        {
            getOscData();
            
            if ( newDataReceived_ )
            {
                processData();
            }
        }
    }
    
    void SensorOSC::update( int _frequency, int _mincutoff, int _beta, int _derivedCutoff )
    {
        for( auto &filter : filters_ )
        {
            filter.setFrequency( _frequency );
            filter.setMinCutoff( _mincutoff );
            filter.setBeta( _beta );
            filter.setDerivateCutoff( _derivedCutoff );
        }
        update();
    }

    // ------------------------------------------------------------

void SensorOSC::adjustSensitivity( vector< float > &oscData, float sensitivity )
{
    for ( auto &sensorValue : oscData )
    {
        sensorValue = ofMap(    sensorValue,
                                0.0 + sensitivity / 2,
                                1.0 - sensitivity / 2,
                                0.0, 1.0, true );
    }
}

// ------------------------------------------------------------

    void SensorOSC::processData()
    {
        for ( int i = 0; i < data_.size(); ++i )
        {
            if ( useFilter_ )
            {
//                data_[ i ] = filters_[ i ].filter( oscMessage_.getArgAsFloat( i ), ofGetElapsedTimef() );
                data_[ i ] = filters_[ i ].filter( oscMessage_.getArgAsFloat( i ) );
            }
            else
            {
                data_[ i ] = oscMessage_.getArgAsFloat( i );
            }
        }
    }
    
    // ------------------------------------------------------------
    
    void SensorOSC::getOscData()
    {
        newDataReceived_ = false;
        
        // --- just take the last message for each frame
        while( receiver_.hasWaitingMessages() )
        {
            receiver_.getNextMessage( oscMessageUndecided_ );
            if( oscMessageUndecided_.getAddress() == oscAdress_ )
            {
                newDataReceived_ = true;
                oscMessage_ = oscMessageUndecided_;
            }
        }
    }
    
    // ------------------------------------------------------------
    
    void SensorOSC::generateNoise()
    {
        for ( int i = 0; i < data_.size(); ++i )
        {
            data_[ i ] = ofNoise( ofGetElapsedTimef() + i * 1000 );
        }
    }
    
    // ------------------------------------------------------------
    
}  // namespace bildpeter