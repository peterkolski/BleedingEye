#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){

    dirList_.listDir( "/Users/sonneundasche/programming/of/apps/BleedingEye/reseach/ofDirectory/folders/A" );

    for( auto &file : dirList_.getFiles() )
    {
        ofLogNotice() << file.path()
                      << " | F: " << file.isFile()
                      << " | D: " << file.isDirectory()
                      << "\n";
    }

}

//--------------------------------------------------------------
void ofApp::update(){
}

//--------------------------------------------------------------
void ofApp::draw(){
}
