#ifndef MAPSTATES_HPP
#define MAPSTATES_HPP
//------------------------------------------------------------------------
//
// Name: MapStates.hpp
//
// Desc: All the states that can be assigned to the Map class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class Map;

// Provide easy access
#define MapIdleState MapIdle::Instance()
#define MapWorldState MapWorld::Instance()
#define MapTempleState MapTemple::Instance()
#define MapTownState MapTown::Instance()
#define MapCaveState MapCave::Instance()

//------------------------------------------------------------------------
//
// This is the Idle State for the Map
//
//------------------------------------------------------------------------
class MapIdle : public State<Map>
{
private:

	MapIdle(){}
	
	// Copy constructor and assignment should be private
	MapIdle(const MapIdle&);
	MapIdle &operator=(const MapIdle&);

public:

	// This is a singleton
	static MapIdle *Instance();
	
	void Enter(Map *map){}
	bool Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Map *map);
	void Exit(Map *map){}
	bool Receive(Map *map, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the World State for the Map
//
//------------------------------------------------------------------------
class MapWorld : public State<Map>
{
private:

	MapWorld(){}
	
	// Copy constructor and assignment should be private
	MapWorld(const MapWorld&);
	MapWorld &operator=(const MapWorld&);

public:

	// This is a singleton
	static MapWorld *Instance();
	
	void Enter(Map *map);
	bool Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Map *map);
	void Exit(Map *map);
	bool Receive(Map *map, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Temple State for the Map
//
//------------------------------------------------------------------------
class MapTemple : public State<Map>
{
private:

	MapTemple(){}
	
	// Copy constructor and assignment should be private
	MapTemple(const MapTemple&);
	MapTemple &operator=(const MapTemple&);

public:

	// This is a singleton
	static MapTemple *Instance();
	
	void Enter(Map *map);
	bool Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Map *map);
	void Exit(Map *map);
	bool Receive(Map *map, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Town State for the Map
//
//------------------------------------------------------------------------
class MapTown : public State<Map>
{
private:
	
	MapTown(){}

	// Copy constructor and assignment should be private
	MapTown(const MapTown&);
	MapTown &operator=(const MapTown&);
 
public:

	// This is a singleton
	static MapTown *Instance();
	
	void Enter(Map *map);
	bool Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Map *map);
	void Exit(Map *map);
	bool Receive(Map *map, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Cave State for the Map
//
//------------------------------------------------------------------------
class MapCave : public State<Map>
{
private:
	
	MapCave(){}

	// Copy constructor and assignment should be private
	MapCave(const MapCave&);
	MapCave &operator=(const MapCave&);
 
public:

	// This is a singleton
	static MapCave *Instance();
	
	void Enter(Map *map);
	bool Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Map *map);
	void Exit(Map *map);
	bool Receive(Map *map, const Message &msg){return true;}

};

#endif