//
// Created by Peter A. Kolski on 29.11.16.
//

#include "MidiMapping.h"

namespace bildpeter
{

/// Activation of a midi device and assigning CC values to each needed word-key
/// \param path to a XML file with tags found in  MidiMapping.h
/// \param listener parent of the ofApp together with ofBaseApp (Multiple Inheritance)
void MidiMapping::midiSetup( string path, ofxMidiListener *listener )
{
    if ( xmlReader_.loadFile( path ) )
    {
        if ( xmlReader_.tagExists( keyMidiPort_ ) )
        {
            midiIn_.openPort( xmlReader_.getValue( keyMidiPort_, 0 ) );
        }
        else
        {
            ofLogError() << "Midi key in 'SettingsMidi.xml' not found: " << keyMidiPort_ << " - Port set to 0";
            midiIn_.openPort( 0 );
        }

        midiIn_.addListener( listener );
        midiIn_.setVerbose( true);
        midiIn_.listPorts();

        for( auto &key : midiKeywordsOld_ )
        {
            if ( xmlReader_.tagExists( key ) )
            {
                midiUsed_.setNameControlerPair( key, xmlReader_.getValue( key, midiValStandard_ ) );
            }
            else
            {
                ofLogError() << "Midi key in 'SettingsMidi.xml' not found: " << key
                             << "  - set to 188";
                midiUsed_.setNameControlerPair( key, midiValStandard_ );
            }
        }

        ofLogNotice() << "XML file Loaded. \n";
    }
    else
    {
        ofLogError() << "File 'SettingsMidi.xml' not found. No Midi loaded. ";
    }
}

/// Should be called to avoid OS conflicts with midi devices after closing
/// \param listener parent of the ofApp together with ofBaseApp (Multiple Inheritance)
void MidiMapping::close( ofxMidiListener *listener )
{
    midiIn_.closePort();
    midiIn_.removeListener( listener );
}

} // namespace bildpeter