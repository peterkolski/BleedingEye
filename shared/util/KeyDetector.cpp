//
// Created by Peter A. Kolski on 29.11.16.
//

#include "KeyDetector.h"

bool bildpeter::KeyDetector::grabKey( int key )
{
    if ( videoKeyMap_.count( key ) )
    {
        indexVideo_ = videoKeyMap_.at( key );
        return true;
    }
    else if ( bankKeyMap_.count( key ) )
    {
        indexBank_ = bankKeyMap_.at( key );
        return true;
    }
    else
        return false;
}


int bildpeter::KeyDetector::getIndexBank() const
{
    return indexBank_;
}

int bildpeter::KeyDetector::getIndexVideo() const
{
    return indexVideo_;
}

void bildpeter::KeyDetector::setMaps( std::unordered_map< int, int > mapVid, std::unordered_map< int, int > mapBank )
{
    videoKeyMap_ = mapVid;
    bankKeyMap_ = mapBank;
}
