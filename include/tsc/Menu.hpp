#ifndef MENU_HPP
#define MENU_HPP
//------------------------------------------------------------------------
//
// Name: Menu.hpp
//
// Desc: A class to implement a Menu
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "MenuStates.hpp"
#include "Module.hpp"
#include "StateManager.hpp"

class Menu : public Module
{
private:

	// Copy constructor and assignment should be private
	Menu(const Menu&);
	Menu &operator=(const Menu&);

public:

	struct MessageData
	{
		char *text;
		TCODColor col;
		MessageData(const char *text, const TCODColor &col): text(strdup(text)), col(col) {}
		~MessageData(){}
	};

	// Menu Text
	vector<string> MainOptions, HelpOptions, GameOptions, EquipOptions, EquipOptionsHorizontal;
	vector<string> EquipListOptions, EquipShopOptions, ItemShopOptions, InnOptions, FerryOptions;
	vector<string> IntroText, FerryText, InnText;
	string HelpText, DeathText;

	// The instances of the State Manager class
	StateManager<Menu> *stateMgr[NSTATES];

	// Magic ID
	int magicID;

	// Background image for main menu
	TCODImage *imgMainMenu;

	// Magic Icon
	TCODImage *imgMagic;

	// Off-Screen Consoles
	TCODConsole *con[NSTATES];

	// Highest Active State Index
	int activeStateID;

	// Status Console
	TCODConsole *conStatus;

	TCODList<MessageData *> Log;

	// The Menu Constructor
	Menu();

	// The Menu Destructor
	virtual ~Menu()
	{
		// Delete all State Managers and consoles
		for(int i = 0; i < NSTATES; i++)
		{
			if( stateMgr[i] != NULL )
			{
				delete stateMgr[i];
				stateMgr[i] = NULL;
			}

			if( con[i] != NULL )
			{
				delete con[i];
				con[i] = NULL;
			}
		}

		if( imgMainMenu != NULL )
		{
			delete imgMainMenu;
			imgMainMenu = NULL;
		}

		if( imgMagic != NULL )
		{
			delete imgMagic;
			imgMagic = NULL;
		}

		if( conStatus != NULL )
		{
			delete conStatus;
			conStatus = NULL;
		}

		Log.clearAndDelete();
	}

	// Update the Menu
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);

	// Render the Menu
	void Render();

	// Handle Messages for the Message Log
	bool Receive(const Message &msg);

	// Send text to MessageLog
	void MessageLog(const TCODColor &col, const char *text, ...);

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	void IncreaseStateID(){activeStateID++; Clamp<int>(activeStateID, 0, NSTATES);}
	void DecreaseStateID(){activeStateID--; Clamp<int>(activeStateID, -1, NSTATES);}

	void IncrementMagicID(){magicID = (magicID + 1) % NMAGIC;}

	void DisplayProgress(string msg, float fraction);
	void UpdateStatusPanel(TCODConsole *con);
	void UpdateStatsPanel(TCODConsole *con);
	void UpdateStatsPanel(TCODConsole *con, Stats stats);
	void UpdateEquipStatsPanel(TCODConsole *con);
	void UpdateEquipStatsPanel(TCODConsole *con, Stats stats);
	void DisplayUpdatedStat(TCODConsole *con, int x, int y, int oldstat, int newstat);

	void RenderBar(int x, int y, int width, string name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor);
	void RenderMouseLook();
};

#endif