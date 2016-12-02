//
// Created by Peter A. Kolski on 02.12.16.
//

#include "VideoFileDetector.h"

vector< string >& bildpeter::VideoFileDetector::getPaths_()
{
    return paths_;
}

void bildpeter::VideoFileDetector::readFiles( string path )
{
    ofDirectory _dirList;

    _dirList.listDir( path );
    _dirList.sort();

    for( auto &dir : _dirList.getFiles() )
    {
        if ( dir.isFile() )
            paths_.push_back( dir.getAbsolutePath() );
    }

    if ( paths_.size() == 0 )
    {
        ofLogError() << logInfo_ << "No file found in " << path;
    }

}

string bildpeter::VideoFileDetector::getPathByIndex( int index )
{
    return paths_[ index ];
}
