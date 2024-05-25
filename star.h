/***********************************************************************
 * Header File:
 *    STAR
 * Author:
 *    Br. Helfrich
 * Summary:
 *    A single star that twinkles
 ************************************************************************/

#pragma once
#include "position.h"   // for POSITION
#include "uiDraw.h"     // for RANDOM and DRAWSTAR

/*****************************************************
 * STAR
 * A star that twinkles
 *****************************************************/
class Star
{
public:
    // Constructor
    Star() : phase(0) {} // Initializes phase to 0

    // Method to reset the star's position 
    void reset(double width, double height) {
        pos.setX(random(0, 400));
        pos.setY(random(0, 400));
    }

    void draw(ogstream& gout) {
        phase += 1;
        gout.drawStar(pos, phase);
    }

private:
	unsigned char phase;
	Position pos;
};
