/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once

#define _USE_MATH_DEFINES // for M_PI which is 3.14159
#include <math.h>   
#define TWO_PI 6.28318530718

class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestAngle;
class TestLander;

/************************************
* ANGLE
************************************/
class Angle
{
public:
	friend TestAcceleration;
	friend TestVelocity;
	friend TestAngle;
	friend TestLander;

	// Constructors
	Angle() : radians(0.0) {}
	Angle(const Angle& rhs) : radians(0.0) { radians = rhs.radians; }
	Angle(double degrees) : radians(0.0) { radians = convertToRadians(degrees); }

	// Getters
	double getDegrees() const { return convertToDegrees(radians); }
	double getRadians() const { return radians; }

	// Setters
	void setDegrees(double degrees) { this->radians = normalize(convertToRadians(degrees)); }
	void setRadians(double radians) { this->radians = normalize(radians); }
	void setUp() { radians = 0.0; }
	void setDown() { radians = M_PI; }
	void setRight() { radians = M_PI_2; }
	void setLeft() { radians = M_PI + M_PI_2; }
	void reverse() { radians = M_PI_2 + M_PI; }
	Angle& add(double delta) { radians += normalize(delta); return *this; }

private:
	double normalize(double radians) const;
	double convertToDegrees(double radians) const;
	double convertToRadians(double degrees) const;

	double radians;   // 360 degrees equals 2 PI radians
};


