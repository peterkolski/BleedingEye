#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxMidi.h"

#include "SensorOSC.hpp"
#include "videoDirectory.hpp"
#include "MidiValues.hpp"

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
    void                adjustSensitivity();

	// TODO easier construction
	bildpeter::Ribbon   ribbon;
    bildpeter::Flow     flow;
    bildpeter::Network  network;
	bildpeter::Lines	lines;
    bildpeter::Video    video;



    // --- OSC
    bildpeter::SensorOSC    oscSensor;
    vector< float >         oscData;
    int                     oscPort;
    int                     inputIsRandom = false;
    
    // --- MIDI
    void                    setupMidi();
    void                    newMidiMessage( ofxMidiMessage& eventArgs );
    ofxMidiIn               midiIn;
    bildpeter::MidiValues   midiUsed, midiUC, midiNano;


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
