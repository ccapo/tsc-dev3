#ifndef GLOBAL_HPP
#define GLOBAL_HPP
//------------------------------------------------------------------------
//
// Name: Global.hpp
//
// Description: Global constants
//
// Author: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
//
// The Serpentine Caves
// Copyright (c) 2011, 2012 Christopher Claudio Capobianco
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Christopher Claudio Capobianco may not be used to endorse
//       or promote products derived from this software without specific prior
//       written permission.
//
// THIS SOFTWARE IS PROVIDED BY CHRISTOPHER CLAUDIO CAPOBIANCO ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL CHRISTOPHER CLAUDIO CAPOBIANCO BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Mingos' Noise Demo 2
// Copyright (c) 2010 Dominik Marczuk
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//     * Redistributions of source code must retain the above copyright
//       notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * The name of Dominik Marczuk may not be used to endorse or promote products
//       derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY DOMINIK MARCZUK ``AS IS'' AND ANY
// EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
// WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL DOMINIK MARCZUK BE LIABLE FOR ANY
// DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
// (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
// LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
// ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
// SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
//------------------------------------------------------------------------
#include <cassert>
#include <iomanip>
#include <iostream>
#include <limits>
#include <map>
#include <math.h>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string>
#include <time.h>
#include <typeinfo>
#include <unistd.h>
#include <vector>
#include <list>
#include "libtcod.hpp"
//#include "leaker.hpp"

using namespace std;

// Game Version
#define MAJOR_VERSION 0
#define MINOR_VERSION 4

// Save Game Magic Number
#define SAVEGAME_MAGIC_NUMBER 0xFD051E4F

// Save Game File Name
#define SAVEGAME_FILENAME "data/.save/savedgame.gz"

// Size of the Map Portion Shown On-Screen
#define DISPLAY_WIDTH 70
#define DISPLAY_HEIGHT 42
//#define DISPLAY_WIDTH 120
//#define DISPLAY_HEIGHT 72

// Size of the Window
#define SCREEN_WIDTH (DISPLAY_WIDTH)
#define SCREEN_HEIGHT (5*DISPLAY_HEIGHT/4 + 6)

// Size of the Map
#define MAP_WIDTH (2*DISPLAY_WIDTH)
#define MAP_HEIGHT (2*DISPLAY_HEIGHT)

// Size of the 2x Map
#define MAP_WIDTH2 (2*MAP_WIDTH)
#define MAP_HEIGHT2 (2*MAP_HEIGHT)
#define SCALE_FACTOR (2*MAP_WIDTH2/DISPLAY_WIDTH)

// Size of the Static Image Maps
#define IMAGE_WIDTH 70
#define IMAGE_HEIGHT 42
//#define IMAGE_WIDTH 120
//#define IMAGE_HEIGHT 72

// Size of the Static Image Maps
#define IMAGE_WIDTH2 (2*IMAGE_WIDTH)
#define IMAGE_HEIGHT2 (2*IMAGE_HEIGHT)

// Max. of Messages
#define NMSGS 8
#define PANEL_HEIGHT 7
#define BAR_WIDTH 20
#define MSG_X 2
#define MSG_HEIGHT (PANEL_HEIGHT - 1)

// Maximum Frame Rate
#define FPSMAX 25

// Number of Commands in Game Help
#define NHELP 10

// Range of the Height Map
#define HM_MIN 0.75f
#define HM_MAX 0.95f

// Max. Size of Lists
#define NITEMMAX 64
#define NCREATUREMAX 1024
#define NCORPSEMAX 1024
#define NPCMAX 64
#define NLOCATIONMAX 32

// Number of Map Regions
#define NREGIONS 4

// Number of Items per Map Region
#define NITEMS_REGION (NITEMS/NREGIONS)

// Number of Cave Regions
#define NCAVE_REGIONS 4

// Number of cave levels per region
#define NLEVELS_REGION (8/4)

// Max. number of movement patterns
#define PATTERNMAX 256

// Number of cells that border a cell
#define NBLOCK 9
#define NBORDER (NBLOCK - 1)

// Torch Information
#define TORCH_RADIUS 24.0f
#define SQUARED_TORCH_RADIUS (TORCH_RADIUS*TORCH_RADIUS)

// Number of Sound Channels
#define NCHANNEL 2

// Maximum Size for Character Strings
#define CHARMAX 128

// World Map Location Identifiers
enum WorldMapLocations
{
	WORLD_MAP,
	TEMPLE_LIGHT,
	TEMPLE_FIRE,
	TEMPLE_WATER,
	TEMPLE_WIND,
	TEMPLE_EARTH,
	TOWN_01,
	TOWN_02,
	TOWN_03,
	TOWN_04,
	TOWN_05,
	TOWN_06,
	TOWN_07,
	TOWN_08,
	TOWN_09,
	TOWN_10,
	TOWN_11,
	TOWN_12,
	CAVE_01,
	CAVE_02,
	CAVE_03,
	CAVE_04,
	CAVE_05,
	CAVE_06,
	CAVE_07,
	NWORLDMAPLOCATIONS
};

#define NTEMPLES 5
#define NTOWNS 12
#define NCAVES 7

// Map grid size
#define NSIZE 32
#define NMAPS (1 + NTEMPLES + NTOWNS + NCAVES*NCAVE_REGIONS*NLEVELS_REGION)

// Map Types
enum MapType
{
	WORLD_TYPE = -3,
	TEMPLE_TYPE = -2,
	TOWN_TYPE = -1,
	CAVETYPE_01,
	CAVETYPE_02,
	CAVETYPE_03,
	CAVETYPE_04,
	BOSS_TYPE,
	NMAPTYPES
};

// Font Types
enum FontType
{
	FONT_01,
	FONT_02,
	NFONTS
};

// List of Magic Types
enum MagicType
{
	MAGIC_LIGHT,
	MAGIC_FIRE,
	MAGIC_WATER,
	MAGIC_WIND,
	MAGIC_EARTH,
	NMAGIC
};

// List of Menu States
enum MenuStates
{
	STATE_01,
	STATE_02,
	STATE_03,
	STATE_04,
	STATE_05,
	NSTATES
};

// Main Menu Option Identifiers
enum MainMenu
{
	MAIN_NEW,
	MAIN_LOAD,
	MAIN_HELP,
	MAIN_QUIT,
	NMAIN
};

// Intro Page Identifiers
enum IntroPage
{
	INTRO_01,
	INTRO_02,
	NINTRO
};

// Game Menu Option Identifiers
enum GameMenu
{
	GAME_EQUIP,
	GAME_ITEMS,
	GAME_EXIT,
	NGAME
};

// Item Shop Menu Option Identifiers
enum ItemShopMenu
{
	ITEMSHOP_BUY,
	ITEMSHOP_SELL,
	ITEMSHOP_EXIT,
	NITEMSHOP
};

// Equip Shop Menu Option Identifiers
enum EquipShopMenu
{
	EQUIPSHOP_BUY,
	EQUIPSHOP_SELL,
	EQUIPSHOP_EXIT,
	NEQUIPSHOP
};

// Inn Menu Option Identifiers
enum InnMenu
{
	INN_STAY,
	INN_EXIT,
	NINN
};

// Ferry Menu Option Identifiers
enum FerryMenu
{
	FERRY_TAKE,
	FERRY_EXIT,
	NFERRY
};

enum StatType
{
	LEVELMIN = 1,
	LEVELMAX = 50,

	IQMIN = 50,
	IQMAX = 200,

	HPMIN = 25,
	HPMAX = 750,
	APMIN = 4,
	APMAX = 50,
	DPMIN = 2,
	DPMAX = 50,
	STRMIN = 10,
	STRMAX = 50,
	SPDMIN = 1,
	SPDMAX = FPSMAX,

	MPMIN = 15,
	MPMAX = 250,
	MAPMIN = 2,
	MAPMAX = 50,
	MDPMIN = 1,
	MDPMAX = 50,
	WILMIN = 2,
	WILMAX = 50,
	ACUMIN = 1,
	ACUMAX = 50
};

// Bodily Status Types
enum BodilyStatusType
{
	STATUS_DEAD,
	STATUS_DYING,
	STATUS_WOUNDED,
	STATUS_INJURED,
	STATUS_HEALTHY,
	NBODILYSTATUS
};

// Ailment Status Types
enum AilmentStatusType
{
	STATUS_BURDENED,
	STATUS_POISONED,
	STATUS_WEAKENED,
	STATUS_SLUGGISH,
	STATUS_FEEBLE,
	STATUS_CONFUSED,
	NAILMENTSTATUS
};

// Equipment Types
enum EquipType
{
	WEAPON,
	SHIELD,
	ARMOUR,
	ACCESSORY,
	NEQUIPTYPE
};

// Category Types
enum CategoryType
{
	CONSUMABLE,
	WEARABLE,
	WIELDABLE,
	MISC,
	NCATEGORIES
};

// Weapon Types
enum WeaponType
{
	WEAPON_01,
	WEAPON_02,
	WEAPON_03,
	WEAPON_04,
	WEAPON_05,
	WEAPON_06,
	WEAPON_07,
	WEAPON_08,
	WEAPON_09,
	NWEAPONS
};

// Shield Types
enum ShieldType
{
	SHIELD_01,
	SHIELD_02,
	SHIELD_03,
	SHIELD_04,
	SHIELD_05,
	SHIELD_06,
	SHIELD_07,
	SHIELD_08,
	SHIELD_09,
	NSHIELDS
};

// Armour Types
enum ArmourType
{
	ARMOUR_01,
	ARMOUR_02,
	ARMOUR_03,
	ARMOUR_04,
	ARMOUR_05,
	ARMOUR_06,
	ARMOUR_07,
	ARMOUR_08,
	ARMOUR_09,
	NARMOUR
};

// Accessory Types
enum AccessoryType
{
	ACCESSORY_01,
	ACCESSORY_02,
	ACCESSORY_03,
	ACCESSORY_04,
	ACCESSORY_05,
	ACCESSORY_06,
	ACCESSORY_07,
	ACCESSORY_08,
	ACCESSORY_09,
	NACCESSORY
};

// Item Types
enum ItemType
{
	ITEM_01,
	ITEM_02,
	ITEM_03,
	ITEM_04,
	ITEM_05,
	ITEM_06,
	ITEM_07,
	ITEM_08,
	ITEM_09,
	ITEM_10,
	ITEM_11,
	NITEMS
};

// Hide Types
enum HideType
{
	HIDE_01,
	HIDE_02,
	HIDE_03,
	HIDE_04,
	HIDE_05,
	HIDE_06,
	HIDE_07,
	HIDE_08,
	NHIDES
};

// AI Types
enum AIType
{
	AI_PLAYER,
	AI_NPC,
	AI_SKITTISH,
	AI_REGULAR,
	AI_AGGRESSIVE,
	AI_PATROLLER,
	AI_SPAWNER,
	AI_SEEKER,
	AI_BOSS,
	NAITYPES
};

// Feature Types
enum FeatureType
{
	FEATURE_FLOOR,
	FEATURE_WALL,
	FEATURE_DOOR,
	FEATURE_TRAP,
	FEATURE_CREATURE,
	FEATURE_NPC,
	NFEATURES
};

// Trap Types
enum TrapType
{
	TRAP_INVISIBLEBARRIER,
	TRAP_DARKTUNNEL,
	NTRAPS
};

// Message Types
enum MsgType
{
	MSG_DEFAULT = -1,

	// These messages are sent by the player or module to the game engine
	MSG_IDLE,
	MSG_PAUSE,
	MSG_NEWGAME,
	MSG_LOADGAME,
	MSG_SAVEGAME,
	MSG_QUITGAME,
	MSG_INTROGAME,
	MSG_BEGINGAME,
	MSG_GAMEHELP,
	MSG_ENTERWORLD,
	MSG_ENTERTEMPLE,
	MSG_ENTERTOWN,
	MSG_ENTERCAVE,
	MSG_GUARDIANDIALOG,
	MSG_NPCDIALOG,
	MSG_GAMEMENU,
	MSG_EQUIPINV,
	MSG_WEAPONINV,
	MSG_SHIELDINV,
	MSG_ARMOURINV,
	MSG_ACCESSORYINV,
	MSG_ITEMINV,
	MSG_ITEMSHOP,
	MSG_ITEMSHOPBUY,
	MSG_ITEMSHOPSELL,
	MSG_EQUIPSHOP,
	MSG_EQUIPSHOPBUY,
	MSG_EQUIPSHOPBUYWEAPON,
	MSG_EQUIPSHOPBUYSHIELD,
	MSG_EQUIPSHOPBUYARMOUR,
	MSG_EQUIPSHOPBUYACCESSORY,
	MSG_EQUIPSHOPSELL,
	MSG_EQUIPSHOPSELLWEAPON,
	MSG_EQUIPSHOPSELLSHIELD,
	MSG_EQUIPSHOPSELLARMOUR,
	MSG_EQUIPSHOPSELLACCESSORY,
	MSG_INNMENU,
	MSG_REST,
	MSG_FERRYMENU,
	MSG_FERRYTAKE,
	MSG_DEATH,
	
	// These messages are sent between entities
	MSG_PATROL,
	MSG_ATTACK,
	MSG_DEFEND,
	MSG_SAFE,
	MSG_THREAT
};

// List of Tile Character Types
enum CharType
{
	// Default Character Tile
	CHAR_DEFAULT = -1,

	// Stairs
	CHAR_STAIRS_UP = 256,
	CHAR_STAIRS_DOWN,

	CHAR_HOLE,

	// Water Animation
	CHAR_WATER_01,
	CHAR_WATER_02,

	// Lava Animation
	CHAR_LAVA_01,
	CHAR_LAVA_02,

	// Chest
	CHAR_CHEST_OPEN,
	CHAR_CHEST_CLOSED,

	// Potions
	CHAR_POTION_YELLOW,
	CHAR_POTION_RED,
	CHAR_POTION_GREEN,
	CHAR_POTION_BLUE,

	// Key
	CHAR_KEY,

	// Rings
	CHAR_RING_RED,
	CHAR_RING_GREEN,
	CHAR_RING_BLUE,
	CHAR_RING_RED_BIG,
	CHAR_RING_GREEN_BIG,
	CHAR_RING_BLUE_BIG,

	// Shields
	CHAR_SHIELD_BROWN,
	CHAR_SHIELD_GREY,
	CHAR_SHIELD_GOLD,

	// Swords
	CHAR_SWORD_BASIC,
	CHAR_SWORD_STEEL,
	CHAR_SWORD_GOLD,

	// Armour
	CHAR_ARMOUR_BROWN,
	CHAR_ARMOUR_YELLOW,
	CHAR_ARMOUR_RED,
	CHAR_ARMOUR_GREEN,
	CHAR_ARMOUR_BLUE,
	CHAR_ARMOUR_MITHRIL,

	// Magic Charge Bar
	CHAR_CHARGEBAR,

	// Player Tiles
	CHAR_PLAYER_RIGHT,
	CHAR_PLAYER_DOWN,
	CHAR_PLAYER_LEFT,
	CHAR_PLAYER_UP,

	// NPC Tiles
	CHAR_GUARDIAN,
	CHAR_KEEPER,
	CHAR_PERSON_MALE,
	CHAR_PERSON_FEMALE,

	// Monster Tiles
	CHAR_GUARD,

	CHAR_WARLOCK_PURPLE,

	CHAR_NECROMANCER_APPENTICE,
	CHAR_NECROMANCER_MASTER,

	CHAR_DARKELF_ARCHER,
	CHAR_DARKELF_WARRIOR,
	CHAR_DARKELF_MAGE,

	CHAR_DWARF_WARRIOR,
	CHAR_DWARF_AXEBEARER,
	CHAR_DWARF_MAGE,
	CHAR_DWARF_HERO,

	CHAR_UNDEAD_DWARF_WARRIOR,
	CHAR_UNDEAD_DWARF_AXEBEARER,
	CHAR_UNDEAD_DWARF_MAGE,
	CHAR_UNDEAD_DWARF_HERO,

	CHAR_GOBLIN_PEON,
	CHAR_GOBLIN_WARRIOR,
	CHAR_GOBLIN_MAGE,

	CHAR_IMP_BLUE,
	CHAR_IMP_RED,

	CHAR_ORGE_PEON_GREEN,
	CHAR_ORGE_WARRIOR_GREEN,

	CHAR_ORGE_PEON_RED,
	CHAR_ORGE_WARRIOR_RED,

	CHAR_SKELETON_PEON,
	CHAR_SKELETON_WARRIOR,
	CHAR_SKELETON_HERO,
	CHAR_SKELETON_MAGE,

	CHAR_SPRITE,

	CHAR_ORC_PEON,
	CHAR_ORC_WARRIOR,
	CHAR_ORC_HERO,
	CHAR_ORC_MAGE,

	CHAR_DEMON_PEON,
	CHAR_DEMON_HERO,
	CHAR_DEMON_MAGE,

	CHAR_FLAYER_WARRIOR,
	CHAR_FLAYER_MAGE,

	CHAR_SKULL,

	CHAR_GOLEM_GREY,
	CHAR_GOLEM_BROWN,
	CHAR_GOLEM_RED,

	CHAR_SLIME_BROWN,
	CHAR_SLIME_GREEN,

	CHAR_EYEBALL,

	CHAR_VERMIN_BROWN,

	CHAR_SNAKE_GREEN,

	CHAR_RUBBLE_PILE,

	CHAR_SCORPIAN_YELLOW,
	CHAR_SCORPIAN_BLACK,

	CHAR_SPIDER_BLACK,
	CHAR_SPIDER_RED,
	CHAR_SPIDER_GREEN,

	CHAR_PYTHON_RED,
	CHAR_PYTHON_BROWN,
	CHAR_PYTHON_YELLOW,

	CHAR_BAT_BROWN,
	CHAR_BAT_BLUE,

	// Environment Tiles
	CHAR_TREE_A,
	CHAR_TREE_B,
	CHAR_TREE_C,
	CHAR_TREE_D,
	CHAR_TREE_E,
	CHAR_TREE_F,
	CHAR_TREE_G,

	CHAR_SHRUB_A,
	CHAR_SHRUB_B,
	CHAR_SHRUB_C,
	CHAR_SHRUB_D,
	CHAR_MUSHROOM,
	CHAR_FLOWERS_WHITE,
	CHAR_FLOWERS_BLUE,

	CHAR_TEMPLE,
	CHAR_TOWN,
	CHAR_CAVE,

	CHAR_BED,
	CHAR_TABLE,
	CHAR_BOOKCASE,
	CHAR_CHAIR_RIGHT,
	CHAR_CHAIR_LEFT,

	// Minor Boss Tiles (Upper Portion)
	CHAR_DEMONLORD_WHITE_UL,
	CHAR_DEMONLORD_WHITE_UR,

	CHAR_DEMONLORD_RED_UL,
	CHAR_DEMONLORD_RED_UR,

	CHAR_CYCLOPS_UL,
	CHAR_CYCLOPS_UR,

	CHAR_DRAGON_LARGE_RED_UL,
	CHAR_DRAGON_LARGE_RED_UR,

	CHAR_DRAGON_LARGE_YELLOW_UL,
	CHAR_DRAGON_LARGE_YELLOW_UR,

	CHAR_DRAGON_LARGE_GREEN_UL,
	CHAR_DRAGON_LARGE_GREEN_UR,

	CHAR_DRAGON_LARGE_BLUE_UL,
	CHAR_DRAGON_LARGE_BLUE_UR,

	CHAR_DRAGON_LARGE_GREY_UL,
	CHAR_DRAGON_LARGE_GREY_UR,

	CHAR_MINOTAUR_UL,
	CHAR_MINOTAUR_UR,

	CHAR_LIZARD_GIANT_UL,
	CHAR_LIZARD_GIANT_UR,

	CHAR_MEDUSA_UL,
	CHAR_MEDUSA_UR,

	CHAR_FLYING_BRAIN_UL,
	CHAR_FLYING_BRAIN_UR,

	CHAR_SLIMELORD_UL,
	CHAR_SLIMELORD_UR,

	CHAR_BEHOLDER_UL,
	CHAR_BEHOLDER_UR,

	CHAR_BEHEMOTH_UL,
	CHAR_BEHEMOTH_UR,

	// Final Boss Tiles (Upper Portion)
	CHAR_FINAL_BOSS_UL,
	CHAR_FINAL_BOSS_UR,

	// Minor Boss Tiles (Lower Portion)
	CHAR_DEMONLORD_WHITE_LL,
	CHAR_DEMONLORD_WHITE_LR,

	CHAR_DEMONLORD_RED_LL,
	CHAR_DEMONLORD_RED_LR,

	CHAR_CYCLOPS_LL,
	CHAR_CYCLOPS_LR,

	CHAR_DRAGON_LARGE_RED_LL,
	CHAR_DRAGON_LARGE_RED_LR,

	CHAR_DRAGON_LARGE_YELLOW_LL,
	CHAR_DRAGON_LARGE_YELLOW_LR,

	CHAR_DRAGON_LARGE_GREEN_LL,
	CHAR_DRAGON_LARGE_GREEN_LR,

	CHAR_DRAGON_LARGE_BLUE_LL,
	CHAR_DRAGON_LARGE_BLUE_LR,

	CHAR_DRAGON_LARGE_GREY_LL,
	CHAR_DRAGON_LARGE_GREY_LR,

	CHAR_MINOTAUR_LL,
	CHAR_MINOTAUR_LR,

	CHAR_LIZARD_GIANT_LL,
	CHAR_LIZARD_GIANT_LR,

	CHAR_MEDUSA_LL,
	CHAR_MEDUSA_LR,

	CHAR_FLYING_BRAIN_LL,
	CHAR_FLYING_BRAIN_LR,

	CHAR_SLIMELORD_LL,
	CHAR_SLIMELORD_LR,

	CHAR_BEHOLDER_LL,
	CHAR_BEHOLDER_LR,

	CHAR_BEHEMOTH_LL,
	CHAR_BEHEMOTH_LR,

	// Final Boss Tiles (Lower Portion)
	CHAR_FINAL_BOSS_LL,
	CHAR_FINAL_BOSS_LR
};

// Macros
#define IN_RECTANGLE(x,y,w,h) ((unsigned)(x) < (unsigned)(w) && (unsigned)(y) < (unsigned)(h))

#define SQRDIST(x1,y1,x2,y2) (((x1)-(x2))*((x1)-(x2))+((y1)-(y2))*((y1)-(y2)))

#define ALL9FOV1XWALKABLE(x,y) (fov1x->isWalkable((x)-1,(y)-1) && fov1x->isWalkable((x),(y)-1) && fov1x->isWalkable((x)+1,(y)-1) && fov1x->isWalkable((x)-1,(y)) && fov1x->isWalkable((x),(y)) && fov1x->isWalkable((x)+1,(y)) && fov1x->isWalkable((x)-1,(y)+1) && fov1x->isWalkable((x),(y)+1) && fov1x->isWalkable((x)+1,(y)+1))

#define ANY9FOV1XWALKABLE(x,y) (fov1x->isWalkable((x)-1,(y)-1) || fov1x->isWalkable((x),(y)-1) || fov1x->isWalkable((x)+1,(y)-1) || fov1x->isWalkable((x)-1,(y)) || fov1x->isWalkable((x),(y)) || fov1x->isWalkable((x)+1,(y)) || fov1x->isWalkable((x)-1,(y)+1) || fov1x->isWalkable((x),(y)+1) || fov1x->isWalkable((x)+1,(y)+1))

#define ALL25FOV2XWALKABLE(x,y) (fov2x->isWalkable((x)-2,(y)-2) && fov2x->isWalkable((x)-1,(y)-2) && fov2x->isWalkable((x),(y)-2) && fov2x->isWalkable((x)+1,(y)-2) && fov2x->isWalkable((x)+2,(y)-2) && fov2x->isWalkable((x)-2,(y)-1) && fov2x->isWalkable((x)-1,(y)-1) && fov2x->isWalkable((x),(y)-1) && fov2x->isWalkable((x)+1,(y)-1) && fov2x->isWalkable((x)+2,(y)-1) && fov2x->isWalkable((x)-2,(y)) && fov2x->isWalkable((x)-1,(y)) && fov2x->isWalkable((x),(y)) && fov2x->isWalkable((x)+1,(y)) && fov2x->isWalkable((x)+2,(y)) && fov2x->isWalkable((x)-2,(y)+1) && fov2x->isWalkable((x)-1,(y)+1) && fov2x->isWalkable((x),(y)+1) && fov2x->isWalkable((x)+1,(y)+1) && fov2x->isWalkable((x)+2,(y)+1) && fov2x->isWalkable((x)-2,(y)+2) && fov2x->isWalkable((x)-1,(y)+2) && fov2x->isWalkable((x),(y)+2) && fov2x->isWalkable((x)+1,(y)+2) && fov2x->isWalkable((x)+2,(y)+2))

#define ANY25FOV2XWALKABLE(x,y) (fov2x->isWalkable((x)-2,(y)-2) || fov2x->isWalkable((x)-1,(y)-2) || fov2x->isWalkable((x),(y)-2) || fov2x->isWalkable((x)+1,(y)-2) || fov2x->isWalkable((x)+2,(y)-2) || fov2x->isWalkable((x)-2,(y)-1) || fov2x->isWalkable((x)-1,(y)-1) || fov2x->isWalkable((x),(y)-1) || fov2x->isWalkable((x)+1,(y)-1) || fov2x->isWalkable((x)+2,(y)-1) || fov2x->isWalkable((x)-2,(y)) || fov2x->isWalkable((x)-1,(y)) || fov2x->isWalkable((x),(y)) || fov2x->isWalkable((x)+1,(y)) || fov2x->isWalkable((x)+2,(y)) || fov2x->isWalkable((x)-2,(y)+1) || fov2x->isWalkable((x)-1,(y)+1) || fov2x->isWalkable((x),(y)+1) || fov2x->isWalkable((x)+1,(y)+1) || fov2x->isWalkable((x)+2,(y)+1) || fov2x->isWalkable((x)-2,(y)+2) || fov2x->isWalkable((x)-1,(y)+2) || fov2x->isWalkable((x),(y)+2) || fov2x->isWalkable((x)+1,(y)+2) || fov2x->isWalkable((x)+2,(y)+2))

#endif