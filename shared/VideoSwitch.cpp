//
// Created by Peter A. Kolski on 29.11.16.
//

#include "VideoSwitch.h"

bool bildpeter::VideoSwitch::grabVideoKey( int key )
{
    if ( videoMap.count( key ) )
    {
        indexVideo = videoMap.at( key );
        return true;
    }

    return false;
}

bool bildpeter::VideoSwitch::grabBankKey( int key )
{
    if ( bank ) {}
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
