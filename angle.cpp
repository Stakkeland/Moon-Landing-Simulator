/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

/************************************
* ANGLE : NORMALIZE
************************************/
double Angle::normalize(double radians) const
{
	// Adjust the angle for values less than 0 or greater than or equal to 2*PI
	if (radians < 0.0)
	{
		// Add 2*PI until the angle is greater than 0
		double multiples = ceil(-radians / TWO_PI);
		return TWO_PI * multiples + radians;
	}
	else if (radians >= TWO_PI)
	{
		// Subtract 2*PI until the angle is less than 2*PI
		double multiples = floor(radians / TWO_PI);
		return radians - (TWO_PI * multiples);
	}

	return radians;
}

/*****************************************
* ANGLE : CONVERT FROM RADIANS TO DEGREES
*     degrees = radians / 2pi * 360
******************************************/
double Angle::convertToDegrees(double radians) const
{
	return normalize(radians) / TWO_PI * 360.0;
}

/*****************************************
* ANGLE : CONVERT FROM DEGREES TO RADIANS
*     radians = degrees / 360 * 2pi
******************************************/
double Angle::convertToRadians(double degrees) const
{
	return normalize(degrees / 360.0 * TWO_PI);
}








