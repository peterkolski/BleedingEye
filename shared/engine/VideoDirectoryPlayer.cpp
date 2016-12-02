//
//  videoDirectory.cpp
//  Video
//
//  Created by Peter A. Kolski on 12.04.16.
//
//

#include "VideoDirectoryPlayer.hpp"


namespace bildpeter {

    
    void VideoDirectoryPlayer::loadDirectory( string rootPath )
    {
        // --- Banks
        bankDir_.readDirectories( rootPath );
        // init entries according to folder, so the keys are assigned right
        videoPathsVec_ = decltype( videoPathsVec_ )( bankDir_.getPathsAmount() );

        for ( int i = 0; i < bankDir_.getPathsAmount(); ++i )
        {
            videoPathsVec_[ i ].readFiles( bankDir_.getPathByIndex( i ) );
        }


        // --- Videos
        directoryList_.listDir( rootPath );
        directoryList_.sort();
        if ( directoryList_.getFiles().size() )
        {
            videoIndexCurrent_  = 0;
            videoIndexMax_      = directoryList_.getFiles().size() - 1;
            loadFromIndex( videoIndexCurrent_ );

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

/// Switching to other video for playing
/// \param index Of the video in the folder (starts with 0)
/// \return     true if video is loaded
bool VideoDirectoryPlayer::setVideoByIndex( int index )
{
    if ( index <= videoIndexMax_  )
    {
        if ( videoIndexCurrent_ != index )
        {
            videoIndexCurrent_ = index;
            loadFromIndex( videoIndexCurrent_ );
            playIfItShould( );
        }
        return true;
    }
    else
    {
        ofLogVerbose() << logInfo_  << "No video with index " << index;
        return false;
    }
}

// --------------------------------------------------------------------------------------

/// Switching to other video-bank (folder with videos)
/// \param index Of the video-bank of folders (starts with 0)
/// \return     true if bank is loaded
bool VideoDirectoryPlayer::setBankByIndex( int index )
{
    if ( index <= bankIndexMax_  )
    {
        if ( bankIndexCurrent_ != index )
        {
            //TODO implement
        }
        ofLogError( ) << logInfo_ << "Not implemented";
        return true;
    }
    else
    {
        ofLogVerbose() << logInfo_  << "No bank with index " << index;
        return false;
    }
}

void VideoDirectoryPlayer::loadFromIndex( int index )
{
    videoPlayer_.load( directoryList_.getFiles()[ index ].path() );    //TODO Does it have to load each time?
    planeWithVideo_.mapTexCoords( 0, 0, videoPlayer_.getWidth(), videoPlayer_.getHeight() ); // TODO should be called with every switch

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