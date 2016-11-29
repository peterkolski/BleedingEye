//
// Created by Peter A. Kolski on 29.11.16.
//

#include "MidiMapping.h"

namespace bildpeter
{

/// Activation of a midi device and assigning CC values to each needed word-key
/// \param path to a XML file with tags found in  MidiMapping.h

void MidiMapping::midiSetup( string path, ofxMidiListener *listener )
{
    if ( xmlReader.loadFile( path ) )
    {
        if ( xmlReader.tagExists( keyMidiPort ) )
        {
            midiIn.openPort( xmlReader.getValue( keyMidiPort, 0 ) );
        }
        else
        {
            ofLogError() << "Midi key in 'SettingsMidi.txt' not found: " << keyMidiPort << " - Port set to 0";
            midiIn.openPort( 0 );
        }

        midiIn.addListener( listener );
        midiIn.setVerbose( true);
        midiIn.listPorts();

        for( auto &key : midiKeywordsOld )
        {
            if ( xmlReader.tagExists( key ) )
            {
                midiUsed.setNameControlerPair( key, xmlReader.getValue( key, midiValStandard ) );
            }
            else
            {
                ofLogError() << "Midi key in 'SettingsMidi.txt' not found: " << key
                             << "  - set to 188";
                midiUsed.setNameControlerPair( key, midiValStandard );
            }
        }

        ofLogNotice() << "XML file Loaded. \n";
    }
    else
    {
        ofLogError() << "File 'SettingsMidi.txt' not found. No Midi loaded. ";
    }
}

void MidiMapping::close( ofxMidiListener *listener )
{
    midiIn.closePort();
    midiIn.removeListener( listener );
}

} // namespace bildpeter