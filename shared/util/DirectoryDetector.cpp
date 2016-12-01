//
// Created by Peter A. Kolski on 01.12.16.
//

#include "DirectoryDetector.h"

void bildpeter::DirectoryDetector::readDirectories( string path )
{
    dirList_.listDir( path );
    dirList_.sort();

    for( auto &dir : dirList_.getFiles() )
    {
        if ( dir.isDirectory() )
            paths_.push_back( dir.getAbsolutePath() );
    }

}
