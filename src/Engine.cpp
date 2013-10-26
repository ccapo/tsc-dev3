#include "Main.hpp"

//-----------------------------------------------------------------------------
// Engine Instance (Singleton)
//-----------------------------------------------------------------------------
Engine *Engine::Instance()
{
	static Engine instance;
	return &instance;
}

//-----------------------------------------------------------------------------
// Startup
//-----------------------------------------------------------------------------
void Engine::Startup(int narg, char *argv[])
{
	// Initialize Random Number Generator
	// If present, get seed value from the command line
	seed = static_cast<uint32>(time(NULL));
	if(narg == 2) seed = static_cast<uint32>(atoi(argv[1]));

	// Libtcod credits
	TCODConsole::credits();

	// Clear root console
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->clear();

	// Add Modules to Engine
	game = new Game();		// Game Module
	menu = new Menu();		// Menu Module
	sound = new Sound();	// Sound Module
	map = new Map();		// Map Module
	player = new Player();	// Player Object
}

//-----------------------------------------------------------------------------
// Shutdown
//-----------------------------------------------------------------------------
void Engine::Shutdown()
{
#ifndef DEV
	// Fade Out
	for(int i = 1; i <= 2*FPSMAX; i++)
	{
		int fade = 255*(2*FPSMAX - i)/(2*FPSMAX - 1);
		TCODConsole::setFade(fade, TCODColor::black);
		TCODConsole::root->flush();
	}
#endif
}

//-----------------------------------------------------------------------------
// Update
//-----------------------------------------------------------------------------
bool Engine::Update()
{
	bool status = true;
	float elapsed = TCODSystem::getLastFrameLength();

	// Update Elapsed Time if not Paused
	if( !menu->stateMgr[menu->activeStateID]->IsInState(MenuPauseState) ) elapsedTime += elapsed;

	// Get Keyboard and Mouse Input
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS | TCOD_EVENT_MOUSE, &key, &mouse);

	status = status && game->Update(elapsed, key, mouse);		// Update Game
	status = status && sound->Update(elapsed, key, mouse);		// Update Sound
	status = status && map->Update(elapsed, key, mouse);		// Update Map
	status = status && player->Update(elapsed, key, mouse);		// Update Player
	status = status && menu->Update(elapsed, key, mouse);		// Update Menu

	return status;
}

//-----------------------------------------------------------------------------
// Render
//-----------------------------------------------------------------------------
void Engine::Render()
{
	// Fade Out
	if( fadeOut )
	{
		fadeOut = false;
#ifndef DEV
		for(int i = 1; i <= FPSMAX; i++)
		{
			int fade = 255*(FPSMAX - i)/(FPSMAX - 1);
			TCODConsole::setFade(fade, TCODColor::black);
			TCODConsole::root->flush();
		}
#endif
	}

	// Clear root console
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->clear();

	game->Render();		// Render Game
	sound->Render();	// Render Sound
	map->Render();		// Render Map
	player->Render();	// Render Player
	menu->Render();		// Render Menu

	// Fade In
	if( fadeIn )
	{
		fadeIn = false;
#ifndef DEV
		for(int i = 1; i <= FPSMAX; i++)
		{
			int fade = 255*(i - 1)/(FPSMAX - 1);
			TCODConsole::setFade(fade, TCODColor::black);
			TCODConsole::root->flush();
		}
#endif
	}
}

//-----------------------------------------------------------------------------
// Receive
//-----------------------------------------------------------------------------
bool Engine::Receive(const Message &msg)
{
	bool status = true;
	static bool PauseFlag = false;
	static bool HelpFlag = false;
	static bool MenuFlag = false;
	static bool EquipInvFlag = false;
	static bool WeaponInvFlag = false;
	static bool ShieldInvFlag = false;
	static bool ArmourInvFlag = false;
	static bool AccessoryInvFlag = false;
	static bool ItemInvFlag = false;
	static bool EquipShopFlag = false;
	static bool EquipShopBuyFlag = false;
	static bool EquipShopBuyWeaponFlag = false;
	static bool EquipShopBuyShieldFlag = false;
	static bool EquipShopBuyArmourFlag = false;
	static bool EquipShopBuyAccessoryFlag = false;
	static bool EquipShopSellFlag = false;
	static bool EquipShopSellWeaponFlag = false;
	static bool EquipShopSellShieldFlag = false;
	static bool EquipShopSellArmourFlag = false;
	static bool EquipShopSellAccessoryFlag = false;
	static bool ItemShopFlag = false;
	static bool ItemShopBuyFlag = false;
	static bool ItemShopSellFlag = false;
	static bool FerryFlag = false;
	static bool InnFlag = false;
	static bool RestFlag = false;
	static bool DeathFlag = false;

	switch(msg.index)
	{
		case MSG_PAUSE:
		{
			PauseFlag = !PauseFlag;
			if( PauseFlag )
			{
				player->stateMgr->ChangeState(PlayerIdleState);
				menu->stateMgr[STATE_02]->ChangeState(MenuPauseState);
			}
			else
			{
				player->stateMgr->RevertToPreviousState();
				menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_NEWGAME:
		{
			fadeIn = true;
			fadeOut = true;
			game->stateMgr->ChangeState(GameNewState);
			sound->stateMgr->ChangeState(SoundNewState);
			menu->stateMgr[STATE_01]->ChangeState(MenuNewState);
			break;
		}
		case MSG_LOADGAME:
		{
			fadeIn = true;
			fadeOut = true;
			game->stateMgr->ChangeState(GameLoadState);
			menu->stateMgr[STATE_01]->ChangeState(MenuLoadState);
			break;
		}
		case MSG_SAVEGAME:
		{
			fadeIn = true;
			fadeOut = true;
			game->stateMgr->ChangeState(GameSaveState);
			player->stateMgr->ChangeState(PlayerIdleState);
			menu->stateMgr[STATE_01]->ChangeState(MenuSaveState);
			break;
		}
		case MSG_QUITGAME:
		{
			game->stateMgr->ChangeState(GameQuitState);
			sound->stateMgr->ChangeState(SoundQuitState);
			break;
		}
		case MSG_INTROGAME:
		{
			fadeIn = true;
			fadeOut = true;
			game->stateMgr->ChangeState(GameIdleState);
			sound->stateMgr->ChangeState(SoundTempleState);
			map->stateMgr->ChangeState(MapTempleState);
			player->stateMgr->ChangeState(PlayerIntroState);
			menu->stateMgr[STATE_01]->ChangeState(MenuUIState);
			menu->stateMgr[STATE_02]->ChangeState(MenuIntroState);
			break;
		}
		case MSG_BEGINGAME:
		{
			game->inGame = true;
			player->stateMgr->ChangeState(PlayerTempleState);
			menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			break;
		}
		case MSG_ENTERWORLD:
		{
			fadeIn = true;
			fadeOut = true;
			mapID = WORLD_MAP;
			game->stateMgr->ChangeState(GameIdleState);
			sound->stateMgr->ChangeState(SoundWorldState);
			map->stateMgr->ChangeState(MapWorldState);
			player->stateMgr->ChangeState(PlayerWorldState);
			menu->stateMgr[STATE_01]->ChangeState(MenuUIState);
			break;
		}
		case MSG_ENTERTEMPLE:
		{
			fadeIn = true;
			fadeOut = true;
			//mapID = TEMPLE_LIGHT;
			sound->stateMgr->ChangeState(SoundTempleState);
			map->stateMgr->ChangeState(MapTempleState);
			player->stateMgr->ChangeState(PlayerTempleState);
			break;
		}		
		case MSG_ENTERTOWN:
		{
			fadeIn = true;
			fadeOut = true;
			//mapID = TOWN_01;
			sound->stateMgr->ChangeState(SoundTownState);
			map->stateMgr->ChangeState(MapTownState);
			player->stateMgr->ChangeState(PlayerTownState);
			break;
		}
		case MSG_ENTERCAVE:
		{
			fadeIn = true;
			fadeOut = true;
			//mapID = CAVE_01;
			sound->stateMgr->ChangeState(SoundCaveState);
			map->stateMgr->ChangeState(MapCaveState);
			player->stateMgr->ChangeState(PlayerCaveState);
			break;
		}
		case MSG_GAMEHELP:
		{
			HelpFlag = !HelpFlag;
			if( HelpFlag )
			{
				player->stateMgr->ChangeState(PlayerIdleState);
				menu->stateMgr[STATE_02]->ChangeState(MenuHelpState);
			}
			else
			{
				player->stateMgr->RevertToPreviousState();
				menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_GAMEMENU:
		{
			MenuFlag = !MenuFlag;
			if( MenuFlag )
			{
				player->stateMgr->ChangeState(PlayerIdleState);
				menu->stateMgr[STATE_02]->ChangeState(MenuGameState);
			}
			else
			{
				player->stateMgr->RevertToPreviousState();
				menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPINV:
		{
			EquipInvFlag = !EquipInvFlag;
			if( EquipInvFlag )
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuEquipInvState);
			}
			else
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_WEAPONINV:
		{
			WeaponInvFlag = !WeaponInvFlag;
			if( WeaponInvFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuWeaponInvState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_SHIELDINV:
		{
			ShieldInvFlag = !ShieldInvFlag;
			if( ShieldInvFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuShieldInvState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ARMOURINV:
		{
			ArmourInvFlag = !ArmourInvFlag;
			if( ArmourInvFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuArmourInvState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ACCESSORYINV:
		{
			AccessoryInvFlag = !AccessoryInvFlag;
			if( AccessoryInvFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuAccessoryInvState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ITEMINV:
		{
			ItemInvFlag = !ItemInvFlag;
			if( ItemInvFlag )
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuItemInvState);
			}
			else
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOP:
		{
			EquipShopFlag = !EquipShopFlag;
			if( EquipShopFlag )
			{
				player->stateMgr->ChangeState(PlayerIdleState);
				menu->stateMgr[STATE_02]->ChangeState(MenuEquipShopState);
			}
			else
			{
				player->stateMgr->RevertToPreviousState();
				menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPBUY:
		{
			EquipShopBuyFlag = !EquipShopBuyFlag;
			if( EquipShopBuyFlag )
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuEquipShopBuyState);
			}
			else
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPBUYWEAPON:
		{
			EquipShopBuyWeaponFlag = !EquipShopBuyWeaponFlag;
			if( EquipShopBuyWeaponFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuEquipShopBuyWeaponState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPBUYSHIELD:
		{
			EquipShopBuyShieldFlag = !EquipShopBuyShieldFlag;
			if( EquipShopBuyShieldFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuEquipShopBuyShieldState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPBUYARMOUR:
		{
			EquipShopBuyArmourFlag = !EquipShopBuyArmourFlag;
			if( EquipShopBuyArmourFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuEquipShopBuyArmourState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPBUYACCESSORY:
		{
			EquipShopBuyAccessoryFlag = !EquipShopBuyAccessoryFlag;
			if( EquipShopBuyAccessoryFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuEquipShopBuyAccessoryState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPSELL:
		{
			EquipShopSellFlag = !EquipShopSellFlag;
			if( EquipShopSellFlag )
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuEquipShopSellState);
			}
			else
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPSELLWEAPON:
		{
			EquipShopSellWeaponFlag = !EquipShopSellWeaponFlag;
			if( EquipShopSellWeaponFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuEquipShopSellWeaponState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPSELLSHIELD:
		{
			EquipShopSellShieldFlag = !EquipShopSellShieldFlag;
			if( EquipShopSellShieldFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuEquipShopSellShieldState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPSELLARMOUR:
		{
			EquipShopSellArmourFlag = !EquipShopSellArmourFlag;
			if( EquipShopSellArmourFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuEquipShopSellArmourState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_EQUIPSHOPSELLACCESSORY:
		{
			EquipShopSellAccessoryFlag = !EquipShopSellAccessoryFlag;
			if( EquipShopSellAccessoryFlag )
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuEquipShopSellAccessoryState);
			}
			else
			{
				menu->stateMgr[STATE_04]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ITEMSHOP:
		{
			ItemShopFlag = !ItemShopFlag;
			if( ItemShopFlag )
			{
				player->stateMgr->ChangeState(PlayerIdleState);
				menu->stateMgr[STATE_02]->ChangeState(MenuItemShopState);
			}
			else
			{
				player->stateMgr->RevertToPreviousState();
				menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ITEMSHOPBUY:
		{
			ItemShopBuyFlag = !ItemShopBuyFlag;
			if( ItemShopBuyFlag )
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuItemShopBuyState);
			}
			else
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_ITEMSHOPSELL:
		{
			ItemShopSellFlag = !ItemShopSellFlag;
			if( ItemShopSellFlag )
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuItemShopSellState);
			}
			else
			{
				menu->stateMgr[STATE_03]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_FERRYMENU:
		{
			FerryFlag = !FerryFlag;
			if( FerryFlag )
			{
				player->stateMgr->ChangeState(PlayerIdleState);
				menu->stateMgr[STATE_02]->ChangeState(MenuFerryState);
			}
			else
			{
				player->stateMgr->RevertToPreviousState();
				menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_INNMENU:
		{
			InnFlag = !InnFlag;
			if( InnFlag )
			{
				player->stateMgr->ChangeState(PlayerIdleState);
				menu->stateMgr[STATE_02]->ChangeState(MenuInnState);
			}
			else
			{
				player->stateMgr->RevertToPreviousState();
				menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_REST:
		{
			RestFlag = !RestFlag;
			if( RestFlag )
			{
				fadeOut = true;
				sound->stateMgr->ChangeState(SoundRestState);
				player->stateMgr->ChangeState(PlayerRestState);
				menu->stateMgr[STATE_02]->ChangeState(MenuRestState);
			}
			else
			{
				fadeIn = true;
				InnFlag = false;
				sound->stateMgr->RevertToPreviousState();
				player->stateMgr->ChangeState(PlayerTownState);
				menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			}
			break;
		}
		case MSG_DEATH:
		{
			DeathFlag = !DeathFlag;
			if( DeathFlag )
			{
				player->stateMgr->ChangeState(PlayerIdleState);
				menu->stateMgr[STATE_02]->ChangeState(MenuDeathState);
			}
			else
			{
				menu->stateMgr[STATE_02]->ChangeState(MenuIdleState);
			}
			break;
		}
		default: break;
	}
	return status;
}

void Engine::GenerateCaveSystem(int &id)
{
	const int dx[NBORDER] = {-1,  0, +1, -1, +1, -1,  0, +1};
	const int dy[NBORDER] = {-1, -1, -1,  0,  0, +1, +1, +1};
	static int rootMapID = 1;

	// Cave System Data
	struct CaveData
	{
		bool occupied;
		int mapID;
		int depth;
	} caveData[NSIZE*NSIZE];

	if( id == WORLD_MAP )
	{
		// Generate World Map
		map->mapData[WORLD_MAP].GenerateMap(WORLD_MAP, WORLD_TYPE);
		id++;
	}
	else if( id >= TEMPLE_LIGHT && id <= TEMPLE_EARTH )
	{
		int xFrom = RNG->getInt(2, map->mapData[WORLD_MAP].width - 3);
		int yFrom = RNG->getInt(2, map->mapData[WORLD_MAP].height - 3);
		int xTo = map->mapData[id].width/2;
		int yTo = map->mapData[id].height - 2;

		map->mapData[id].GenerateMap(id, TEMPLE_TYPE);

		// Add Guardian
		map->mapData[id].AddNpc(Entity::GUARDIAN, map->mapData[id].width/2, map->mapData[id].height/2);

		// Copy equipment names to each temple
		map->mapData[id].WeaponNames = map->mapData[WORLD_MAP].WeaponNames;
		map->mapData[id].ShieldNames = map->mapData[WORLD_MAP].ShieldNames;
		map->mapData[id].ArmourNames = map->mapData[WORLD_MAP].ArmourNames;
		map->mapData[id].AccessoryNames = map->mapData[WORLD_MAP].AccessoryNames;

		// Connect Temple and Town Maps to World Map
		map->mapData[WORLD_MAP].AddMapLocation(xFrom, yFrom, id, xTo, yTo);
		map->mapData[id].AddTunnelSurface(xTo, yTo, WORLD_MAP, xFrom, yFrom);
		id++;
	}
	else if( id >= TOWN_01 && id <= TOWN_12 )
	{
		int xFrom = RNG->getInt(2, map->mapData[WORLD_MAP].width - 3);
		int yFrom = RNG->getInt(2, map->mapData[WORLD_MAP].height - 3);
		int xTo = map->mapData[id].width/2;
		int yTo = map->mapData[id].height - 2;

		map->mapData[id].GenerateMap(id, TOWN_TYPE);

		// Add Townsperson
		map->mapData[id].AddNpc(Entity::TOWNSPERSON, map->mapData[id].width/2, map->mapData[id].height/2);

		// Copy equipment names to each town
		map->mapData[id].WeaponNames = map->mapData[WORLD_MAP].WeaponNames;
		map->mapData[id].ShieldNames = map->mapData[WORLD_MAP].ShieldNames;
		map->mapData[id].ArmourNames = map->mapData[WORLD_MAP].ArmourNames;
		map->mapData[id].AccessoryNames = map->mapData[WORLD_MAP].AccessoryNames;

		// Connect Temple and Town Maps to World Map
		map->mapData[WORLD_MAP].AddMapLocation(xFrom, yFrom, id, xTo, yTo);
		map->mapData[id].AddTunnelSurface(xTo, yTo, WORLD_MAP, xFrom, yFrom);
		id++;
	}
	else
	{
		int g_depthMax = -1;

		// Initialize caveData
		for(int y = 0; y < NSIZE; y++)
		{
			for(int x = 0; x < NSIZE; x++)
			{
				int offset = x + y*NSIZE;
				caveData[offset].occupied = false;
				caveData[offset].mapID = -1;
				caveData[offset].depth = -1;
			}
		}

		int xFrom = RNG->getInt(2, map->mapData[WORLD_MAP].width - 3);
		int yFrom = RNG->getInt(2, map->mapData[WORLD_MAP].height - 3);

		//cout << "Cave mapID: " << id << endl;
		map->mapData[id].GenerateMap(id, CAVETYPE_01);

		// Copy equipment names to each cave
		map->mapData[id].WeaponNames = map->mapData[WORLD_MAP].WeaponNames;
		map->mapData[id].ShieldNames = map->mapData[WORLD_MAP].ShieldNames;
		map->mapData[id].ArmourNames = map->mapData[WORLD_MAP].ArmourNames;
		map->mapData[id].AccessoryNames = map->mapData[WORLD_MAP].AccessoryNames;

		int xTo = RNG->getInt(2, map->mapData[id].width - 3);
		int yTo = RNG->getInt(2, map->mapData[id].height - 3);

		while( map->mapData[id].IsObstructed(xTo, yTo) || map->mapData[id].FeatureType(xTo, yTo) == FEATURE_TRAP )
		{
			xTo = RNG->getInt(2, map->mapData[id].width - 3);
			yTo = RNG->getInt(2, map->mapData[id].height - 3);
		}

		// Connect Cave Map to World Map
		map->mapData[WORLD_MAP].AddMapLocation(xFrom, yFrom, id, xTo, yTo);
		map->mapData[id].AddTunnelSurface(xTo, yTo, WORLD_MAP, xFrom, yFrom);

		int srcMapID = id;
		int srcDepth = 0;
		int srcCaveType = srcDepth/5;

		// Seed Brownian Tree Cave System
		int offset = NSIZE/2 + (NSIZE/2)*NSIZE;
		caveData[offset].occupied = true;
		caveData[offset].mapID = srcMapID;
		caveData[offset].depth = 0;
		//printf("Map: %d, Depth: %d\n", caveData[offset].mapID, caveData[offset].depth);

		id++;
		for(int k = 1; k < NCAVE_REGIONS*NLEVELS_REGION; k++)
		{
			// Start Map Position At Random
			int x, y, offset;
			OVER: do
			{
				x = RNG->getInt(1, NSIZE - 2);
				y = RNG->getInt(1, NSIZE - 2);
				offset =  x + y*NSIZE;
			} while( caveData[offset].occupied );

			// Random Walk Map Position Until Adjacent To Existing Maps
			bool vacant = true;
			for(int j = 0; j < NBORDER; j++)
			{
				offset = (x + dx[j]) + (y + dy[j])*NSIZE;
				vacant = vacant && !caveData[offset].occupied;
			}
			while( vacant )
			{
				int k = RNG->getInt(0, NBORDER - 1);
				x += dx[k];
				y += dy[k];

				// Start Over If We Leave The Grid
				if(x < 1 || x >= NSIZE - 1 || y < 1 || y >= NSIZE - 1) goto OVER;
				vacant = true;
				for(int j = 0; j < NBORDER; j++)
				{
					offset = (x + dx[j]) + (y + dy[j])*NSIZE;
					vacant = vacant && !caveData[offset].occupied;
				}
			}

			// Store Information For Current Map
			offset = x + y*NSIZE;
			caveData[offset].occupied = true;
			caveData[offset].mapID = id;

			// Determine Maximum Depth Of Adjacent Maps
			int depthMax = 0;
			for(int j = 0; j < NBORDER; j++)
			{
				offset = (x + dx[j]) + (y + dy[j])*NSIZE;
				if( caveData[offset].depth >= depthMax ) depthMax = caveData[offset].depth;
			}

			// Assign Depth For Current Map
			depthMax++;
			offset = x + y*NSIZE;
			caveData[offset].depth = depthMax;

			// Keep Track Of Global Max. Depth
			if( depthMax >= g_depthMax ) g_depthMax = depthMax;

			// Generate Map
			int srcMapID = caveData[offset].mapID;
			int srcDepth = caveData[offset].depth;
			int srcCaveType = srcDepth/5;

			map->mapData[srcMapID].GenerateMap(srcMapID, srcCaveType);

			// Copy equipment names to each cave
			map->mapData[id].WeaponNames = map->mapData[WORLD_MAP].WeaponNames;
			map->mapData[id].ShieldNames = map->mapData[WORLD_MAP].ShieldNames;
			map->mapData[id].ArmourNames = map->mapData[WORLD_MAP].ArmourNames;
			map->mapData[id].AccessoryNames = map->mapData[WORLD_MAP].AccessoryNames;

			//printf("Map: %d, Depth: %d\n", srcMapID, srcDepth);
			//printf("Connected To Maps: ");
			for(int j = 0; j < NBORDER; j++)
			{
				offset = (x + dx[j]) + (y + dy[j])*NSIZE;
				if( caveData[offset].depth >= depthMax - 1 )
				{
					// Connect Maps
					int dstMapID = caveData[offset].mapID;
					int dstDepth = caveData[offset].depth;
					int xFrom = RNG->getInt(2, map->mapData[srcMapID].width - 3);
					int yFrom = RNG->getInt(2, map->mapData[srcMapID].height - 3);
					int xTo = RNG->getInt(2, map->mapData[dstMapID].width - 3);
					int yTo = RNG->getInt(2, map->mapData[dstMapID].height - 3);
					//printf("(%d, %d) ", dstMapID, dstDepth);

					while( map->mapData[srcMapID].IsObstructed(xFrom, yFrom) || map->mapData[srcMapID].FeatureType(xFrom, yFrom) == FEATURE_TRAP )
					{
						xFrom = RNG->getInt(2, map->mapData[srcMapID].width - 3);
						yFrom = RNG->getInt(2, map->mapData[srcMapID].height - 3);
					}

					while( map->mapData[dstMapID].IsObstructed(xTo, yTo) || map->mapData[dstMapID].FeatureType(xTo, yTo) == FEATURE_TRAP )
					{
						xTo = RNG->getInt(2, map->mapData[dstMapID].width - 3);
						yTo = RNG->getInt(2, map->mapData[dstMapID].height - 3);
					}

					map->mapData[srcMapID].AddTunnelUp(xFrom, yFrom, dstMapID, xTo, yTo);
					map->mapData[dstMapID].AddTunnelDown(xTo, yTo, srcMapID, xFrom, yFrom);
				}
			}
			id++;
			//printf("\n");
		}
		//printf("Max Depth: %d\n", g_depthMax);

#ifdef DEV
		// Store Map Information In A PGM Image
		FILE *fout = fopen("cave_system.pgm", "w");
		fprintf(fout, "P2\n%d %d\n%d\n", NSIZE, NSIZE, g_depthMax + 1);
		for(int y = 0; y < NSIZE; y++)
		{
			for(int x = 0; x < NSIZE; x++)
			{
				int offset = x + y*NSIZE;
				fprintf(fout, "%d ", caveData[offset].occupied ? caveData[offset].depth : g_depthMax + 1);
			}
			fprintf(fout, "\n");
		}
		fclose(fout);

		// Convert PGM Image to PNG Image
		system("convert cave_system.pgm cave_system.png; rm cave_system.pgm");

		string cmd = "mv cave_system.png screenshots/cave_system_0";
		stringstream number;
		number << rootMapID++;
		cmd.append(number.str());
		cmd.append(".png");
		system(cmd.c_str());
#endif
	}

	if( id >= NMAPS - 1 )
	{
		// Handle Dark Tunnel Traps
		for(int i = CAVE_01; i < NMAPS; i++)
		{
			for(int y = 0; y < map->mapData[i].height; y++)
			{
				for(int x = 0; x < map->mapData[i].width; x++)
				{
					if( map->mapData[i].TrapType(x, y) == TRAP_DARKTUNNEL )
					{
						if( i <= NMAPS - 5 )
						{
							int dstMapID = RNG->getInt(i + 1, i + 4);
							int xTo = RNG->getInt(2, map->mapData[dstMapID].width - 3);
							int yTo = RNG->getInt(2, map->mapData[dstMapID].height - 3);
							while( map->mapData[dstMapID].IsObstructed(xTo, yTo) || map->mapData[dstMapID].FeatureType(xTo, yTo) == FEATURE_TRAP )
							{
								xTo = RNG->getInt(2, map->mapData[dstMapID].width - 3);
								yTo = RNG->getInt(2, map->mapData[dstMapID].height - 3);
							}
							map->mapData[i].SetTrap(x, y, TRAP_DARKTUNNEL, dstMapID, xTo, yTo);
						}
						else
						{
							map->mapData[i].SetFloor(x, y);
						}
					}
				}
			}
		}
	}
}