#ifndef ENGINE_HPP
#define ENGINE_HPP
//------------------------------------------------------------------------
//
// Name: Engine.hpp
//
// Desc: Singleton class to handle the management of modules
//
// Author: Chris Capobianco, 2012-10-06
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Game.hpp"
#include "Menu.hpp"
#include "Map.hpp"
#include "Player.hpp"
#include "Sound.hpp"

class Module;
class Map;

// Provide easy access
#define engine Engine::Instance()

class Engine
{
private:

	// Copy constructor and assignment should be private
	Engine(const Engine&);
	Engine &operator=(const Engine&);

public:

	// Engine Instance
	static Engine *Instance();

	// A pointer to the game module
	Game *game;

	// A pointer to the menu module
	Menu *menu;

	// A pointer to the map module
	Map *map;

	// A pointer to the sound module
	Sound *sound;

	// A pointer to the Player module
	Player *player;

	// Game Title
	string title;

	// Game Version
	string version;

	// Keyboard Data
	TCOD_key_t key;

	// Mouse Data
	TCOD_mouse_t mouse;

	// Font information
	vector<string> fonts;

	// Font ID
	int fontID;

	// Current Map ID
	int mapID;

	// Fade In and Flag Out flags
	bool fadeIn, fadeOut;

	// Elapsed Time
	float elapsedTime;

	Engine(): fontID(FONT_01), mapID(TEMPLE_LIGHT), fadeIn(false), fadeOut(false), elapsedTime(0.0f)
	{
		fonts.push_back("data/fonts/arial8x8-ext.png");
		fonts.push_back("data/fonts/arial16x16-ext.png");

		int fontFlags = TCOD_FONT_LAYOUT_TCOD | TCOD_FONT_TYPE_GREYSCALE;
		int nCol = 32, nRow = 14;
		int initialDelay = 100, interval = 1000/MAX(1,FPSMAX);
		bool fullscreen = false;
		TCOD_renderer_t renderer = TCOD_RENDERER_SDL;

		// Initialize Fonts
		TCODConsole::setCustomFont(fonts[fontID].c_str(), fontFlags, nCol, nRow);

		// Define Title and Version
		title = "The Serpentine Caves";
		version = "v";

		stringstream majorversion, minorversion, buildversion;
		majorversion << MAJOR_VERSION;
		minorversion << MINOR_VERSION;
		buildversion << BUILD_VERSION;

		version.append(majorversion.str());
		version.append(".");
		version.append(minorversion.str());
		version.append(".");
		version.append(buildversion.str());

		title.append(" ");
		title.append(version);

		// Initialize Root Console
		//TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, "The Serpentine Caves v"VERSION, fullscreen, renderer);
		TCODConsole::initRoot(SCREEN_WIDTH, SCREEN_HEIGHT, title.c_str(), fullscreen, renderer);

		// Set keyboard repeat delay
		TCODConsole::setKeyboardRepeat(initialDelay, interval);

		// Show cursor
		TCODMouse::showCursor(true);

		// Limit the framerate to maxFps FPS
		TCODSystem::setFps(FPSMAX);

		// Assign extra ascii keys
		int x = 0, y = 8;
		TCODConsole::mapAsciiCodeToFont(CHAR_STAIRS_UP, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_STAIRS_DOWN, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_HOLE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_WATER_01, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_WATER_02, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_LAVA_01, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_LAVA_02, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_CHEST_OPEN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_CHEST_CLOSED, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_POTION_YELLOW, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_POTION_RED, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_POTION_GREEN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_POTION_BLUE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_KEY, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_RING_RED, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_RING_GREEN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_RING_BLUE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_RING_RED_BIG, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_RING_GREEN_BIG, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_RING_BLUE_BIG, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SHIELD_BROWN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SHIELD_GREY, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SHIELD_GOLD, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SWORD_BASIC, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SWORD_STEEL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SWORD_GOLD, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_BROWN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_YELLOW, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_RED, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_GREEN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_BLUE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ARMOUR_MITHRIL, x++, y);
		x = 0; y++;

		TCODConsole::mapAsciiCodeToFont(CHAR_CHARGEBAR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_RIGHT, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_DOWN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_LEFT, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_PLAYER_UP, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_GUARDIAN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_KEEPER, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_PERSON_MALE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_PERSON_FEMALE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_GUARD, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_WARLOCK_PURPLE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_NECROMANCER_APPENTICE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_NECROMANCER_MASTER, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DARKELF_ARCHER, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DARKELF_WARRIOR, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DARKELF_MAGE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_WARRIOR, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_AXEBEARER, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_MAGE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DWARF_HERO, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_WARRIOR, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_AXEBEARER, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_MAGE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_UNDEAD_DWARF_HERO, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_GOBLIN_PEON, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_GOBLIN_WARRIOR, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_GOBLIN_MAGE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_IMP_BLUE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_IMP_RED, x++, y);
		x = 0; y++;

		TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_PEON_GREEN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_WARRIOR_GREEN, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_PEON_RED, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ORGE_WARRIOR_RED, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_PEON, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_WARRIOR, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_HERO, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SKELETON_MAGE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SPRITE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_ORC_PEON, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ORC_WARRIOR, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ORC_HERO, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_ORC_MAGE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DEMON_PEON, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DEMON_HERO, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DEMON_MAGE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_FLAYER_WARRIOR, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_FLAYER_MAGE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SKULL, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_GOLEM_GREY, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_GOLEM_BROWN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_GOLEM_RED, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SLIME_BROWN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SLIME_GREEN, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_EYEBALL, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_VERMIN_BROWN, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SNAKE_GREEN, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_RUBBLE_PILE, x++, y);
		x = 0; y++;

		TCODConsole::mapAsciiCodeToFont(CHAR_SCORPIAN_YELLOW, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SCORPIAN_BLACK, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SPIDER_BLACK, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SPIDER_RED, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SPIDER_GREEN, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_PYTHON_RED, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_PYTHON_BROWN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_PYTHON_YELLOW, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_BAT_BROWN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_BAT_BLUE, x++, y);

		// Environment Tiles
		TCODConsole::mapAsciiCodeToFont(CHAR_TREE_A, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_TREE_B, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_TREE_C, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_TREE_D, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_TREE_E, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_TREE_F, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_TREE_G, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_A, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_B, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_C, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SHRUB_D, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_MUSHROOM, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_FLOWERS_WHITE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_FLOWERS_BLUE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_TEMPLE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_TOWN, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_CAVE, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_BED, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_TABLE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_BOOKCASE, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_CHAIR_RIGHT, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_CHAIR_LEFT, x++, y);
		x = 0; y++;

		// Minor Bosses (Upper Portion)
		TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_UR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_UR, x++, y);

		// Final Boss (Upper Portion)
		TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_UL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_UR, x++, y);
		x = 0; y++;

		// Minor Bosses (Lower Portion)
		TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_WHITE_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DEMONLORD_RED_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_CYCLOPS_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_RED_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_YELLOW_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREEN_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_BLUE_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_DRAGON_LARGE_GREY_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_MINOTAUR_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_LIZARD_GIANT_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_MEDUSA_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_FLYING_BRAIN_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_SLIMELORD_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_BEHOLDER_LR, x++, y);

		TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_BEHEMOTH_LR, x++, y);

		// Final Boss (Lower Portion)
		TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_LL, x++, y);
		TCODConsole::mapAsciiCodeToFont(CHAR_FINAL_BOSS_LR, x++, y);
	}

	virtual ~Engine()
	{
		if( game != NULL )
		{
			delete game;
			game = NULL;
		}

		if( map != NULL )
		{
			delete map;
			map = NULL;
		}

		if( menu != NULL )
		{
			delete menu;
			menu = NULL;
		}

		if( sound != NULL )
		{
			delete sound;
			sound = NULL;
		}

		if( player != NULL )
		{
			delete player;
			player = NULL;
		}
	}

	// Startup Engine
	void Startup(int narg, char *argv[]);

	// Shutdown Engine
	void Shutdown();

	// Generate Cave System
	void GenerateCaveSystem(int &id);

	// Update all the Modules
	bool Update();

	// Render all the Modules
	void Render();

	// Receive all messages
	bool Receive(const Message &msg);

	//----------------------------------------------------
	// Accessors
	//----------------------------------------------------
	void IncreaseFontID(){fontID++; Clamp<int>(fontID, 0, NFONTS - 1);}
	void DecreaseFontID(){fontID--; Clamp<int>(fontID, 0, NFONTS - 1);}
};

#endif