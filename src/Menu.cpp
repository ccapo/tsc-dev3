#include "Main.hpp"

// The Menu Constructor
Menu::Menu() : magicID(0), activeStateID(0), imgMagic(NULL)
{
	// Setup State Managers and Off-Screen Consoles
	for(int i = 0; i < NSTATES; i++)
	{
		// State Managers
		stateMgr[i] = new StateManager<Menu>(this);
		stateMgr[i]->SetCurrentState(MenuIdleState);

		// Consoles
		con[i] = NULL;
	}

	// Define Status Console
	conStatus = new TCODConsole(DISPLAY_WIDTH, 3);

	// Set up the State Manager
	stateMgr[activeStateID]->SetCurrentState(MenuMainState);

	// Background image for Main Menu
	imgMainMenu = new TCODImage("data/img/main_menu.png");

	// Initialize the Message Log
	MessageLog(TCODColor::red, "Welcome Adventurer!\nPrepare to perish in the Serpentine Caves.");

	MainOptions.push_back("%cNew Game %c");
	MainOptions.push_back("%cLoad Game%c");
	MainOptions.push_back("%cGame Help%c");
	MainOptions.push_back("%cQuit Game%c");

	HelpOptions.push_back("Move/Attack        :: Arrow Keys       ");
	HelpOptions.push_back("Use Magic          :: Left Mouse Button");
	HelpOptions.push_back("Select Magic       :: Control          ");
	HelpOptions.push_back("Toggle Menu/Cancel :: Escape           ");
	HelpOptions.push_back("Select/Action      :: Enter            ");
	HelpOptions.push_back("Toggle Music       :: Delete           ");
	HelpOptions.push_back("Toggle Game        :: Pause            ");
	HelpOptions.push_back("Toggle Fullscreen  :: Alt + Enter      ");
	HelpOptions.push_back("Screen Capture     :: Backspace        ");
	HelpOptions.push_back("Game Help          :: ?                ");

	HelpText = "Whenever the Player returns to the %cWorld Map%c, the game will automatically overwrite the existing save file.\n\nIf the Player expires, death is %cpermanent%c as the save file is %cdeleted%c.";

	IntroText.push_back("Welome brave adventurer, thank you for heeding my pleas for help.\n\n\nI am the %cGuardian of Light%c, one of the five entrusted to protect this world.\n\n\nA %cPowerful Ancient Menace%c is gathering once again in the shadows, and threatens to destroy the peace and harmony of these lands.\n\n\nThis is why I have summoned you here, I must impress upon you to persue a perilous quest to rid the world of this threat.");
	IntroText.push_back("We know this power is gathering deep within\n%cThe Serpentine Caves%c, but where we know not.\n\n\nIt will be a difficult journey, so seek out the other four %cElemental Guardians%c for assistance. If they deem you worthy, they will grant you the ability to use their power.\n\n\nTo aid you on your quest I will grant my %cPower of Light%c, and any creature of the dark will be startled by its brilliance. Use this power wisely.\n\n\nGood luck brave hero, and may the record of your deeds be sung throughout the ages.");

	GameOptions.push_back("%cEquipment%c");
	GameOptions.push_back("%cInventory%c");
	GameOptions.push_back("%cQuit Game%c");

	EquipOptions.push_back("%cWeapon   %c ::");
	EquipOptions.push_back("%cShield   %c ::");
	EquipOptions.push_back("%cArmour   %c ::");
	EquipOptions.push_back("%cAccessory%c ::");

	EquipOptionsHorizontal.push_back("%cWeapon%c");
	EquipOptionsHorizontal.push_back("%cShield%c");
	EquipOptionsHorizontal.push_back("%cArmour%c");
	EquipOptionsHorizontal.push_back("%cAccessory%c");

	EquipListOptions.push_back("Weapons");
	EquipListOptions.push_back("Shields");
	EquipListOptions.push_back("Armour");
	EquipListOptions.push_back("Accessories");

	EquipShopOptions.push_back("%cBuy Equip %c");
	EquipShopOptions.push_back("%cSell Equip%c");
	EquipShopOptions.push_back("%cExit Shop %c");

	ItemShopOptions.push_back("%cBuy Items %c");
	ItemShopOptions.push_back("%cSell Items%c");
	ItemShopOptions.push_back("%cExit Shop %c");

	FerryOptions.push_back("%cTake Ferry%c");
	FerryOptions.push_back("%cExit Ferry%c");

	FerryText.push_back("Where are you headed?\n\n\nMy fee is %c25 GP%c per trip.");
	FerryText.push_back("Come back any time.");

	InnOptions.push_back("%cStay Inn%c");
	InnOptions.push_back("%cExit Inn%c");

	InnText.push_back("Hello there young traveller.\n\n\nCan I interest you in a nice hearty meal, and a warm comfortable bed?\n\n\nWe charge %c15 GP%c per night, meal included.\n\n\nWould you care to stay?");
	InnText.push_back("It is a shame to see you leave.\n\n\nPlease hurry back!");

	DeathText = "While your valiant efforts should be commended, they were all for naught.\n\n\nThe %cAncient Menance%c spread across these lands, killing all those that could fight and enslaving the rest.\n\n\nEventhough your part in this tale is over, perhaps a new hero will one day emerge from the remnants of these broken and shattered people.";
}

// Update the Menu
bool Menu::Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	TCOD_key_t k = {TCODK_NONE, 0};
	TCOD_mouse_t m = {0,0, 0,0, 0,0, 0,0};

	// Delete all the consoles
	for(int i = 0; i < NSTATES; i++)
	{
		if( con[i] != NULL )
		{
			delete con[i];
			con[i] = NULL;
		}
	}

	//cout << "Active State ID: " << activeStateID << endl;
	for(int i = 0; i < NSTATES; i++)
	{
		//cout << i << " Menu State: " << stateMgr[i]->GetNameOfCurrentState() << endl;
		if( i == activeStateID )
		{
			status = status && stateMgr[i]->Update(elapsed, key, mouse);
		}
		else
		{
			status = status && stateMgr[i]->Update(elapsed, k, m);
		}
	}
	return status;
}

// Render the Menu
void Menu::Render()
{
	for(int i = 0; i < NSTATES; i++) stateMgr[i]->Render();
}

// Handle Messages for the Message Log
bool Menu::Receive(const Message &msg)
{
	bool status = true;
	for(int i = 0; i < NSTATES; i++) status && stateMgr[STATE_01]->Receive(msg);
	return status;
}

// Displays Progress Bar
void Menu::DisplayProgress(string msg, float fraction)
{
	int length = static_cast<int>(fraction*SCREEN_WIDTH/2);
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->clear();
	TCODConsole::root->printEx(SCREEN_WIDTH/2, SCREEN_HEIGHT/2 + 4, TCOD_BKGND_NONE, TCOD_CENTER, msg.c_str());
	if(length > 0)
	{
		TCODConsole::root->setDefaultBackground(TCODColor::red);
		TCODConsole::root->rect(SCREEN_WIDTH/4, SCREEN_HEIGHT/2, length, 2, false, TCOD_BKGND_SET);
	}
	if(length < SCREEN_WIDTH/2)
	{
		TCODConsole::root->setDefaultBackground(TCODColor::darkestRed);
		TCODConsole::root->rect(SCREEN_WIDTH/4 + length, SCREEN_HEIGHT/2, SCREEN_WIDTH/2 - length, 2, false, TCOD_BKGND_SET);
	}
}

// Update Status Panel
void Menu::UpdateStatusPanel(TCODConsole *con)
{
	int x = 3, y = 12;

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

	con->print(x, y, "%cHP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 4, y++, "%d/%d", engine->player->entity->status.hp, engine->player->entity->stats.hpmax);

	con->print(x, y, "%cMP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 4, y++, "%d/%d", engine->player->entity->status.mp, engine->player->entity->stats.mpmax);

	con->print(x, ++y, "%cStatus:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x, ++y, "%s", engine->player->entity->status.bodilyStatus[engine->player->entity->status.bodilyIndex].c_str());

	for(int i = 0; i < NAILMENTSTATUS; i++)
	{
		if( engine->player->entity->status.ailmentFlag[i] )
		{
			con->print(x, ++y, "%s", engine->player->entity->status.ailmentStatus[i].c_str());
		}
	}

	// Compute the elapsed time in convenient units
	int nhours = static_cast<int>(engine->elapsedTime/(60.0f*60.0f));
	float time = engine->elapsedTime - (60.0f*60.0f)*static_cast<float>(nhours);
	int nmins = static_cast<int>(time/60.0f);
	int nsecs = static_cast<int>(time - 60.0f*static_cast<float>(nmins));

	x = 3, y = 24;
	con->print(x, y, "%cGP:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 4, y++, "%d", engine->player->entity->status.gp);
	y++;

	con->print(x, y++, "%cTime:%c", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x, y, "%02d:%02d:%02d", nhours, nmins, nsecs);
}

// Update Stats Panel
void Menu::UpdateStatsPanel(TCODConsole *con)
{
	int x = 2, y = NEQUIPTYPE + 6;

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

	float xpfraction = static_cast<float>(engine->player->entity->status.xp)/static_cast<float>(engine->player->entity->status.xpnext);
	int xpbar = static_cast<int>(14.0f*xpfraction);
	if(xpbar > 0)
	{
		con->setDefaultBackground(TCODColor::darkGreen);
		con->rect(x, y + 2, xpbar, 1, true, TCOD_BKGND_SET);
	}
	if(xpbar < 14)
	{
		con->setDefaultBackground(TCODColor::darkerGreen);
		con->rect(x + xpbar, y + 2, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	}
	con->setDefaultBackground(TCODColor::black);
	con->print(x, y, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->status.lvl);
	con->print(x, y++, "%cXP   :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->printEx(x + 7, y++, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", engine->player->entity->status.xp, engine->player->entity->status.xpnext);

	y += 2;
	con->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.hpmax);

	con->print(x, y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.ap);
	con->print(x, y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.dp);

	con->print(x, y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.str);
	con->print(x, y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.spd);

	y += 2;
	con->print(x, y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.mpmax);

	con->print(x, y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.map);
	con->print(x, y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.mdp);

	con->print(x, y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.wil);
	con->print(x, y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.acu);
}

// Update Stats Panel
void Menu::UpdateStatsPanel(TCODConsole *con, Stats stats)
{
	int x = 2, y = NEQUIPTYPE + 6; //, i = 0;
	if( !engine->menu->stateMgr[engine->menu->activeStateID]->IsInState(MenuIdleState) ) y = 2;

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

	float xpfraction = static_cast<float>(engine->player->entity->status.xp)/static_cast<float>(engine->player->entity->status.xpnext);
	int xpbar = static_cast<int>(14.0f*xpfraction);
	if(xpbar > 0)
	{
		con->setDefaultBackground(TCODColor::darkGreen);
		con->rect(x, y + 2, xpbar, 1, true, TCOD_BKGND_SET);
	}
	if(xpbar < 14)
	{
		con->setDefaultBackground(TCODColor::darkerGreen);
		con->rect(x + xpbar, y + 2, 14 - xpbar, 1, true, TCOD_BKGND_SET);
	}
	con->setDefaultBackground(TCODColor::black);
	con->print(x, y, "%cLVL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->status.lvl);
	con->print(x, y++, "%cXP   :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->printEx(x + 7, y++, TCOD_BKGND_NONE, TCOD_CENTER, "%d/%d", engine->player->entity->status.xp, engine->player->entity->status.xpnext);

	y += 2;
	con->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.hpmax);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.hpmax, stats.hpmax);

	con->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.ap);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.ap, stats.ap);

	con->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.dp);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.dp, stats.dp);

	con->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.str);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.str, stats.str);

	con->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.spd);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.spd, stats.spd);

	y += 2;
	con->print(x, ++y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.mpmax);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.mpmax, stats.mpmax);

	con->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.map);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.map, stats.map);

	con->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.mdp);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.mdp, stats.mdp);

	con->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.wil);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.wil, stats.wil);

	con->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.acu);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.acu, stats.acu);
}

// Update Equip Stats Panel
void Menu::UpdateEquipStatsPanel(TCODConsole *con)
{
	int h = 3*DISPLAY_HEIGHT/4, hs = h - 2;
	int x = 2, y = 2*hs/3 + 1 + 2;
	if( !engine->menu->stateMgr[engine->menu->activeStateID]->IsInState(MenuIdleState) ) y = (hs - 5)/2 + 3 + 2;

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

	con->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.hpmax);

	con->print(x, y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.ap);
	con->print(x, y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.dp);

	con->print(x, y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.str);
	con->print(x, y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.spd);

	x += 20; y = 2*hs/3 + 1 + 2;
	if( !engine->menu->stateMgr[engine->menu->activeStateID]->IsInState(MenuIdleState) ) y = (hs - 5)/2 + 3 + 2;
	con->print(x, y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.mpmax);

	con->print(x, y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.map);
	con->print(x, y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.mdp);

	con->print(x, y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.wil);
	con->print(x, y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y++, "%2d", engine->player->entity->stats.acu);
}

// Update Equip Stats Panel
void Menu::UpdateEquipStatsPanel(TCODConsole *con, Stats stats)
{
	int h = 3*DISPLAY_HEIGHT/4, hs = h - 2;
	int x = 2, y = 2*hs/3 + 1 + 2; //, i = 0;
	if( !engine->menu->stateMgr[engine->menu->activeStateID]->IsInState(MenuIdleState) ) y = (hs - 5)/2 + 3 + 2;

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

	con->print(x, y, "%cHPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.hpmax);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.hpmax, stats.hpmax);

	con->print(x, ++y, "%cATK  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.ap);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.ap, stats.ap);

	con->print(x, ++y, "%cDEF  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.dp);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.dp, stats.dp);

	con->print(x, ++y, "%cSTR  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.str);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.str, stats.str);

	con->print(x, ++y, "%cSPD  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.spd);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.spd, stats.spd);

	x += 20; y = 2*hs/3 + 1 + 2;
	if( !engine->menu->stateMgr[engine->menu->activeStateID]->IsInState(MenuIdleState) ) y = (hs - 5)/2 + 3 + 2;
	con->print(x, y, "%cMPMAX:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.mpmax);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.mpmax, stats.mpmax);

	con->print(x, ++y, "%cM.ATK:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.map);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.map, stats.map);

	con->print(x, ++y, "%cM.DEF:%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.mdp);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.mdp, stats.mdp);

	con->print(x, ++y, "%cWIL  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.wil);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.wil, stats.wil);

	con->print(x, ++y, "%cACU  :%c ", TCOD_COLCTRL_3, TCOD_COLCTRL_STOP);
	con->print(x + 7, y, "%2d", engine->player->entity->stats.acu);
	DisplayUpdatedStat(con, x, y, engine->player->entity->stats.acu, stats.acu);
}

// Displays Preview of Player Stats 
void Menu::DisplayUpdatedStat(TCODConsole *con, int x, int y, int oldstat, int newstat)
{
	char str[CHARMAX];

	// Set text colours
	TCODConsole::setColorControl(TCOD_COLCTRL_1, TCODColor::white, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_2, TCODColor::white, TCODColor::lightBlue);
	TCODConsole::setColorControl(TCOD_COLCTRL_3, TCODColor::lighterYellow, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_4, TCODColor::red, TCODColor::black);
	TCODConsole::setColorControl(TCOD_COLCTRL_5, TCODColor::green, TCODColor::black);

	x += 10;
	con->print(x, y, "%c", TCOD_CHAR_ARROW_E);
	sprintf(str, "%s%2d%s", "%c", newstat, "%c");
	x += 2;
	if( newstat > oldstat )
	{
		con->print(x, y, str, TCOD_COLCTRL_5, TCOD_COLCTRL_STOP);
	}
	else if( newstat < oldstat )
	{
		con->print(x, y, str, TCOD_COLCTRL_4, TCOD_COLCTRL_STOP);
	}
	else
	{
		con->print(x, y, str, TCOD_COLCTRL_1, TCOD_COLCTRL_STOP);
	}
}

void Menu::RenderBar(int x, int y, int width, string name, float value, float maxValue, const TCODColor &barColor, const TCODColor &backColor)
{
	// Fill the background
	conStatus->setDefaultBackground(backColor);
	conStatus->rect(x, y, width, 1, false, TCOD_BKGND_SET);

	int barWidth = static_cast<int>(width*value/maxValue);
	if( barWidth > 0 )
	{
		// Draw the bar
		conStatus->setDefaultBackground(barColor);
		conStatus->rect(x, y, barWidth, 1, false, TCOD_BKGND_SET);
	}

	// Print text on top of the bar
	conStatus->setDefaultForeground(TCODColor::white);
	conStatus->printEx(x + width/2, y, TCOD_BKGND_NONE, TCOD_CENTER, "%s: %g/%g", name.c_str(), value, maxValue);
}

void Menu::RenderMouseLook()
{
	string buffer;
	buffer.clear();
	bool first = true;
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	TCODConsole::root->setDefaultBackground(TCODColor::lightGrey);
	TCODConsole::root->setDefaultForeground(TCODColor::white);

	for(int i = 0; i < SCREEN_WIDTH; i++) TCODConsole::root->putChar(i, DISPLAY_HEIGHT + 3, ' ' ,TCOD_BKGND_DEFAULT);

	// If mouse is out of FOV, nothing to render
	if( engine->mouse.cx < 0 || engine->mouse.cx >= DISPLAY_WIDTH || engine->mouse.cy < 0 || engine->mouse.cy >= DISPLAY_HEIGHT + 3 ) return;

	for(int i = 0; i < mapdata->objects.size(); i++)
	{
		// Find entities under the mouse cursor
		Object *object = mapdata->objects.get(i);
		for(int i = 0; i < object->sym.size(); i++)
		{
			if( object->x.get(i) == engine->mouse.cx && object->y.get(i) + 3 == engine->mouse.cy )
			{
				if( !first )
				{
					buffer.append(", ");
				}
				else
				{
					first = false;
				}
				buffer.append(object->name);
			}
		}
	}

	// Display the list of entities under the mouse cursor
	TCODConsole::root->printEx(1, DISPLAY_HEIGHT + 3, TCOD_BKGND_NONE, TCOD_LEFT, buffer.c_str());
}

void Menu::MessageLog(const TCODColor &col, const char *text, ...)
{
	// Build the text
	va_list ap;
	char buf[CHARMAX];
	va_start(ap, text);
	vsprintf(buf, text, ap);
	va_end(ap);

	char *lineBegin = buf;
	char *lineEnd;
	do
	{
		// Make room for the new message
		if( Log.size() == NMSGS )
		{
			MessageData *toRemove = Log.get(0);
			Log.remove(toRemove);
			delete toRemove;
		}

		// Detect end of the line
		lineEnd = strchr(lineBegin,'\n');
		if( lineEnd ) *lineEnd = '\0';

		// Add a new message to the log
		MessageData *msg = new MessageData(lineBegin, col);
		Log.push(msg);

		// Go to next line
		lineBegin = lineEnd + 1;
	} while( lineEnd );
}
