/***********************************************************************
 * Source File:
 *    VELOCITY
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about speed
 ************************************************************************/

#include "velocity.h"
#include "acceleration.h"
#include "angle.h"

#include <math.h>  // for sqrt()

 /*********************************************
  * VELOCITY : ADD
  *  v = v_0 + a t
  *********************************************/
void Velocity::add(const Acceleration& acceleration, double time)
{
	setDX(dx + (acceleration.getDDX() * time));
	setDY(dy + (acceleration.getDDY() * time));
}

/*********************************************
 * VELOCITY : GET SPEED
 *  find the magnitude of velocity
 *********************************************/
double Velocity::getSpeed() const
{
	return sqrt(dx * dx + dy * dy);
}

/*********************************************
 * VELOCITY : SET
 *  set from angle and direction
 *********************************************/
void Velocity::set(const Angle& angle, double magnitude)
{
	double degrees = angle.getDegrees();
	double radians = degrees / 360.0 * TWO_PI;

	// Making that 0.0 degrees is up, and so on
	radians = M_PI / 2.0 - radians;

	setDX(magnitude * cos(radians));
	setDY(magnitude * sin(radians));
}
