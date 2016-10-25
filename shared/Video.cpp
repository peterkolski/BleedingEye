//
// Created by Peter A. Kolski on 25.10.16.
//

#include "ofApp.h"
#include "Video.h"

namespace bildpeter
{
void Video::videoSetup( string pathA, string pathB )
{
    videoA.loadDirectory( pathA );
    videoB.loadDirectory( pathB );
    videoA.play();
    videoB.play();
}

void Video::videoUpdate( float faderA, float faderB, float sensorA, float sensorB, float arm, float back )
{
    videoASensor        = ( 1 - arm ) * sensorA;
    videoBSensor        = ( 1 - back ) * sensorB;

    if ( faderA )
    {
        if ( !videoA.videoPlayer_.isPlaying() ) { videoA.videoPlayer_.play(); }
        videoA.update();
        videoA.fade( ofClamp( faderA - videoASensor, 0.0, 1.0 ) * 255 );
    }
    else    { videoA.videoPlayer_.setPaused( true ); }

    if ( faderB ) {
        if ( !videoB.videoPlayer_.isPlaying() ) { videoB.videoPlayer_.play(); }
        videoB.update();
        videoB.fade( ofClamp( faderB - videoBSensor, 0.0, 1.0 ) * 255 );
    }
    else    { videoB.videoPlayer_.setPaused( true ); }
}

void Video::videoDraw( float videoFaderA, float videoFaderB )
{
    auto x = ofGetWidth() / 2;
    auto y = ofGetHeight() / 2;
    auto z = -2000;
    // macbookAir
    auto w = 5120;
    auto h = 3200;

    if ( videoFaderA ) videoA.draw( x, y, z, w, h );
    if ( videoFaderB ) videoB.draw( x, y, z, w, h );
}

void Video::videoNext()
{
    videoA.nextVideo();
    videoB.nextVideo();
}

} // namespace bildpeter