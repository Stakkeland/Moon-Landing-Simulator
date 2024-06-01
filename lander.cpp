/***********************************************************************
 * Source File:
 *    LANDER
 * Author:
 *    Br. Helfrich
 * Summary:
 *    All the information about the lunar lander
 ************************************************************************/

#include "lander.h"
#include "acceleration.h"

 /***************************************************************
  * RESET
  * Reset the lander and its position to start the game over
  ***************************************************************/
void Lander :: reset(const Position & posUpperRight)
{
   // Straight the lander up
   angle.setUp();

   // Random velocity
   velocity.setDX(random(-10.0, -4.0));
   velocity.setDY(random(-2.0, 2.0));

   // The position is at the right side of the screen
   pos.setX(posUpperRight.getX() - 1.0);
   pos.setY(random(posUpperRight.getY() * 0.75, posUpperRight.getY() * 0.95));

   // Status is playing
   status = PLAYING;

   // Always a full tank to start
   fuel = FUEL_MAX; 
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
   gout.drawLander(pos, angle.getRadians()); // Following same as simulator.cpp
   
   if (isFlying() && fuel > 0.0)
   {
      gout.drawLanderFlames(pos, angle.getRadians(),
         thrust.isMain(), thrust.isClock(), thrust.isCounter());
   }
      
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   // Acceleration due to gravity
   Acceleration a;

   // Add gravity
   a.addDDY(gravity);

   // If out of gas
   if (fuel == 0.0)
      return a;

  // Main engines
   if (thrust.isMain())
   {
      // Thrust components
      double power = (LANDER_THRUST / LANDER_WEIGHT);
      a.addDDX(-sin(angle.getRadians()) * power );
      a.addDDY(cos(angle.getRadians()) * power);
      fuel -= FUEL_MAIN_THRUST;
   }

   // Clockwise
   if (thrust.isClock())
   {
      angle.add(0.1); // rotation
      fuel -= FUEL_ROTATE; // Consuming fuel
   }

   // Counter Clockwise
   if (thrust.isCounter())
   {
      angle.add(-0.1); // rotation
      fuel -= FUEL_ROTATE; // Consuming fuel
   }

   if (fuel < 0.0)
      fuel = 0.0;
   
   return a;
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   // Update position
   pos.add(acceleration, velocity, time);

   // update velocity
   velocity.add(acceleration, time);

   
}
