//------------------------------------------------------------------------
//
// Name: Main.cpp
//
// Desc: Calls and updates the game instance
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Main.hpp"

// Global Seed Value
uint32 seed = 0;

int main(int narg, char *argv[])
{
	bool status = true;

	// Startup the Engine
	engine->Startup(narg, argv);

	// Loop through a few Update calls
	while(status && !TCODConsole::isWindowClosed())
	{
		// Update the Engine
		status = engine->Update();

		// Render using the Engine
		engine->Render();

		// Flush Updates to Console
		TCODConsole::root->flush();
	}

	// Shutdown the Engine
	engine->Shutdown();

	return 0;
}
