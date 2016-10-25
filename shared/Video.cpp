//
// Created by Peter A. Kolski on 25.10.16.
//

#include "Video.h"

namespace bildpeter
{
void Video::setup( string pathA, string pathB )
{
    videoA.loadDirectory( pathA );
    videoB.loadDirectory( pathB );
    videoA.play();
    videoB.play();
}

void Video::update( float faderA, float faderB, float sensorA, float sensorB, float arm, float back )
{
    sensorValA        = ( 1 - arm ) * sensorA;
    sensorValB        = ( 1 - back ) * sensorB;

    if ( faderA )
    {
        if ( !videoA.videoPlayer_.isPlaying() ) { videoA.videoPlayer_.play(); }
        videoA.update();
        videoA.fade( ofClamp( faderA - sensorValA, 0.0, 1.0 ) * 255 );
    }
    else    { videoA.videoPlayer_.setPaused( true ); }

    if ( faderB ) {
        if ( !videoB.videoPlayer_.isPlaying() ) { videoB.videoPlayer_.play(); }
        videoB.update();
        videoB.fade( ofClamp( faderB - sensorValB, 0.0, 1.0 ) * 255 );
    }
    else    { videoB.videoPlayer_.setPaused( true ); }
}

void Video::draw( float faderA, float faderB )
{
    auto x = ofGetWidth() / 2;
    auto y = ofGetHeight() / 2;
    auto z = -2000;
    // macbookAir
    auto w = 5120;
    auto h = 3200;

    if ( faderA ) videoA.draw( x, y, z, w, h );
    if ( faderB ) videoB.draw( x, y, z, w, h );
}

void Video::next()
{
    videoA.nextVideo();
    videoB.nextVideo();
}

} // namespace bildpeter