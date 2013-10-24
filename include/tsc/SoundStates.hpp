#ifndef SOUNDSTATES_HPP
#define SOUNDSTATES_HPP
//------------------------------------------------------------------------
//
// Name: SoundStates.hpp
//
// Desc: All the states that can be assigned to the Sound class
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

class Sound;

// Provide easy access
#define SoundIdleState SoundIdle::Instance()
#define SoundMainMenuState SoundMainMenu::Instance()
#define SoundNewState SoundNew::Instance()
#define SoundWorldState SoundWorld::Instance()
#define SoundTempleState SoundTemple::Instance()
#define SoundTownState SoundTown::Instance()
#define SoundCaveState SoundCave::Instance()
#define SoundRestState SoundRest::Instance()
#define SoundQuitState SoundQuit::Instance()

//------------------------------------------------------------------------
//
// This is the Idle State for the Sound
//
//------------------------------------------------------------------------
class SoundIdle : public State<Sound>
{
private:
	
	SoundIdle(){}

	// Copy constructor and assignment should be private
	SoundIdle(const SoundIdle&);
	SoundIdle &operator=(const SoundIdle&);
 
public:

	// This is a singleton
	static SoundIdle *Instance();
	
	void Enter(Sound *sound){}
	bool Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Sound *sound);
	void Exit(Sound *sound){}
	bool Receive(Sound *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Main Menu State for the Sound
//
//------------------------------------------------------------------------
class SoundMainMenu : public State<Sound>
{
private:
	
	SoundMainMenu(){}

	// Copy constructor and assignment should be private
	SoundMainMenu(const SoundMainMenu&);
	SoundMainMenu &operator=(const SoundMainMenu&);
 
public:

	// This is a singleton
	static SoundMainMenu *Instance();
	
	void Enter(Sound *sound);
	bool Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Sound *sound);
	void Exit(Sound *sound);
	bool Receive(Sound *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the New Game State for the Sound
//
//------------------------------------------------------------------------
class SoundNew : public State<Sound>
{
private:

	SoundNew(){}
	
	// Copy constructor and assignment should be private
	SoundNew(const SoundNew&);
	SoundNew &operator=(const SoundNew&);

public:

	// This is a singleton
	static SoundNew *Instance();
	
	void Enter(Sound *sound);
	bool Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Sound *sound);
	void Exit(Sound *sound);
	bool Receive(Sound *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the World State for the Sound
//
//------------------------------------------------------------------------
class SoundWorld : public State<Sound>
{
private:

	SoundWorld(){}
	
	// Copy constructor and assignment should be private
	SoundWorld(const SoundWorld&);
	SoundWorld &operator=(const SoundWorld&);

public:

	// This is a singleton
	static SoundWorld *Instance();
	
	void Enter(Sound *sound);
	bool Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Sound *sound);
	void Exit(Sound *sound);
	bool Receive(Sound *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Temple State for the Sound
//
//------------------------------------------------------------------------
class SoundTemple : public State<Sound>
{
private:
	
	SoundTemple(){}

	// Copy constructor and assignment should be private
	SoundTemple(const SoundTemple&);
	SoundTemple &operator=(const SoundTemple&);
 
public:

	// This is a singleton
	static SoundTemple *Instance();
	
	void Enter(Sound *sound);
	bool Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Sound *sound);
	void Exit(Sound *sound);
	bool Receive(Sound *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Town State for the Sound
//
//------------------------------------------------------------------------
class SoundTown : public State<Sound>
{
private:
	
	SoundTown(){}

	// Copy constructor and assignment should be private
	SoundTown(const SoundTown&);
	SoundTown &operator=(const SoundTown&);
 
public:

	// This is a singleton
	static SoundTown *Instance();
	
	void Enter(Sound *sound);
	bool Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Sound *sound);
	void Exit(Sound *sound);
	bool Receive(Sound *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Cave State for the Sound
//
//------------------------------------------------------------------------
class SoundCave : public State<Sound>
{
private:
	
	SoundCave(){}

	// Copy constructor and assignment should be private
	SoundCave(const SoundCave&);
	SoundCave &operator=(const SoundCave&);
 
public:

	// This is a singleton
	static SoundCave *Instance();
	
	void Enter(Sound *sound);
	bool Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Sound *sound);
	void Exit(Sound *sound);
	bool Receive(Sound *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Rest State for the Sound
//
//------------------------------------------------------------------------
class SoundRest : public State<Sound>
{
private:
	
	SoundRest(){}

	// Copy constructor and assignment should be private
	SoundRest(const SoundRest&);
	SoundRest &operator=(const SoundRest&);
 
public:

	// This is a singleton
	static SoundRest *Instance();
	
	void Enter(Sound *sound);
	bool Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Sound *sound);
	void Exit(Sound *sound);
	bool Receive(Sound *sound, const Message &msg){return true;}

};

//------------------------------------------------------------------------
//
// This is the Quit State for the Sound
//
//------------------------------------------------------------------------
class SoundQuit : public State<Sound>
{
private:
	
	SoundQuit(){}

	// Copy constructor and assignment should be private
	SoundQuit(const SoundQuit&);
	SoundQuit &operator=(const SoundQuit&);
 
public:

	// This is a singleton
	static SoundQuit *Instance();
	
	void Enter(Sound *sound);
	bool Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	void Render(Sound *sound);
	void Exit(Sound *sound);
	bool Receive(Sound *sound, const Message &msg){return true;}

};

#endif