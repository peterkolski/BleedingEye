#pragma once

#include "ofMain.h"
#include "ofxGui.h"
#include "ofxFlowTools.h"
#include "ofxTwistedRibbon.h"
#include "ofxMidi.h"

#include "NetworkNode.hpp"
#include "NetworkVisual.hpp"
#include "SensorOSC.hpp"
#include "VideoDirectoryPlayer.hpp"
#include "MidiValues.hpp"
#include "LinesHorizontal.hpp"
#include "FlowPoint.hpp"

// -------------------------------------------------------------------
// -------------------------------------------------------------------

// For midi we need multiple inheritance
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
    vector< ofVec3f >   getPositions( );
    void                adjustSensitivity();
    
    bool                isPointDrawing  = false;
    
    // --- Video
    void    videoUpdate();
    void    videoDraw();
    void    videoNext();
    bildpeter::VideoDirectoryPlayer     videoA, videoB;
    
    // --- Network
    void    networkUpdate();
    void    networkDraw();
    bildpeter::NetworkVisual    network;
    
    // --- Ribbon
    void    ribbonUpdate();
    void    ribbonDraw();
    ofxTwistedRibbon        *ribbonLeft, *ribbonRight;
    int                     ribbonLength    = 200;
    ofColor                 ribbonColor     = ofColor::black;
    float                   ribbonThickness = 10.0;
    float                   ribbonRadius    = 600;
    float                   ribbonRadiusMax = 1000;
    
    // --- LINES
    void    linesSetup();
    void    linesUpdate();
    void    linesDraw();
    bildpeter::LinesHorizontal  lines;
    
    // --- FLOW
    void                flowSetup();
    void                flowUpdate();
    void                flowDraw();
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
    void    controlSet2();
    void    controlset3();
    void    controlNextSet();
    float   videoASensor, videoBSensor;
    float   flowSensorA, flowSensorB, flowSensorC;
    float   linesSensor;
    float   netMoveSensor, netConnectionSensor, netDiffSensor, netCenterSensor;
    float   ribbonLeftX, ribbonLeftY, ribbonLeftZ;
    float   ribbonRightX, ribbonRightY, ribbonRightZ;
    
    
    
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
