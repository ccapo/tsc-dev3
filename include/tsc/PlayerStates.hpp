#ifndef PLAYERSTATES_HPP
#define PLAYERSTATES_HPP
//------------------------------------------------------------------------
//
// Name: PlayerStates.hpp
//
// Desc: All the states that can be assigned to the Player class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Message.hpp"
#include "State.hpp"
#include "Player.hpp"

class Player;

// Provide easy access
#define PlayerIdleState PlayerIdle::Instance()
#define PlayerIntroState PlayerIntro::Instance()
#define PlayerWorldState PlayerWorld::Instance()
#define PlayerTempleState PlayerTemple::Instance()
#define PlayerTownState PlayerTown::Instance()
#define PlayerCaveState PlayerCave::Instance()
#define PlayerRestState PlayerRest::Instance()

//-------------------------------------------------------------------------
//
// In this state the Player is Idle
//
//-------------------------------------------------------------------------
class PlayerIdle : public State<Player>
{
private:
	
	PlayerIdle(){}

	// Copy constructor and assignment should be private
	PlayerIdle(const PlayerIdle&);
	PlayerIdle &operator=(const PlayerIdle&);
 
public:

	// This is a singleton
	static PlayerIdle *Instance();

	void Enter(Player *player);
	bool Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Player *player);
	void Exit(Player *player){}
	bool Receive(Player *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the Introduction
//
//-------------------------------------------------------------------------
class PlayerIntro : public State<Player>
{
private:
	
	PlayerIntro(){}

	// Copy constructor and assignment should be private
	PlayerIntro(const PlayerIntro&);
	PlayerIntro &operator=(const PlayerIntro&);
 
public:

	// This is a singleton
	static PlayerIntro *Instance();

	void Enter(Player *player);
	bool Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Player *player);
	void Exit(Player *player){}
	bool Receive(Player *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the World Map
//
//-------------------------------------------------------------------------
class PlayerWorld : public State<Player>
{
private:
	
	PlayerWorld(){}

	// Copy constructor and assignment should be private
	PlayerWorld(const PlayerWorld&);
	PlayerWorld &operator=(const PlayerWorld&);
 
public:

	// This is a singleton
	static PlayerWorld *Instance();

	void Enter(Player *player);
	bool Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Player *player);
	void Exit(Player *player){}
	bool Receive(Player *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the Temple Map
//
//-------------------------------------------------------------------------
class PlayerTemple : public State<Player>
{
private:
	
	PlayerTemple(){}

	// Copy constructor and assignment should be private
	PlayerTemple(const PlayerTemple&);
	PlayerTemple &operator=(const PlayerTemple&);
 
public:

	// This is a singleton
	static PlayerTemple *Instance();

	void Enter(Player *player);
	bool Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Player *player);
	void Exit(Player *player){}
	bool Receive(Player *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the Town Map
//
//-------------------------------------------------------------------------
class PlayerTown : public State<Player>
{
private:
	
	PlayerTown(){}

	// Copy constructor and assignment should be private
	PlayerTown(const PlayerTown&);
	PlayerTown &operator=(const PlayerTown&);
 
public:

	// This is a singleton
	static PlayerTown *Instance();
	void Enter(Player *player);
	bool Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Player *player);
	void Exit(Player *player){}
	bool Receive(Player *player, const Message &msg){return true;}

};

//-------------------------------------------------------------------------
//
// In this state the Player is in the Cave Map
//
//-------------------------------------------------------------------------
class PlayerCave : public State<Player>
{
private:
	
	PlayerCave(){}

	// Copy constructor and assignment should be private
	PlayerCave(const PlayerCave&);
	PlayerCave &operator=(const PlayerCave&);
 
public:

	// This is a singleton
	static PlayerCave *Instance();

	void Enter(Player *player);
	bool Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Player *player);
	void Exit(Player *player){}
	bool Receive(Player *player, const Message &msg){return true;}

};

//----------------------------------------------------------------------------
//
// In this state the Player is at Rest
//
//----------------------------------------------------------------------------
class PlayerRest : public State<Player>
{
private:
	
	PlayerRest(){}

	// Copy constructor and assignment should be private
	PlayerRest(const PlayerRest&);
	PlayerRest &operator=(const PlayerRest&);
 
public:

	// This is a singleton
	static PlayerRest *Instance();

	void Enter(Player *player);
	bool Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Player *player);
	void Exit(Player *player){}
	bool Receive(Player *player, const Message &msg){return true;}

};

#endif