#pragma once

#include "ofMain.h"
#include "util/DirectoryDetector.h"
// -------------------------------------------------------------------
// -------------------------------------------------------------------

/// For midi we need multiple inheritance
class ofApp : public ofBaseApp
{

	public:
		void setup();
		void update();
		void draw();


    ofDirectory                     dirList_;
    bildpeter::DirectoryDetector    dirDetect;
};
