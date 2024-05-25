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
   angle.setUp();
   status = PLAYING; 
   fuel = 5000.0;
   velocity.setDX(random(-10.0, -4.0));
   velocity.setDY(random(-2.0, 2.0));
   pos.setX(posUpperRight.getX() - 1.0);
   pos.setY(random(posUpperRight.getY() * 0.75, posUpperRight.getY() * 0.95));
}

/***************************************************************
 * DRAW
 * Draw the lander on the screen
 ***************************************************************/
void Lander :: draw(const Thrust & thrust, ogstream & gout) const
{
   gout.drawLander(pos, angle.getRadians()); // Following same as simulator.cpp
   
   if (thrust.isMain())
   {
      gout.drawLanderFlames(pos, angle.getRadians(), true, false, false);
   }
   else if (thrust.isClock())
   {
      gout.drawLanderFlames(pos, angle.getRadians(), false, true, false);
   }
   else if (thrust.isCounter())
   {
      gout.drawLanderFlames(pos, angle.getRadians(), false, false, true);
   }
}

/***************************************************************
 * INPUT
 * Accept input from the Neil Armstrong
 ***************************************************************/
Acceleration Lander :: input(const Thrust& thrust, double gravity)
{
   double ddx = 0.0;
   double ddy = gravity;

   if (fuel > 0)
   {
      if (thrust.isMain())
      {
         // Thrust components
         double thrustMagnitude = thrust.mainEngineThrust();
         ddx -= thrustMagnitude * sin(angle.getRadians());
         ddy += thrustMagnitude * cos(angle.getRadians());
         fuel -= 10.0; // Consuming fuel
      }
      if (thrust.isClock() && fuel > 0)
      {
         angle.setRadians(angle.getRadians() + 0.1); // rotation
         fuel -= 1.0; // Consuming fuel
      }
      if (thrust.isCounter() && fuel > 0)
      {
         angle.setRadians(angle.getRadians() - 0.1); // rotation
         fuel -= 1.0; // Consuming fuel
      }
   }

   // Return the new acceleration
   return Acceleration(ddx, ddy);
}

/******************************************************************
 * COAST
 * What happens when we coast?
 *******************************************************************/
void Lander :: coast(Acceleration & acceleration, double time)
{
   // update through velocity and acceleration
   pos.addX(velocity.getDX() * time + 0.5 * acceleration.getDDX() * time * time);
   pos.addY(velocity.getDY() * time + 0.5 * acceleration.getDDY() * time * time);

   // Update through acceleration
   velocity.addDX(acceleration.getDDX() * time);
   velocity.addDY(acceleration.getDDY() * time);
}
