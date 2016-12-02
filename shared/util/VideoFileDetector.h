//
// Created by Peter A. Kolski on 02.12.16.
//

#ifndef BLEEDINGEYE_VIDEOFILEDETECTOR_H
#define BLEEDINGEYE_VIDEOFILEDETECTOR_H

#include "ofMain.h"

namespace bildpeter
{

class VideoFileDetector
{
public:
    void findFiles( string path );

private:
    string                  logInfo_ = "VideoFileDetector | ";
    std::vector< string >   paths_;

};

} // namespace bildpeter


#endif //BLEEDINGEYE_VIDEOFILEDETECTOR_H
