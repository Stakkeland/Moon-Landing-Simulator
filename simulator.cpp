/**********************************************************************
 * LAB 06
 * Lunar Lander simulation. This is the Game class and main()
 **********************************************************************/

#include "position.h"    // everything should have a point
#include "acceleration.h"// for ACCELERATION
#include "lander.h"      // for LANDER
#include "star.h"        // for STAR
#include "uiInteract.h"  // for INTERFACE
#include "uiDraw.h"      // for RANDOM and DRAW*
#include "ground.h"      // for GROUND
#include "test.h"        // for the unit tests
#include "thrust.h"      // moving lunar lander
#include <cmath>         // for SQRT
#include <cassert>       // for ASSERT
#include <windows.h>     // for SLEEP
#include <iostream>		 // for SLEEP
#include <iomanip>       // for decimal places
using namespace std;

#define GRAVITY -1.625   // Gravity
#define TIME     0.1     // Time
#define WIDTH  400       // Width
#define HEIGHT 400       // Height

/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : ground(posUpperRight), lander(posUpperRight), posText(20,380), 
		centerText(120, 300) {}
   
   // display stuff on the screen
   void display();

   Ground ground;
   Angle a;
   Position posLander;
   Star star;
   Lander lander;
   Thrust thrust;
   Position posText;
   Position centerText;
};

/**********************************************************
 * DISPLAY
 * Draw on the screen
 **********************************************************/
void Simulator::display()
{
	ogstream gout;

   // draw 50 stars
	for (int i = 0; i < 50; i++)
   {
		star.reset(WIDTH, HEIGHT);
		star.draw(gout);
	}

	// draw the ground
	ground.draw(gout);

	// draw the lander
	lander.draw(thrust, gout);

   // Draw variables on the screen
   gout.setPosition(posText);
   gout << "Fuel: " << lander.getFuel() << " lbs" << endl;
   gout << "Altitude: " << static_cast<int>(ground.getElevation(lander.getPosition())) << " m" << endl;
   gout << "Speed: " << fixed << setprecision(2) << (lander.getSpeed()) << " m/s" << endl;
   gout.flush();

   // Land success
   if (ground.onPlatform(posLander, 20) == true && lander.getSpeed() <= 4.00)
   {
	   lander.land();

	   // Put text on screen
	   gout.setPosition(centerText);
	   gout << "Eagle has landed!" << endl;
	   gout.flush();

   }

   // Crash
   if (ground.hitGround(posLander, 20) == true)
   {
	   lander.crash();

	   // Put text on screen
	   gout.setPosition(centerText);
	   gout << "Houston we have a problem!" << endl;
	   gout.flush();

   }

   // Crash
   if (ground.onPlatform(posLander, 20) == true && lander.getSpeed() >= 4.00)
   {
	   lander.crash();

	   // Put text on screen
	   gout.setPosition(centerText);
	   gout << "Houston we have a problem!" << endl;
	   gout.flush();

   }

}


/*************************************
 * CALLBACK
 * Handle one frame of the simulator
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Simulator * pSimulator = (Simulator *)p;
   ogstream gout;

   // Get up to date position of the lander.
   pSimulator->posLander = pSimulator->lander.getPosition();

   // If the lander touches the ground for any circumstance
   if (pSimulator->lander.isLanded() || pSimulator->lander.isDead()) 
   {
      // Give me the last position and don't update the screen
      pSimulator->display();
      return;
   }

   // input from keyboard 
   Thrust thrust;
   thrust.set(pUI);

   // Add lander flames
   if (pUI->isDown() || pUI->isRight() || pUI->isLeft())
   {
	   gout.drawLanderFlames(pSimulator->posLander, pSimulator->a.getRadians(), thrust.isMain(), thrust.isClock(), thrust.isCounter());
   }

   Acceleration acceleration = pSimulator->lander.input(thrust, GRAVITY); // gravity given at the beginning

   pSimulator->lander.coast(acceleration, TIME); // with this time we can appreciate better the movement

   // draw the game
   pSimulator->display();
}

/*********************************
 * Main is pretty sparse.  Just initialize
 * my LM type and call the display engine.
 * That is all!
 *********************************/
#ifdef _WIN32
#include <windows.h>
int WINAPI WinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ LPSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Run the unit tests
   testRunner();

   
   // Initialize OpenGL
   Position posUpperRight(WIDTH, HEIGHT);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void *) & simulator);

   return 0;
}
