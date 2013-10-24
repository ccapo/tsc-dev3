#ifndef GAME_HPP
#define GAME_HPP
//------------------------------------------------------------------------
//
// Name: Game.hpp
//
// Desc: A class to implement a Game
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Module.hpp"
#include "StateManager.hpp"
#include "GameStates.hpp"

class Game : public Module
{
private:

	// Copy constructor and assignment should be private
	Game(const Game&);
	Game &operator=(const Game&);

public:

	// An instance of the State Manager class
	StateManager<Game> *stateMgr;

	// Progress Indicator
	int progress;

	// Max. Progress Indicator
	int progressMax;

	// Switch when game is active
	bool inGame;

	// The Game Constructor
	Game() : progress(0), progressMax(NMAPS - 1), inGame(false)
	{
		// Set up the State Manager
		stateMgr = new StateManager<Game>(this);
		stateMgr->SetCurrentState(GameIdleState);
	}

	// The Game Destructor
	virtual ~Game()
	{
		if( stateMgr != NULL )
		{
			delete stateMgr;
			stateMgr = NULL;
		}
	}

	// Update the Game
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
	{
		return stateMgr->Update(elapsed, key, mouse);
	}

	// Render the Game
	void Render()
	{
		stateMgr->Render();
	}

	// Handle Messages for the Game
	bool Receive(const Message &msg)
	{
		return stateMgr->Receive(msg);
	}

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	bool IsProgressComplete() const {return progress >= progressMax;}
	float FractionalProgress() const {return static_cast<float>(progress)/static_cast<float>(progressMax);}
};

#endif