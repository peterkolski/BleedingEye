#include "ofApp.h"

#include "ofMain.h"
#include "ofxMidi.h"
#include "MidiValues.hpp"

#include "Ribbon.h"
#include "Flow.h"

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

    network.setCorrelation( 777 );

    setRandomPositions( guiNumPoints );
    
    oscPort = 6000;
    oscSensor.setup( oscPort, "/dance", 7 );
    oscSensor.enableRandomValues( inputIsRandom );

    // --- VIDEO
    videoA.loadDirectory( "/Users/sonneundasche/Programming/ofx/apps/LacunExh16/_excluded/videosA/" );
    videoB.loadDirectory( "/Users/sonneundasche/Programming/ofx/apps/LacunExh16/_excluded/videosB/" );
    videoA.play();
    videoB.play();
    
    linesSetup();
    
    // --- MIDI
    midiIn.openPort( 0 );
    midiIn.addListener( this );
    // verbose
    midiIn.setVerbose(true);
//    midiIn.listPorts();
    setupMidi();

    flow.setup( ofColor::lightBlue );
}

//--------------------------------------------------------------
void ofApp::update(){
    oscSensor.update();
    oscData = oscSensor.getData();
    adjustSensitivity();
    controlUpdate();
    
    videoUpdate();
    networkUpdate();
    linesUpdate();
    flow.update( midiUC.getValue( "flowFade" ), midiUC.getValue( "flowStrength" ), armValue, shoulderValue, backValue,
                 midiUC.getValue( "flowStrengthSensor" ) );

    ribbon.update( midiUC, "ribbonSize", "ribbonFade", armValue, shoulderValue, backValue );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( ofColor::black );
//    ofBackgroundGradient( ofColor( 0 ), ofColor( 100 ) , OF_GRADIENT_CIRCULAR );
    
    videoDraw();

    linesDraw();

    networkDraw();
    
    ribbon.draw( midiUC, "ribbonFade" );
    flow.draw( midiUC.getValue( "flowFade" ) );
}
//--------------------------------------------------------------
//--------------------------------------------------------------

void    ofApp::setRandomPositions( int _num )
{
    ofLogVerbose()  << "Setting random node position";
    network.nodes_.clear();
    for ( int i = 0; i  < _num; ++i)
    {
        network.nodes_.emplace_back( i );
        network.nodes_.back().setRandomPosition( -(ofGetWidth() / 2), ofGetWidth() / 2,
                                                -(ofGetWidth() / 2), ofGetWidth() / 2,
                                                -(ofGetWidth() / 2), ofGetWidth() / 2 );
        
        ofLogVerbose()  << "node ID: " << network.nodes_.back().getId() << " ( "
                        << network.nodes_.back().getPosition().x << ", "
                        << network.nodes_.back().getPosition().y << ", "
                        << network.nodes_.back().getPosition().z << " )";
    }
}

//--------------------------------------------------------------
//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    
    switch ( key ) {
        case 'r':   setRandomPositions( guiNumPoints ); break;
        case 'p':   isPointDrawing = !isPointDrawing;   break;
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
    minDist             = guiDistCenter - guiDistDiff / 2;
    maxDist             = guiDistCenter + guiDistDiff / 2;
    valOpacity          = oscData[ 0 ] * guiOscOpacity;
    valMovement         = oscData[ 0 ] * guiOscMaxMovement;
}

//--------------------------------------------------------------

void ofApp::videoUpdate()
{
    if ( midiUC.getValue( "videoFaderA" ) )
    {
        if ( !videoA.videoPlayer_.isPlaying() ) { videoA.videoPlayer_.play(); }
        videoA.update();
        videoA.fade( ofClamp( midiUC.getValue( "videoFaderA" ) - videoASensor, 0.0, 1.0 ) * 255 );
    }
    else    { videoA.videoPlayer_.setPaused( true ); }
    
    if ( midiUC.getValue( "videoFaderB" ) ) {
        if ( !videoB.videoPlayer_.isPlaying() ) { videoB.videoPlayer_.play(); }
        videoB.update();
        videoB.fade( ofClamp( midiUC.getValue( "videoFaderB" ) - videoBSensor, 0.0, 1.0 ) * 255 );
    }
    else    { videoB.videoPlayer_.setPaused( true ); }
}

//--------------------------------------------------------------

void ofApp::videoDraw()
{
    auto x = ofGetWidth() / 2;
    auto y = ofGetHeight() / 2;
    auto z = -2000;
    // macbookAir
    auto w = 5120;
    auto h = 3200;
    
    if ( midiUC.getValue( "videoFaderA" ) ) videoA.draw( x, y, z, w, h );
    if ( midiUC.getValue( "videoFaderB" ) ) videoB.draw( x, y, z, w, h );
}

//--------------------------------------------------------------

void ofApp::videoNext()
{
    videoA.nextVideo();
    videoB.nextVideo();
}

//--------------------------------------------------------------

void ofApp::networkUpdate()
{
    if ( midiUC.getValue( "networkFade" ) )
    {
        auto    opacityMain         = midiUC.getValue( "networkFade" );
//        auto    opacityFromSensor   = midiUC.getValue("networkFadeSensor" ) * oscData[ 2 ];
        auto    movementMain        = midiUC.getValue("networkMovement" );
//        auto    movementFromSensor  = midiUC.getValue("networkMovementSensor") * oscData[ 0 ];
        auto    distanceCenterMain  = midiUC.getValue("networkDistCenter");
//        auto    distanceCenterSensor = midiUC.getValue("networkDistCenterSensor") * oscData[ 4 ];
        auto    distanceDiffMain    = midiUC.getValue("networkDistDiff");
//        auto    distanceDiffSensor  = midiUC.getValue("networkDistDiffSensor") * oscData[ 6 ];
        
        distanceCenter      = ofClamp( distanceCenterMain   - netCenterSensor, 0.0, 1.0 ) * distanceMaxCenter;
        distanceDifference  = ofClamp( distanceDiffMain     - netDiffSensor, 0.0, 1.0 ) * distanceMaxDifference;
        minDist             = distanceCenter - distanceDifference / 2;
        maxDist             = distanceCenter + distanceDifference / 2;
        valOpacity          = ofClamp( opacityMain, 0.0, 1.0);
        valMovement         = ofClamp( movementMain - netMoveSensor, 0.0, 1.0 ) * movementMax;
        
        // --- NETWORK
        network.setMaxMovement( valMovement );
        network.update();
    }
}

//--------------------------------------------------------------

void ofApp::networkDraw()
{
    if ( midiUC.getValue("networkFade") )
    {
        if ( isPointDrawing )   network.drawPoints( 2, ofColor::gray );
        
        ofPushMatrix();
        {
            ofTranslate( ofGetWidth() / 2, ofGetHeight() / 2, -1000 );
            network.draw( minDist, maxDist,  valOpacity );
        }
        ofPopMatrix();
    }
}

//--------------------------------------------------------------

//--------------------------------------------------------------

//--------------------------------------------------------------

void ofApp::linesSetup()
{
    lines.setup( 20, 2.0, 3.0, ofGetScreenHeight() / 3, ofGetScreenHeight() * 2 / 3 );
    lines.setSpeedFactor( 1.0 );
}

//--------------------------------------------------------------

void ofApp::linesUpdate()
{
    lines.setSpeedFactor( ofClamp( midiUC.getValue( "linesSpeed" ) - linesSensor, 0.0, 1.0 ) );
    lines.setFade( midiUC.getValue( "linesFade" ) );
    lines.update();
}

//--------------------------------------------------------------

void ofApp::linesDraw()
{
    if ( midiUC.getValue( "linesFade" ) )
    {
        auto brightness = 255.0 * midiUC.getValue( "linesColor" );
        auto alpha      = 255.0 * midiUC.getValue("linesFade");
        auto color      = ofColor(brightness, brightness, brightness, alpha );
        
        ofPushStyle();
        {
//            ofSetColor(brightness, brightness, brightness, alpha );
            lines.setColor( color );
            lines.draw();
        }
        ofPopStyle();
    }
}


//--------------------------------------------------------------

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

//--------------------------------------------------------------

//--------------------------------------------------------------


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
    videoNext();
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
    backValue         = std::max( oscData[ 0 ], oscData[ 0 ] ); // 0 real |�4 mapped
    legValue          = std::max( oscData[ 6 ], oscData[ 6 ] );

    videoASensor        = ( 1 - armValue ) * midiUC.getValue( "videoSensorA" );
    videoBSensor        = ( 1 - backValue ) * midiUC.getValue( "videoSensorB" );

    
    linesSensor         = ( 1 - armValue ) * midiUC.getValue( "linesSpeedSensor" );

    netMoveSensor       = ( 1 - armValue ) * midiUC.getValue( "networkMovementSensor" );
    netDiffSensor       = ( 1 - backValue ) * midiUC.getValue( "networkDistDiffSensor" );
    netCenterSensor     = ( 1 - shoulderValue ) * midiUC.getValue( "networkDistCenterSensor" );
}
