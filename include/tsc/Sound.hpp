#ifndef SOUND_HPP
#define SOUND_HPP
//------------------------------------------------------------------------
//
// Name: Sound.hpp
//
// Desc: A class to implement a Sound
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Module.hpp"
#include "StateManager.hpp"
#include "SoundStates.hpp"

class Sound : public Module
{
private:

	// Copy constructor and assignment should be private
	Sound(const Sound&);
	Sound &operator=(const Sound&);

public:

	// An instance of the State Manager class
	StateManager<Sound> *stateMgr;

	// The Sound Constructor
	Sound()
	{
		// Set up the State Manager
		stateMgr = new StateManager<Sound>(this);
		stateMgr->SetCurrentState(SoundMainMenuState);
	}

	// The Sound Destructor
	virtual ~Sound()
	{
		if( stateMgr != NULL )
		{
			delete stateMgr;
			stateMgr = NULL;
		}
	}

	// Update the Sound
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
	{
		return stateMgr->Update(elapsed, key, mouse);
	}

	// Render the Sound
	void Render()
	{
		stateMgr->Render();
	}

	// Handle Messages for the Sound
	bool Receive(const Message &msg)
	{
		return stateMgr->Receive(msg);
	}
};

#endif