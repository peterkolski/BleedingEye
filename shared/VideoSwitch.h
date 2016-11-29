//
// Created by Peter A. Kolski on 29.11.16.
//

#ifndef BLEEDINGEYE_VIDEOSWITCH_H
#define BLEEDINGEYE_VIDEOSWITCH_H

#include <map>
#include <vector>

namespace bildpeter
{
class VideoSwitch
{
public:
    bool grabVideoKey( int key );
    bool grabBankKey( int key );

    int getIndexVideo() const;
    int getIndexBank() const;


private:
    int indexVideo  = 0;
    int indexBank   = 0;

    std::map< int, int > videoMap = { {1,1}, {2,2}, {3,3}, {4,4}, {5,5}, {6,6}, {7,7}, {8,8}, {9,9}, {0,0} };
//    std::vector< int > bankMap  = { 'Q', 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O' };
};
} // namespace bildpeter


#endif //BLEEDINGEYE_VIDEOSWITCH_H
