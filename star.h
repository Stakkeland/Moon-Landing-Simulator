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

    // Member function to reset the star's position and phase
    void reset(double width, double height) {
        
    }

    void draw(ogstream& gout) const {
        
    }

private:
	unsigned char phase;
	Position pos;
};
