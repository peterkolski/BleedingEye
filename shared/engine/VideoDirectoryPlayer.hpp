//
//  videoDirectory.hpp
//  Video
//
//  Created by Peter A. Kolski on 12.04.16.
//
//

#ifndef videoDirectory_hpp
#define videoDirectory_hpp

#include <stdio.h>
#include "ofMain.h"
#include "util/DirectoryDetector.h"
#include "util/VideoFileDetector.h"

namespace bildpeter {

class VideoDirectoryPlayer {
public:
    VideoDirectoryPlayer()  {};
    ~VideoDirectoryPlayer() {};
    VideoDirectoryPlayer( string _path )    { loadDirectory( _path ); }

    void    loadDirectory( string rootPath );
    void    nextVideo();
    bool    setVideoByIndex( int index );
    bool    setBankByIndex( int index );
    void    update();
    void    play();
    void    stop();
    void    draw( float x, float y, float w, float h );
    void    draw( float x, float y, float z, float w, float h );
    void    fade( float alpha )             { fadeColor_ = ofColor( ofColor::white, alpha ); }

private:
    void loadFromIndex( int indexBank, int indexVideo );
    void playIfItShould();

    string              logInfo_ = "VideoDirectory | ";
    ofVideoPlayer       videoPlayer_;
    DirectoryDetector   bankDir_;
    std::vector< bildpeter::VideoFileDetector > videoPathsVec_;
    ofPlanePrimitive    planeWithVideo_;

    int                 videoIndexCurrent_  = 0;    // TODO replace with iterators
    int                 bankIndexCurrent_   = 0;
    bool                isPlaying_          = false;
    ofColor             fadeColor_          = ofColor::white;

};
    
}   // namespace bildpeter

#endif /* videoDirectory_hpp */
