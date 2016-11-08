//
//  MidiValues.hpp
//  LacunaDance
//
//  Created by Peter A. Kolski on 18.04.16.
//
//

#ifndef MidiValues_hpp
#define MidiValues_hpp

#include <stdio.h>
#include "ofxMidi.h"


namespace bildpeter{

class MidiValues
{
public:
    void    updateMessageValues( ofxMidiMessage& _msg );
    void    setNameControlerPair( string _name, int _controler );
    float   getValue( string _name )    { return nameToValue_.at( _name ); }
    float   getValue( int _control )    { return controlToValue_.at( _control ); }    

private:
    unordered_map< string, int >    nameToControler_;
    unordered_map< int, string >    controlToName_;
    unordered_map< string, float >  nameToValue_;
    unordered_map< int, float>      controlToValue_;
};

} // namespace bildpeter

#endif /* MidiValues_hpp */
