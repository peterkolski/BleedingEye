//
// Created by Peter A. Kolski on 25.10.16.
//

#include "ofApp.h"
#include "Lines.h"

void Lines::linesSetup()
{
    lines.setup( 20, 2.0, 3.0, ofGetScreenHeight() / 3, ofGetScreenHeight() * 2 / 3 );
    lines.setSpeedFactor( 1.0 );
}

void Lines::linesUpdate( float fade, float speed, float speedSensor, float arm )
{
    linesSensor         = ( 1 - arm ) * speedSensor;
    lines.setSpeedFactor( ofClamp( speed - linesSensor, 0.0, 1.0 ) );
    lines.setFade( fade );
    lines.update();
}

void Lines::linesDraw( float fade, float brightness )
{
    if ( fade )
    {
        auto brightness = 255.0 * brightness;
        auto alpha      = 255.0 * fade;
        auto color      = ofColor(brightness, brightness, brightness, alpha );
        
        ofPushStyle();
        {
            lines.setColor( color );
            lines.draw();
        }
        ofPopStyle();
    }
}