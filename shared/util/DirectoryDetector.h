//
// Created by Peter A. Kolski on 01.12.16.
//

#ifndef BLEEDINGEYE_DIRECTORYDETECTOR_H
#define BLEEDINGEYE_DIRECTORYDETECTOR_H

#include "ofMain.h"

namespace bildpeter
{
class DirectoryDetector
{
public:
    void    readDirectories( string path );

    int                     getPathsAmount()    { return paths_.size(); }
    std::vector< string >   getPaths()          { return paths_; }

private:
    ofDirectory             dirList_;
    std::vector< string >   paths_;
};
} // namespace bildpeter


#endif //BLEEDINGEYE_DIRECTORYDETECTOR_H
