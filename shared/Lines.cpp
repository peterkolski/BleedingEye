//
// Created by Peter A. Kolski on 25.10.16.
//

#include "Lines.h"

namespace bildpeter
{

void Lines::linesSetup()
{
    lines_.setup( 20, 2.0, 3.0, ofGetScreenHeight( ) / 3, ofGetScreenHeight( ) * 2 / 3 );
    lines_.setSpeedFactor( 1.0 );
}

void Lines::linesUpdate( float fade, float speed, float speedSensor, float arm )
{
    linesSensor_ = ( 1 - arm ) * speedSensor;
    lines_.setSpeedFactor( ofClamp( speed - linesSensor_, 0.0, 1.0 ) );
    lines_.setFade( fade );
    lines_.update( );
}

void Lines::linesDraw( float fade, float brightness )
{
    if ( fade ) {
        auto _brightness = 255.0 * brightness;
        auto alpha = 255.0 * fade;
        auto color = ofColor( _brightness, _brightness, _brightness, alpha );

        ofPushStyle( );
        {
            lines_.setColor( color );
            lines_.draw( );
        }
        ofPopStyle( );
    }
}

}