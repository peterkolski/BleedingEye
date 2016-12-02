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

    if ( paths_.size() == 0 )
    {
        ofLogError() << logInfo_ << "No directory found in " << path;
    }
}

string bildpeter::DirectoryDetector::getPathByIndex( int index )
{
    return paths_.at( index );
}
