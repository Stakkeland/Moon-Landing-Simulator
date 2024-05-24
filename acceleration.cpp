/***********************************************************************
 * Source File:
 *    ACCELERATION
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about changing speed
 ************************************************************************/

#include "acceleration.h"
#include "angle.h"

#include <cmath>

 /*********************************************
  * ACCELERATION : ADD
  *  a += a
  *********************************************/
void Acceleration::add(const Acceleration& acceleration)
{
	ddx = ddx + acceleration.ddx;
	ddy = ddy + acceleration.ddy;
}

/*********************************************
 * ACCELERATION : SET
 *  set from angle and direction
 *********************************************/
void Acceleration::set(const Angle& angle, double magnitude)
{
	// Assuming what is entering are degrees
	double degrees = angle.getDegrees();
	double radians = degrees / 360.0 * TWO_PI;

	// Making that 0.0 degrees is up, and so on
	radians = M_PI / 2.0 - radians;

	// setting up the acceleration for both components
	setDDX(magnitude * cos(radians));
	setDDY(magnitude * sin(radians));
}