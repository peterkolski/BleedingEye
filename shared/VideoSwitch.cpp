//
// Created by Peter A. Kolski on 29.11.16.
//

#include "VideoSwitch.h"

bool bildpeter::VideoSwitch::grabVideoKey( int key )
{

    return false;
}

bool bildpeter::VideoSwitch::grabBankKey( int key )
{

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
