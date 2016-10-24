#pragma once

#include "ofMain.h"

#include "ofxGui.h"

#include "ofxMidi.h"
#include "ofxFlowTools.h"

#include "Ribbon.h"

#include "FlowPoint.hpp"
#include "LinesHorizontal.hpp"
#include "NetworkNode.hpp"
#include "NetworkVisual.hpp"
#include "DancePerfOSC.hpp"
#include "videoDirectory.hpp"
#include "MidiValues.hpp"


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
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
    void                setRandomPositions( int _num );
    void                drawInputIndicator();
    void                adjustSensitivity();
    bool                isPointDrawing  = false;

	// TODO easier construction
	bildpeter::Ribbon ribbon;


    // --- Video
    void    videoUpdate();
    void    videoDraw();
    void    videoNext();
    bildpeter::VideoDirectoryPlayer     videoA, videoB;
    
    // --- Network
    void    networkUpdate();
    void    networkDraw();
    bildpeter::NetworkVisual    network;

    // --- LINES
    void    linesSetup();
    void    linesUpdate();
    void    linesDraw();
    bildpeter::LinesHorizontal  lines;
    
    // --- FLOW
    void flowSetup( ofColor color );
    void flowUpdate( float fadeFlow, float strengthFlow );
    void flowDraw( float fadeFlow );
    flowTools::ftFluidSimulation	fluidSimulation;
    vector< FlowPoint > flowPoints;
    ofVec2f             posCurrent, posPrevious, posDelta;
    int					flowWidth;
    int					flowHeight;
    int					drawWidth;
    int					drawHeight;
    
    ofEasyCam           cam;
    
    // --- OSC
    bildpeter::SensorOSC    oscSensor;
    vector< float >         oscData;
    int                     oscPort;
    int                     inputIsRandom = false;
    
    // --- MIDI
    void                    setupMidi();
    void                    newMidiMessage( ofxMidiMessage& eventArgs );
    ofxMidiIn               midiIn;
//    unordered_map< int, float>  midiControlXS;
//    bildpeter::MidiValues   midiXS;
    bildpeter::MidiValues   midiUC;

    
    //--- CONTROL
    void    controlInit();
    void    controlUpdate();
    void    controlSet1();
    void    controlNextSet();
    float   videoASensor, videoBSensor;
    float   flowSensorA, flowSensorB, flowSensorC;
    float   linesSensor;
    float   netMoveSensor, netConnectionSensor, netDiffSensor, netCenterSensor;
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
    float           minDist, maxDist;

    // --- VALUES
    float           valMovement;
    float           valMovementShift;
    float           valOpacity;
    float           movementMax             = 500.0;
    float           distanceMaxDifference   = 500.0;
    float           distanceMaxCenter       = 500.0;
    float           distanceDifference;
    float           distanceCenter;

    
    ofEasyCam       camera;
};
