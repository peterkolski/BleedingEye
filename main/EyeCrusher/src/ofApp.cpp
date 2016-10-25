#include "ofApp.h"
#include "Video.h"

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

    // --- VIDEO
    
    // --- MIDI
    midiIn.openPort( 0 );
    midiIn.addListener( this );
    midiIn.setVerbose(true);
//    midiIn.listPorts();
    setupMidi();

    flow.setup( ofColor::lightBlue );
    network.setup( guiNumPoints );
    lines.setup( );
    video.videoSetup( "/Users/sonneundasche/Programming/ofx/apps/LacunExh16/_excluded/videosA/",
                       "/Users/sonneundasche/Programming/ofx/apps/LacunExh16/_excluded/videosB/" );
}

//--------------------------------------------------------------
void ofApp::update(){
    oscSensor.update();
    oscData = oscSensor.getData();
    adjustSensitivity();
    controlUpdate();

    video.videoUpdate( midiUC.getValue( "videoFaderA" ), midiUC.getValue( "videoFaderB" ), midiUC.getValue( "videoSensorA" ),
                        midiUC.getValue( "videoSensorB" ), armValue, backValue );
    network.update( midiUC.getValue( "networkFade" ), midiUC.getValue( "networkMovement" ),
                    midiUC.getValue( "networkDistCenter" ), midiUC.getValue( "networkDistDiff" ), armValue, backValue,
                    shoulderValue, midiUC.getValue( "networkMovementSensor" ),
                    midiUC.getValue( "networkDistCenterSensor" ), midiUC.getValue( "networkDistDiffSensor" ) );
    lines.update( midiUC.getValue( "linesFade" ), midiUC.getValue( "linesSpeed" ),
                  midiUC.getValue( "linesSpeedSensor" ),
                  armValue );
    flow.update( midiUC.getValue( "flowFade" ), midiUC.getValue( "flowStrength" ), armValue, shoulderValue, backValue,
                 midiUC.getValue( "flowStrengthSensor" ) );

    ribbon.update( midiUC, "ribbonSize", "ribbonFade", armValue, shoulderValue, backValue );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( ofColor::black );
//    ofBackgroundGradient( ofColor( 0 ), ofColor( 100 ) , OF_GRADIENT_CIRCULAR );

    video.videoDraw( midiUC.getValue( "videoFaderA" ), midiUC.getValue( "videoFaderB" ) );
    lines.draw( midiUC.getValue( "linesFade" ), midiUC.getValue( "linesColor" ) );

    network.draw( midiUC.getValue( "networkFade" ) );
    ribbon.draw( midiUC, "ribbonFade" );
    flow.draw( midiUC.getValue( "flowFade" ) );
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
        midiUC.updateMessageValues( msg );
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    midiIn.closePort();
    midiIn.removeListener(this);
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

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
                                0.0 + midiUC.getValue( "sensitivity" ) / 2,
                                1.0 - midiUC.getValue( "sensitivity" ) / 2,
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
}


//--------------------------------------------------------------

void ofApp::controlNextSet()
{
    video.videoNext();
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
