#ifndef MAP_HPP
#define MAP_HPP
//------------------------------------------------------------------------
//
// Name: Map.hpp
//
// Desc: A class to implement a Map
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Feature.hpp"
#include "Module.hpp"
#include "StateManager.hpp"
#include "Message.hpp"
#include "MapStates.hpp"

class Cell
{
public:

	Feature *feature;			// Current Feature of this cell
	Feature *defaultFeature;	// Previous Feature of this cell

	friend void swap(Cell &first, Cell &second)
	{
		// enable ADL (not necessary in our case, but good practice)
		using std::swap;

		// by swapping the members of two classes,
		// the two classes are effectively swapped
		swap(first.feature, second.feature);
		swap(first.defaultFeature, second.defaultFeature);
	}

	Cell(): feature(NULL), defaultFeature(NULL) {}
	virtual ~Cell() {}

	Cell(const Cell &c)
	{
		if( c.feature != NULL )
		{
			feature = c.feature->clone();
			*feature = *(c.feature);
		}
		else
		{
			FloorFeature f = FloorFeature();
			feature = f.clone();
			*feature = f;
		}

		if( c.defaultFeature != NULL )
		{
			defaultFeature = c.defaultFeature->clone();
			*defaultFeature = *(c.defaultFeature);
		}
		else
		{
			FloorFeature f = FloorFeature();
			defaultFeature = f.clone();
			*defaultFeature = f;
		}
	}

	Cell &operator=(Cell c)
	{
		// Check for self-assignment
		if( this != &c ) swap(*this, c);
		return *this;
	}

	// Use these methods to initialize the features in each cell
	void SetFeature(Feature *pFeature)
	{
		feature = pFeature->clone();
		*feature = *pFeature;
	}

	// Use these methods to initialize the features in each cell
	void SetDefaultFeature(Feature *pFeature)
	{
		defaultFeature = pFeature->clone();
		*defaultFeature = *pFeature;
	}

	// Change feature back to the previous feature
	void RevertToDefaultFeature()
	{
		// Change feature to default feature
		feature = defaultFeature->clone();
		*feature = *defaultFeature;
	}
};

class MapData
{
public:

	vector<Cell> cells;

	// Background image, and its thumbnail
	TCODImage *img;
	TCODImage *imgThumb;

	int width, height, type;
	int nCreatures, nNpcs, nItems, nTraps;
	map<int, int> object_chances;
	TCODList<Object *> objects;

	vector<string> WeaponNames, ShieldNames, ArmourNames, AccessoryNames, LocationNames;

	friend void swap(MapData &first, MapData &second)
	{
		// enable ADL (not necessary in our case, but good practice)
		using std::swap;

		// by swapping the members of two classes,
		// the two classes are effectively swapped
		swap(first.cells, second.cells);

		swap(first.img, second.img);
		swap(first.imgThumb, second.imgThumb);

		swap(first.width, second.width);
		swap(first.height, second.height);
		swap(first.type, second.type);

		swap(first.nCreatures, second.nCreatures);
		swap(first.nNpcs, second.nNpcs);
		swap(first.nItems, second.nItems);
		swap(first.nTraps, second.nTraps);

		swap(first.object_chances, second.object_chances);
		swap(first.objects, second.objects);

		swap(first.WeaponNames, second.WeaponNames);
		swap(first.ShieldNames, second.ShieldNames);
		swap(first.ArmourNames, second.ArmourNames);
		swap(first.AccessoryNames, second.AccessoryNames);
		swap(first.LocationNames, second.LocationNames);
	}

	MapData(): img(NULL), imgThumb(NULL), width(DISPLAY_WIDTH), height(DISPLAY_HEIGHT), type(-1), nCreatures(10), nNpcs(0), nItems(4), nTraps(4) {}
	virtual ~MapData() {}

	MapData(const MapData &m): cells(m.cells), img(new TCODImage(m.img)), imgThumb(new TCODImage(m.imgThumb)), width(m.width), height(m.height), type(m.type), nCreatures(m.nCreatures), nNpcs(m.nNpcs), nItems(m.nItems), nTraps(m.nTraps), WeaponNames(m.WeaponNames), ShieldNames(m.ShieldNames), ArmourNames(m.ArmourNames), AccessoryNames(m.AccessoryNames), LocationNames(m.LocationNames) {}

	MapData &operator=(MapData m)
	{
		// Check for self-assignment
   		if( this != &m ) swap(*this, m);
		return *this;
   	}

	void Action(Object *owner, int x, int y);
	int FeatureType(int x, int y) const;
	int TrapType(int x, int y) const;
	TCODColor Colour(int x, int y) const;
	void Colour(int x, int y, TCODColor colour);
	bool Activated(int x, int y) const;
	void Activated(int x, int y, bool lvalue);
	bool Explored(int x, int y) const;
	void Explored(int x, int y, bool lvalue);
	void RevertCell(int x, int y);
	void SetFloor(int x, int y);
	void SetWall(int x, int y);
	void SetDoor(int x, int y);
	void SetTrap(int x, int y, int type, int mapID = -1, int xTo = -1, int yTo = -1);
	void SetCreature(int x, int y);
	void SetNpc(int x, int y);

	void GetItemChances(int caveType);
	void GetTrapChances(int caveType);
	void GetCreatureChances(int caveType);
	void AddWall(int x, int y, bool imprevious);
	void AddTunnelUp(int x, int y, int mapID, int xTo, int yTo);
	void AddTunnelDown(int x, int y, int mapID, int xTo, int yTo);
	void AddTunnelSurface(int x, int y, int mapID, int xTo, int yTo);
	void AddMapLocation(int x, int y, int mapID, int xTo, int yTo);
	void AddItem(int x, int y);
	void AddTrap(int x, int y);
	void AddCreature(int x, int y);
	void AddBoss(int x, int y);
	void AddNpc(int type, int x, int y);
	int RandomChoiceIndex(TCODList<int> chances);
	int RandomChoice(map<int, int> object_chances);

	void SendToBack(Object *object);
	bool IsObstructed(int x, int y) const;
	Object *GetObject(int x, int y) const;
	Object *GetEntity(int x, int y) const;
	Object *GetEntity(int id) const;

	// Generate Maps
	void GenerateMap(int locationID, int mapType);
};

class Map : public Module
{
private:

	// Copy constructor and assignment should be private
	Map(const Map&);
	Map &operator=(const Map&);

public:

	// An instance of the State Manager class
	StateManager<Map> *stateMgr;

	// Map Data
	vector<MapData> mapData;

	// The Map Constructor
	Map()
	{
		stateMgr = new StateManager<Map>(this);
		stateMgr->SetCurrentState(MapIdleState);

		for(int i = 0; i < NMAPS; i++)
		{
			MapData mapdata;
			mapData.push_back(mapdata);
		}
	}

	// The Map Destructor
	virtual ~Map()
	{
		if( stateMgr != NULL )
		{
			delete stateMgr;
			stateMgr = NULL;
		}
	}

	// Update the Map
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
	{
		return stateMgr->Update(elapsed, key, mouse);
	}

	// Render the Map
	void Render()
	{
		stateMgr->Render();
	}

	// Handle Messages for the Map
	bool Receive(const Message &msg)
	{
		return stateMgr->Receive(msg);
	}
};

#endif