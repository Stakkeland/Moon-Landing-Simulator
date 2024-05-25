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


/*************************************************************************
 * SIMULATOR
 * Everything pertaining to the simulator.
 *************************************************************************/
class Simulator
{
public:
   Simulator(const Position & posUpperRight) : ground(posUpperRight), lander(posUpperRight) {}
   
   // display stuff on the screen
   void display();

   Ground ground;
   Angle a;
   Position posLander;
   Star star;
   Lander lander;
   Thrust thrust;
};

/**********************************************************
 * DISPLAY
 * Draw on the screen
 **********************************************************/
void Simulator::display()
{
	ogstream gout;

	// draw 50 stars
	for (int i = 0; i < 50; i++) {
		star.reset(0.0, 0.0);
		star.draw(gout);
	}

	// draw the ground
	ground.draw(gout);

	// draw the lander
	lander.draw(thrust, gout);

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

   /*ogstream gout;*/
   Thrust thrust;
   // input from keyboard 
   thrust.set(pUI);

   // draw the ground
   //pSimulator->ground.draw(gout);

   Acceleration acceleration = pSimulator->lander.input(thrust, -1.625); // ups I don't know what to put in gravity but that is the number in our first exercise
   pSimulator->lander.coast(acceleration, 0.1); // ups with the time too...


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
   Position posUpperRight(400, 400);
   Interface ui("Lunar Lander", posUpperRight);

   // Initialize the game class
   Simulator simulator(posUpperRight);

   // set everything into action
   ui.run(callBack, (void *)&simulator);

   return 0;
}
