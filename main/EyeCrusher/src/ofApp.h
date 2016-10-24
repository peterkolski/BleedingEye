#pragma once

#include <Flow.h>
#include "ofMain.h"

#include "ofxGui.h"

#include "ofxMidi.h"

#include "Ribbon.h"

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
	bildpeter::Ribbon   ribbon;
    bildpeter::Flow     flow;

    // --- Video
    void    videoUpdate();
    void    videoDraw();
    void    videoNext();
    bildpeter::VideoDirectoryPlayer     videoA, videoB;
    
    // --- Network
    void networkUpdate( float fade, float movement, float distCenter, float distDiff, float arm, float back,
                        float shoulder, float movementSensor, float distCenterSensor, float distDiffSensor );
    void networkDraw( float fade );
    bildpeter::NetworkVisual    network;

    // --- VALUES
    float           valMovement;
    float           valOpacity;
    float           movementMax             = 500.0;
    float           distanceMaxDifference   = 500.0;
    float           distanceMaxCenter       = 500.0;
    float           distanceDifference;
    float           distanceCenter;
    float           minDist, maxDist;
    float   netMoveSensor, netConnectionSensor, netDiffSensor, netCenterSensor;


    // --- LINES
    void    linesSetup();
    void    linesUpdate();
    void    linesDraw();
    bildpeter::LinesHorizontal  lines;

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
    bildpeter::MidiValues   midiUC;


    void    controlUpdate();
    void    controlSet1();
    void    controlNextSet();
    float   videoASensor, videoBSensor;
    float   linesSensor;
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



    
    ofEasyCam       camera;
};
