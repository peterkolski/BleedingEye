//
// Created by Peter A. Kolski on 29.11.16.
//

#include "VideoSwitch.h"

bool bildpeter::VideoSwitch::grabKey( int key )
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


int bildpeter::VideoSwitch::getIndexBank() const
{
    return indexBank_;
}

int bildpeter::VideoSwitch::getIndexVideo() const
{
    return indexVideo_;
}

void bildpeter::VideoSwitch::setMaps( std::unordered_map< int, int > mapVid, std::unordered_map< int, int > mapBank )
{
    videoKeyMap_ = mapVid;
    bankKeyMap_ = mapBank;
}
