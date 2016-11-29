//
// Created by Peter A. Kolski on 29.11.16.
//

#include "VideoSwitch.h"

bool bildpeter::VideoSwitch::grabVideoKey( int key )
{
    if ( videoKeyMap_.count( key ) )
    {
        indexVideo_ = videoKeyMap_.at( key );
        return true;
    }

    return false;
}

bool bildpeter::VideoSwitch::grabBankKey( int key )
{
    if ( bankKeyMap_.count( key ) )
    {
        indexBank_ = bankKeyMap_.at( key );
        return true;
    }
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
