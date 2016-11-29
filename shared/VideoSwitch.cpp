//
// Created by Peter A. Kolski on 29.11.16.
//

#include "VideoSwitch.h"

bool bildpeter::VideoSwitch::grabVideoKey( int key )
{
    if ( videoKeyMap.count( key ) )
    {
        indexVideo = videoKeyMap.at( key );
        return true;
    }

    return false;
}

bool bildpeter::VideoSwitch::grabBankKey( int key )
{
    if ( bankKeyMap.count( key ) )
    {
        indexBank = bankKeyMap.at( key );
        return true;
    }
    return false;
}


int bildpeter::VideoSwitch::getIndexBank() const
{
    return indexBank;
}

int bildpeter::VideoSwitch::getIndexVideo() const
{
    return indexVideo;
}
