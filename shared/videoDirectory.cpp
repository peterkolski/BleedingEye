//
//  videoDirectory.cpp
//  Video
//
//  Created by Peter A. Kolski on 12.04.16.
//
//

#include "videoDirectory.hpp"


namespace bildpeter {

    
    void VideoDirectoryPlayer::loadDirectory( string _path )
    {
        directoryList_.listDir( _path );
        directoryList_.sort();
        if ( directoryList_.getFiles().size() )
        {
            videoIndexCurrent_  = 0;
            videoIndexMax_      = directoryList_.getFiles().size() - 1;
            videoPlayer_.load( directoryList_.getFiles()[ videoIndexCurrent_ ].path() );
            
            // --- Logging
            ofLogVerbose()  << "File paths: " << directoryList_.getFiles().size();
            for ( auto &file : directoryList_.getFiles() )
            {
                ofLogVerbose() << file.path();
            }
            
            planeWithVideo_.mapTexCoords( 0, 0, videoPlayer_.getWidth(), videoPlayer_.getHeight() );

        }
        else
        {
            ofLogError() << "No files in directory";
        }
    }
    
    // --------------------------------------------------------------------------------------
    
    void VideoDirectoryPlayer::update()
    {
        videoPlayer_.update();
    }

    // --------------------------------------------------------------------------------------
    
    void VideoDirectoryPlayer::draw( float x, float y, float w, float h )
    {
        ofPushStyle();
        {
            ofSetColor( fadeColor_ );
            videoPlayer_.draw( x, y, w, h );
        }
        ofPopStyle();
    }

    // --------------------------------------------------------------------------------------
    
    void VideoDirectoryPlayer::draw( float x, float y, float z, float w, float h )
    {
        planeWithVideo_.set( w, h );
        planeWithVideo_.setPosition( x, y, z );
        ofPushStyle();
        {
            ofSetColor( fadeColor_ );
            videoPlayer_.getTexture().bind();
            planeWithVideo_.draw();
            videoPlayer_.getTexture().unbind();
        }
        ofPopStyle();
    }
    
    // --------------------------------------------------------------------------------------
    
    void VideoDirectoryPlayer::nextVideo()
    {
        auto isPlaying  = videoPlayer_.isPlaying();
        
        if ( videoIndexCurrent_ >= videoIndexMax_ ) {
            videoIndexCurrent_ = 0;
            ofLogVerbose() << "Last video";
        }
        else
        {
            videoIndexCurrent_++;
            ofLogVerbose() << "Next video";
        }
        
        videoPlayer_.load( directoryList_.getFiles()[ videoIndexCurrent_ ].path() );
        if (isPlaying) {
            videoPlayer_.play();
        }
        
        planeWithVideo_.mapTexCoords( 0, 0, videoPlayer_.getWidth(), videoPlayer_.getHeight() );
    }

bool VideoDirectoryPlayer::setVideoByIndex( int index )
{
    return false;
}

// --------------------------------------------------------------------------------------
    
    
}   // namespace bildpeter