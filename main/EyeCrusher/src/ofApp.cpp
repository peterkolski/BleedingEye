#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofEnableAntiAliasing();
//    ofSetLogLevel( OF_LOG_VERBOSE );
    ofEnableAlphaBlending();
    ofHideCursor();
    
    gui.setup();
    gui.add( guiNumPoints.setup( "Num Points", 100, 0, 200 ) );
    gui.add( guiDistDiff.setup( "Dist Diff", 100, 0, ofGetWidth() ) );
    gui.add( guiDistCenter.setup( "Dist Center", 100, 0, ofGetWidth() ) );
    gui.add( guiOscOpacity.setup( "OSC Opacity", 0.5, 0.0, 1.0 ) );
    gui.add( guiOscShift.setup( "OSC Shift", 0.0, 0.0, 1.0 ) );
    gui.add( guiOscMaxMovement.setup( "OSC move distance", 100.0, 0.0, 500.0 ) );


    oscPort = 6000;
    oscSensor.setup( oscPort, "/dance", 7 );
    oscSensor.enableRandomValues( inputIsRandom );

    cout << "FileLoaded: "
         << xmlReader.loadFile("/Users/sonneundasche/programming/of/apps/BleedingEye/main/EyeCrusher/bin/data/SettingsMidi.txt")
         << "\n";

    // --- MIDI
    midiIn.openPort( 1 );
    midiIn.addListener( this );
    midiIn.setVerbose(true);
    midiIn.listPorts();
    setupMidi();
    midiUsed = midiNano;

    flow.setup( ofColor::lightBlue );
    network.setup( guiNumPoints );
    lines.setup( );
    video.setup( "/Users/sonneundasche/programming/of/apps/BleedingEye/data/videosA/",
                 "/Users/sonneundasche/programming/of/apps/BleedingEye/data/videosB/" );
}

//--------------------------------------------------------------
void ofApp::update(){
    oscSensor.update();
    oscData = oscSensor.getData();
    adjustSensitivity();
    controlUpdate();

    video.update( midiUsed.getValue( "videoFaderA" ), midiUsed.getValue( "videoFaderB" ), midiUsed.getValue( "videoSensorA" ),
                  midiUsed.getValue( "videoSensorB" ), armValue, backValue );
    network.update( midiUsed.getValue( "networkFade" ), midiUsed.getValue( "networkMovement" ),
                    midiUsed.getValue( "networkDistCenter" ), midiUsed.getValue( "networkDistDiff" ), armValue, backValue,
                    shoulderValue, midiUsed.getValue( "networkMovementSensor" ),
                    midiUsed.getValue( "networkDistCenterSensor" ), midiUsed.getValue( "networkDistDiffSensor" ) );
    lines.update( midiUsed.getValue( "linesFade" ), midiUsed.getValue( "linesSpeed" ),
                  midiUsed.getValue( "linesSpeedSensor" ),
                  armValue );
    flow.update( midiUsed.getValue( "flowFade" ), midiUsed.getValue( "flowStrength" ), armValue, shoulderValue, backValue,
                 midiUsed.getValue( "flowStrengthSensor" ) );

    ribbon.update( midiUsed.getValue( "ribbonSize"),
                   midiUsed.getValue( "ribbonFade"),
                   armValue, shoulderValue, backValue );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( ofColor::black );
//    ofBackgroundGradient( ofColor( 0 ), ofColor( 100 ) , OF_GRADIENT_CIRCULAR );

    video.draw( midiUsed.getValue( "videoFaderA" ), midiUsed.getValue( "videoFaderB" ) );
    lines.draw( midiUsed.getValue( "linesFade" ), midiUsed.getValue( "linesColor" ) );

    network.draw( midiUsed.getValue( "networkFade" ) );
    ribbon.draw( midiUsed.getValue( "ribbonFade" ) );
    flow.draw( midiUsed.getValue( "flowFade" ) );
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    
    switch ( key ) {
        case 'r':   network.setRandomPositions( guiNumPoints ); break;
        case 'p':   network.isPointDrawing_ = !network.isPointDrawing_;   break;
        case 's':   controlNextSet();                   break;
//        case 'i':
//            inputIsRandom = !inputIsRandom;
//            oscSensor.enableRandomValues( inputIsRandom );
//            break;
        case 'f':
            isFullscreen = !isFullscreen;
            ofSetFullscreen( isFullscreen );
            break;
            
        default:    break;
    }
}

//--------------------------------------------------------------

void ofApp::newMidiMessage(ofxMidiMessage& msg) {
 
    if( msg.channel == 1 )
    {
        midiUsed.updateMessageValues( msg );
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    midiIn.closePort();
    midiIn.removeListener(this);
}

//--------------------------------------------------------------

void ofApp::guiUpdate()
{
    // For Network
//    minDist             = guiDistCenter - guiDistDiff / 2;
//    maxDist             = guiDistCenter + guiDistDiff / 2;
//    valOpacity          = oscData[ 0 ] * guiOscOpacity;
//    valMovement         = oscData[ 0 ] * guiOscMaxMovement;
}

void    ofApp::adjustSensitivity()
{
    for ( auto &sensorValue : oscData )
    {
        sensorValue = ofMap(    sensorValue,
                                0.0 + midiUsed.getValue( "sensitivity" ) / 2,
                                1.0 - midiUsed.getValue( "sensitivity" ) / 2,
                                0.0, 1.0, true );
    }
}

//--------------------------------------------------------------

void ofApp::drawInputIndicator()
{
    if ( !inputIsRandom )
        ofDrawBitmapStringHighlight( "INPUT: OSC", ofGetWidth() - 100, ofGetHeight() - 10 );
    else
        ofDrawBitmapStringHighlight( "INPUT: Noise", ofGetWidth() - 100, ofGetHeight() - 10 );
}

//--------------------------------------------------------------

void ofApp::setupMidi()
{
    midiUC.setNameControlerPair( "networkFade", 1 );
    midiUC.setNameControlerPair( "networkFadeSensor", 10 );
    midiUC.setNameControlerPair( "networkMovement", 18 );
    midiUC.setNameControlerPair( "networkMovementSensor", 26 );
    midiUC.setNameControlerPair( "networkDistCenter", 2 );
    midiUC.setNameControlerPair( "networkDistCenterSensor", 11 );
    midiUC.setNameControlerPair( "networkDistDiff", 19 );
    midiUC.setNameControlerPair( "networkDistDiffSensor", 27 );
    
    midiUC.setNameControlerPair( "linesFade", 3 );
    midiUC.setNameControlerPair( "linesSpeed", 12 );
    midiUC.setNameControlerPair( "linesSpeedSensor", 20 );
    midiUC.setNameControlerPair( "linesColor", 28 );
    
    midiUC.setNameControlerPair( "flowFade", 4 );
    midiUC.setNameControlerPair( "flowStrength", 13 );
    midiUC.setNameControlerPair( "flowStrengthSensor", 21 );
    
    midiUC.setNameControlerPair("ribbonFade", 5 );
    midiUC.setNameControlerPair("ribbonSize", 14 );
    
    midiUC.setNameControlerPair( "videoFaderA", 7 );
    midiUC.setNameControlerPair( "videoFaderB", 8 );
    midiUC.setNameControlerPair( "videoSensorA", 16 );
    midiUC.setNameControlerPair( "videoSensorB", 17 );
    
    midiUC.setNameControlerPair( "sensitivity", 9 );

    midiNano.setNameControlerPair( "networkFade", 1 );
    midiNano.setNameControlerPair( "networkFadeSensor", 88 );
    midiNano.setNameControlerPair( "networkMovement", 11 );
    midiNano.setNameControlerPair( "networkMovementSensor", 88 );
    midiNano.setNameControlerPair( "networkDistCenter", 2 );
    midiNano.setNameControlerPair( "networkDistCenterSensor", 88 );
    midiNano.setNameControlerPair( "networkDistDiff", 12 );
    midiNano.setNameControlerPair( "networkDistDiffSensor", 88 );

    midiNano.setNameControlerPair( "linesFade", 3 );
    midiNano.setNameControlerPair( "linesSpeed", 13 );
    midiNano.setNameControlerPair( "linesSpeedSensor", 88 );
    midiNano.setNameControlerPair( "linesColor", 4 );

    midiNano.setNameControlerPair( "flowFade", 5 );
    midiNano.setNameControlerPair( "flowStrength", 15 );
    midiNano.setNameControlerPair( "flowStrengthSensor", 88 );

    midiNano.setNameControlerPair("ribbonFade", 6 );
    midiNano.setNameControlerPair("ribbonSize", 16 );

    midiNano.setNameControlerPair( "videoFaderA", 8 );
    midiNano.setNameControlerPair( "videoSensorA", 88 );
    midiNano.setNameControlerPair( "videoFaderB", 9 );
    midiNano.setNameControlerPair( "videoSensorB", 88 );

    midiNano.setNameControlerPair( "sensitivity", 20 );
}


//--------------------------------------------------------------

void ofApp::controlNextSet()
{
    video.next( );
}

//--------------------------------------------------------------

void ofApp::controlUpdate()
{
    controlSet1();
}

//--------------------------------------------------------------

void ofApp::controlSet1()
{
    // -- In case two linbs are mapped, just use one value
    armValue          = std::max( oscData[ 2 ], oscData[ 2 ] ); // 2 real | 0 mapped
    shoulderValue     = std::max( oscData[ 3 ], oscData[ 3 ] );
    backValue         = std::max( oscData[ 0 ], oscData[ 0 ] ); // 0 real | 4 mapped
    legValue          = std::max( oscData[ 6 ], oscData[ 6 ] );

}
