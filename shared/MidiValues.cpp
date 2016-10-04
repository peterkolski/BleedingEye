//
//  MidiValues.cpp
//  LacunaDance
//
//  Created by Peter A. Kolski on 18.04.16.
//
//

#include "MidiValues.hpp"

namespace bildpeter
{
    void MidiValues::setNameControlerPair(string _name, int _controler )
    {
        nameToControler_[ _name ]       = _controler;
        controlToName_[ _controler ]    = _name;
        nameToValue_[ _name ]           = 0.0;
        controlToValue_[ _controler ]   = 0.0;
    }
    
    void MidiValues::updateMessageValues( ofxMidiMessage &_msg )
    {
        auto  &_control = _msg.control;
        
        if ( controlToValue_.count( _control ) ) // check if controler is set
        {
            // set the two values
            controlToValue_[ _control ]                 = ofMap( _msg.value, 0, 127, 0.0, 1.0 );
            nameToValue_[ controlToName_[ _control ] ]  = ofMap( _msg.value, 0, 127, 0.0, 1.0 );
        }
    }

} // namespace bildpeter