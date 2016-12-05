#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
//    ofEnableAntiAliasing();
    ofSetLogLevel( OF_LOG_VERBOSE );
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

    midiMapper.midiSetup(
            "/Users/sonneundasche/programming/of/apps/BleedingEye/main/EyeCrusher/bin/data/SettingsMidi.xml", this );

    flow.setup( ofColor::lightBlue );
    network.setup( guiNumPoints );
    lines.setup( );

    videoSwitchLeft.setMaps(    keyMapLeftVideo,  keyMapLeftBank );
    videoSwitcherRight.setMaps( keyMapRightVideo, keyMapRightBank );

    video.setup( "/Users/sonneundasche/programming/of/apps/BleedingEye/data/videosA/",
                 "/Users/sonneundasche/programming/of/apps/BleedingEye/data/videosB/" );
}

//--------------------------------------------------------------
void ofApp::update(){
    oscSensor.update();
    oscData = oscSensor.getData();
    oscSensor.adjustSensitivity( oscData, midiMapper.midiUsed_.getValue( "sensitivity" ) );

    controlUpdate();

    video.update( midiMapper.midiUsed_.getValue( "videoFaderA" ), midiMapper.midiUsed_.getValue( "videoFaderB" ), midiMapper.midiUsed_.getValue( "videoSensorA" ),
                  midiMapper.midiUsed_.getValue( "videoSensorB" ), armValue, backValue );
    network.update( midiMapper.midiUsed_.getValue( "networkFade" ), midiMapper.midiUsed_.getValue( "networkMovement" ),
                    midiMapper.midiUsed_.getValue( "networkDistCenter" ), midiMapper.midiUsed_.getValue( "networkDistDiff" ), armValue, backValue,
                    shoulderValue, midiMapper.midiUsed_.getValue( "networkMovementSensor" ),
                    midiMapper.midiUsed_.getValue( "networkDistCenterSensor" ), midiMapper.midiUsed_.getValue( "networkDistDiffSensor" ) );
    lines.update( midiMapper.midiUsed_.getValue( "linesFade" ), midiMapper.midiUsed_.getValue( "linesSpeed" ),
                  midiMapper.midiUsed_.getValue( "linesSpeedSensor" ),
                  armValue );
    flow.update( midiMapper.midiUsed_.getValue( "flowFade" ), midiMapper.midiUsed_.getValue( "flowStrength" ), armValue, shoulderValue, backValue,
                 midiMapper.midiUsed_.getValue( "flowStrengthSensor" ) );

    ribbon.update( midiMapper.midiUsed_.getValue( "ribbonSize"),
                   midiMapper.midiUsed_.getValue( "ribbonFade"),
                   armValue, shoulderValue, backValue );
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofBackground( ofColor::black );
//    ofBackgroundGradient( ofColor( 0 ), ofColor( 100 ) , OF_GRADIENT_CIRCULAR );

    video.draw( midiMapper.midiUsed_.getValue( "videoFaderA" ), midiMapper.midiUsed_.getValue( "videoFaderB" ) );
    lines.draw( midiMapper.midiUsed_.getValue( "linesFade" ), midiMapper.midiUsed_.getValue( "linesColor" ) );

    network.draw( midiMapper.midiUsed_.getValue( "networkFade" ) );
    ribbon.draw( midiMapper.midiUsed_.getValue( "ribbonFade" ) );
    flow.draw( midiMapper.midiUsed_.getValue( "flowFade" ) );
    ofDrawBitmapStringHighlight( ofToString( ofGetFrameRate() ), ofPoint( 100, 100 ) );
}

//--------------------------------------------------------------

void ofApp::keyPressed(int key){
    
    switch ( key ) {
        case 'r':   network.setRandomPositions( guiNumPoints ); break;
        case 'p':   network.isPointDrawing_ = !network.isPointDrawing_;   break;
        case 's':   controlNextSet();                   break;
        case 'f':
            isFullscreen = !isFullscreen;
            ofSetFullscreen( isFullscreen );
            break;
            
        default:    break;
    }

    if ( videoSwitchLeft.grabKey( key ) )
    {
        video.setVideoA( videoSwitchLeft.getIndexVideo() );
        video.setBankA( videoSwitchLeft.getIndexBank() );
        ofLogVerbose() << "LEFT | video: " << videoSwitchLeft.getIndexVideo()
                       << " bank: " << videoSwitchLeft.getIndexBank();
    }


    if ( videoSwitcherRight.grabKey( key ) )
    {
        video.setVideoB( videoSwitcherRight.getIndexVideo() );
        video.setBankB( videoSwitcherRight.getIndexBank() );
        ofLogVerbose()  << "Right | video: " << videoSwitcherRight.getIndexVideo()
                        << " bank: " << videoSwitcherRight.getIndexBank();
    }
}

//--------------------------------------------------------------

void ofApp::newMidiMessage(ofxMidiMessage& msg) {
 
    if( msg.channel == 1 )
    {
        midiMapper.midiUsed_.updateMessageValues( msg );
    }
}

//--------------------------------------------------------------
void ofApp::exit() {
    midiMapper.close( this );
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

//--------------------------------------------------------------

void ofApp::drawInputIndicator()
{
    if ( !inputIsRandom )
        ofDrawBitmapStringHighlight( "INPUT: OSC", ofGetWidth() - 100, ofGetHeight() - 10 );
    else
        ofDrawBitmapStringHighlight( "INPUT: Noise", ofGetWidth() - 100, ofGetHeight() - 10 );
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
