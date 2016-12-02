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
        bankDir_.readDirectories( rootPath );
        // --- init entries according to folder, so the keys are assigned right
        videoPathsVec_ = decltype( videoPathsVec_ )( bankDir_.getPathsAmount() );

        for ( int i = 0; i < bankDir_.getPathsAmount(); ++i )
        {
            videoPathsVec_.at( i ).readFiles( bankDir_.getPathByIndex( i ) );
        }

        // TODO first video should be started (search for one)
        loadFromIndex( bankIndexCurrent_, videoIndexCurrent_);

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
        if ( videoIndexCurrent_ >= videoPathsVec_[ bankIndexCurrent_ ].getPathsAmount() ) {
            videoIndexCurrent_ = 0;
            ofLogVerbose() << logInfo_ << "Last video";
        }
        else
        {
            videoIndexCurrent_++;
            ofLogVerbose() << logInfo_ << "Next video";
        }

        loadFromIndex( bankIndexCurrent_, videoIndexCurrent_ );
        playIfItShould( );
    }

// --------------------------------------------------------------------------------------

/// Switching to other video for playing
/// \param index Of the video in the folder (starts with 0)
/// \return     true if video is loaded
bool VideoDirectoryPlayer::setVideoByIndex( int index )
{
    if ( index < videoPathsVec_.at( bankIndexCurrent_ ).getPathsAmount()  )
    {
        if ( videoIndexCurrent_ != index )
        {
            videoIndexCurrent_ = index;
            loadFromIndex( bankIndexCurrent_, videoIndexCurrent_ );
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
    //TODO this should be better designed
    // --- check if bank exists
    if ( index < videoPathsVec_.size() )
    {
        bankIndexCurrent_ = index;

        // --- check if video exists
        if ( videoIndexCurrent_ < videoPathsVec_.at( bankIndexCurrent_ ).getPathsAmount() )
        {
            loadFromIndex( bankIndexCurrent_, videoIndexCurrent_ ); //TODO shouldnt be reLoaded when the same button is pressed
            playIfItShould();
            return true;
        }
        else
        {
            ofLogVerbose() << logInfo_  << "No video with index " << videoIndexCurrent_
                                        << " in bank " << bankIndexCurrent_;
            return false;
        }
    }
    else
    {
        ofLogVerbose() << logInfo_  << "No bank with index " << index;
        return false;
    }
}

void VideoDirectoryPlayer::loadFromIndex( int indexBank, int indexVideo )
{

    string _pathCurrent = videoPathsVec_.at( indexBank ).getPathByIndex( indexVideo );
    videoPlayer_.load( _pathCurrent );    //TODO Does it have to load each time?
    planeWithVideo_.mapTexCoords( 0, 0, videoPlayer_.getWidth(), videoPlayer_.getHeight() );

    ofLogVerbose() << logInfo_
                    << " Bank_" << indexBank
                    << " Video_" << indexVideo
                    << " Video path " << _pathCurrent;
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

bool VideoDirectoryPlayer::isPlaying()
{
    return isPlaying_;
}

void VideoDirectoryPlayer::setPaused( bool pause )
{
    isPlaying_ = false;
    videoPlayer_.setPaused( pause );
}


// --------------------------------------------------------------------------------------
    
    
}   // namespace bildpeter