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
            loadFromIndex( videoIndexCurrent_ );

            ofLogVerbose()  << logInfo_ << "File paths amount: " << directoryList_.getFiles().size();

            for ( auto &file : directoryList_.getFiles() )
            {
                ofLogVerbose() << logInfo_<< file.path();
            }
            
            planeWithVideo_.mapTexCoords( 0, 0, videoPlayer_.getWidth(), videoPlayer_.getHeight() );

        }
        else
        {
            ofLogError() << logInfo_ << "No files in directory";
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
        if ( videoIndexCurrent_ >= videoIndexMax_ ) {
            videoIndexCurrent_ = 0;
            ofLogVerbose() << logInfo_ << "Last video";
        }
        else
        {
            videoIndexCurrent_++;
            ofLogVerbose() << logInfo_ << "Next video";
        }

        loadFromIndex( videoIndexCurrent_ );

        playIfItShould( );
        
        planeWithVideo_.mapTexCoords( 0, 0, videoPlayer_.getWidth(), videoPlayer_.getHeight() );
    }

// --------------------------------------------------------------------------------------

///
/// \param index Of the video in the folder (starts with 0)
/// \return     true if video is loaded
bool VideoDirectoryPlayer::setVideoByIndex( int index )
{
    if ( index <= videoIndexMax_ )
    {
        videoIndexCurrent_ = index;

        loadFromIndex( videoIndexCurrent_ );

        playIfItShould( );

        return true;
    }
    else
    {
        ofLogVerbose() << logInfo_  << "No video with index " << index;
        return false;
    }
}

void VideoDirectoryPlayer::loadFromIndex( int index )
{
    videoPlayer_.load( directoryList_.getFiles()[ index ].path() );    //TODO Does it have to load each time?

    ofLogVerbose() << logInfo_  << "Video index set to " << videoIndexCurrent_;
}

void VideoDirectoryPlayer::playIfItShould()
{
    if ( isPlaying_ && !( videoPlayer_.isPlaying( ) ) ) {
            videoPlayer_.play();
        }
}

void VideoDirectoryPlayer::play()
{
    isPlaying_ = true;
    if ( !videoPlayer_.isPlaying() )
    {
        videoPlayer_.play();
        ofLogVerbose() << logInfo_  << "Play video";
    }
}

void VideoDirectoryPlayer::stop()
{
    isPlaying_ = false;
    if ( videoPlayer_.isPlaying() )
    {
        videoPlayer_.stop();
        ofLogVerbose() << logInfo_  << "Stop video";
    }
}


// --------------------------------------------------------------------------------------
    
    
}   // namespace bildpeter