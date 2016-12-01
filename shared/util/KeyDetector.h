//
// Created by Peter A. Kolski on 29.11.16.
//

#ifndef BLEEDINGEYE_KEYDETECTOR_H
#define BLEEDINGEYE_KEYDETECTOR_H

#include <unordered_map>
#include <vector>
#include <algorithm>

namespace bildpeter
{
class KeyDetector
{
public:
    void setVideoMap( std::unordered_map< int, int > map )    { videoKeyMap_ = map; }
    void setBankMap( std::unordered_map< int, int > map )     { bankKeyMap_  = map; }
    void setMaps( std::unordered_map< int, int > mapVid, std::unordered_map< int, int > mapBank );
    bool grabKey( int key );

    int getIndexVideo() const;
    int getIndexBank() const;


private:
    int indexVideo_  = 0;
    int indexBank_   = 0;

    std::unordered_map< int, int >   videoKeyMap_ =
            {
                    {'1', 0 },
                    {'2', 1 },
                    {'3', 2 },
                    {'4', 3 },
                    {'5', 4 },
                    {'6', 5 },
                    {'7', 6 },
                    {'8', 7 },
                    {'9', 8 },
                    {'0', 9 },
            };
    std::unordered_map< int, int >   bankKeyMap_  =
            {
                    {'Q', 0 },
                    {'W', 1 },
                    {'E', 2 },
                    {'R', 3 },
                    {'T', 4 },
                    {'Z', 5 },
                    {'U', 6 },
                    {'I', 7 },
                    {'O', 8 },
                    {'P', 9 }
            };
};
} // namespace bildpeter


#endif //BLEEDINGEYE_VIDEOSWITCH_H
