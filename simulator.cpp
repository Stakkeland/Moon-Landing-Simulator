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
		startLander(posUpperRight) {}
   
   // display stuff on the screen
   void display();

   Ground ground;
   Angle a;
   Position posLander;
   Star star;
   Lander lander;
   Thrust thrust;
   Position posText;
   Position startLander;
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
   gout << "Fuel: " << lander.getFuel() << " L? gal?" << endl;
   gout << "Altitude: " << static_cast<int>(lander.getPosition().getY() - ground.getElevation(lander.getPosition())) << " m" << endl;
   gout << "Speed: " << static_cast<int>(lander.getSpeed()) << " m/s" << endl;
   gout.flush();

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

   // Get up to date position of the lander.
   pSimulator->posLander = pSimulator->lander.getPosition();

   Thrust thrust;
   // input from keyboard 
   thrust.set(pUI);

   Acceleration acceleration = pSimulator->lander.input(thrust, GRAVITY); // gravity given at the beginning

   pSimulator->lander.coast(acceleration, TIME); // with this time we can appreciate better the movement


   // Handle crashes and landings.
   if (pSimulator->ground.onPlatform(pSimulator->posLander, 20) == true)
   {
	   pSimulator->lander.land();
	   pSimulator->lander.reset(pSimulator->startLander);
   }

   if (pSimulator->ground.hitGround(pSimulator->posLander, 20) == true)
   {
	   pSimulator->lander.crash();
	   pSimulator->lander.reset(pSimulator->startLander);
   }
	   

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
