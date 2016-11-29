//
// Created by Peter A. Kolski on 29.11.16.
//

#ifndef BLEEDINGEYE_VIDEOSWITCH_H
#define BLEEDINGEYE_VIDEOSWITCH_H

#include <unordered_map>
#include <vector>
#include <algorithm>

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

    std::unordered_map< int, int >   videoKeyMap =
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
//    std::map< int, int > bankMap  = { {'Q',0}, 'W', 'E', 'R', 'T', 'Z', 'U', 'I', 'O' };
};
} // namespace bildpeter


#endif //BLEEDINGEYE_VIDEOSWITCH_H
