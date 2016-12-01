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

namespace bildpeter {

class VideoDirectoryPlayer {
public:
    VideoDirectoryPlayer()  {};
    ~VideoDirectoryPlayer() {};
    VideoDirectoryPlayer( string _path )    { loadDirectory( _path ); }

    void    loadDirectory( string _path );
    void    nextVideo();
    bool    setVideoByIndex( int index );
    bool    setBankByIndex( int index );
    void    update();
    void    play();
    void    stop();
    void    draw( float x, float y, float w, float h );
    void    draw( float x, float y, float z, float w, float h );

    void    fade( float alpha )             { fadeColor_ = ofColor( ofColor::white, alpha ); }

    ofVideoPlayer       videoPlayer_;

private:
    void loadFromIndex( int index );
    void playIfItShould();

    string              logInfo_ = "VideoDirectory | ";
    ofDirectory         directoryList_;
    ofPlanePrimitive    planeWithVideo_;
    int                 videoIndexCurrent_  = 0;    // TODO replace with iterators
    int                 videoIndexMax_      = -1;
    int                 bankIndexCurrent_   = 0;
    int                 bankIndexMax_       = -1;

    bool                isPlaying_          = false;

    ofColor             fadeColor_          = ofColor::white;

};
    
}   // namespace bildpeter

#endif /* videoDirectory_hpp */
