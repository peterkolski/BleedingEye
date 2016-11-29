//
// Created by Peter A. Kolski on 29.11.16.
//

#ifndef BLEEDINGEYE_MIDIMAPPING_H
#define BLEEDINGEYE_MIDIMAPPING_H

#include <vector>
#include <string>

namespace bildpeter
{

class MidiMapping
{
public:
    std::vector< std::string >   midiKeywordsOld =
            {   "networkFade",
                "networkFadeSensor",
                "networkMovement",
                "networkMovementSensor",
                "networkDistCenter",
                "networkDistCenterSensor",
                "networkDistDiff",
                "networkDistDiffSensor",
                "linesFade",
                "linesSpeed",
                "linesSpeedSensor",
                "linesColor",
                "flowFade",
                "flowStrength",
                "flowStrengthSensor",
                "ribbonFade",
                "ribbonSize",
                "videoFaderA",
                "videoFaderB",
                "videoSensorA",
                "videoSensorB",
                "sensitivity",
            };

};

} // namespace bildpeter

#endif //BLEEDINGEYE_MIDIMAPPING_H
