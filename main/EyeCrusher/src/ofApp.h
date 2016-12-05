#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMidi.h"

#include "engine/VideoDirectoryPlayer.hpp"
#include "util/KeyDetector.h"
#include "SensorOSC.hpp"

#include "MidiMapping.h"
#include "Ribbon.h"
#include "Flow.h"
#include "Network.h"
#include "Lines.h"
#include "Video.h"

// -------------------------------------------------------------------
// -------------------------------------------------------------------

/// For midi we need multiple inheritance
class ofApp : public ofBaseApp, public ofxMidiListener{

	public:
		void setup();
		void update();
		void draw();
        void exit();
	    void keyPressed(int key);


    void                drawInputIndicator();

    bildpeter::Ribbon   ribbon;
    bildpeter::Flow     flow;
    bildpeter::Network  network;
	bildpeter::Lines	lines;

    // --- Video
    bildpeter::Video        video;
    bildpeter::KeyDetector  videoSwitchLeft, videoSwitcherRight;


    // --- OSC
    bildpeter::SensorOSC    oscSensor;
    vector< float >         oscData;
    int                     oscPort;
    int                     inputIsRandom = false;
    
    // --- MIDI
    bildpeter::MidiMapping  midiMapper;
    void                    newMidiMessage( ofxMidiMessage& eventArgs );


    void    controlUpdate();
    void    controlSet1();
    void    controlNextSet();
    float   armValue, shoulderValue, backValue, legValue;


    // --- GUI
    void            guiUpdate();
    bool            useMidi      = true;
    bool            isFullscreen = false;
    ofxIntSlider    guiNumPoints;
    ofxFloatSlider  guiDistDiff;
    ofxFloatSlider  guiDistCenter;
    ofxFloatSlider  guiOscOpacity;
    ofxFloatSlider  guiOscShift;
    ofxFloatSlider  guiOscMaxMovement;
    ofxPanel        gui;
};

// ----------------------------------------------------------
// ------------------  CONSTANTS  ---------------------------

const std::unordered_map< int, int > keyMapLeftVideo =
        {
                {'1', 0 },
                {'2', 1 },
                {'3', 2 },
                {'4', 3 },
                {'5', 4 },
                {'6', 5 },
                {'7', 6 },
                {'8', 7 },
                {'9', 8 },
                {'0', 9 },
        };

const std::unordered_map< int, int > keyMapLeftBank =
        {
                {'!', 0 },
                {'"', 1 },
// TODO               {'§', 2 },
                {'$', 3 },
                {'%', 4 },
                {'&', 5 },
                {'/', 6 },
                {'(', 7 },
                {')', 8 },
                {'=', 9 },
        };


const std::unordered_map< int, int >   keyMapRightVideo  =
        {
                {'q', 0 },
                {'w', 1 },
                {'e', 2 },
                {'r', 3 },
                {'t', 4 },
                {'z', 5 },
                {'u', 6 },
                {'i', 7 },
                {'o', 8 },
                {'p', 9 }
        };

const std::unordered_map< int, int >   keyMapRightBank  =
        {
                {'Q', 0 },
                {'W', 1 },
                {'E', 2 },
                {'R', 3 },
                {'T', 4 },
                {'Z', 5 },
                {'U', 6 },
                {'I', 7 },
                {'O', 8 },
                {'P', 9 }
        };