#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for SoundIdle
//
//------------------------------------------------------------------------
SoundIdle *SoundIdle::Instance()
{
	static SoundIdle instance;
	return &instance;
}
bool SoundIdle::Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundIdle::Render(Sound *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundMainMenu
//
//------------------------------------------------------------------------
SoundMainMenu *SoundMainMenu::Instance()
{
	static SoundMainMenu instance;
	return &instance;
}

void SoundMainMenu::Enter(Sound *sound){}
bool SoundMainMenu::Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundMainMenu::Render(Sound *sound){}
void SoundMainMenu::Exit(Sound *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundNew
//
//------------------------------------------------------------------------
SoundNew *SoundNew::Instance()
{
	static SoundNew instance;
	return &instance;
}

void SoundNew::Enter(Sound *sound){}
bool SoundNew::Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundNew::Render(Sound *sound){}
void SoundNew::Exit(Sound *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundWorld
//
//------------------------------------------------------------------------
SoundWorld *SoundWorld::Instance()
{
	static SoundWorld instance;
	return &instance;
}

void SoundWorld::Enter(Sound *sound){}
bool SoundWorld::Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundWorld::Render(Sound *sound){}
void SoundWorld::Exit(Sound *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundTemple
//
//------------------------------------------------------------------------
SoundTemple *SoundTemple::Instance()
{
	static SoundTemple instance;
	return &instance;
}

void SoundTemple::Enter(Sound *sound){}
bool SoundTemple::Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundTemple::Render(Sound *sound){}
void SoundTemple::Exit(Sound *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundTown
//
//------------------------------------------------------------------------
SoundTown *SoundTown::Instance()
{
	static SoundTown instance;
	return &instance;
}

void SoundTown::Enter(Sound *sound){}
bool SoundTown::Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundTown::Render(Sound *sound){}
void SoundTown::Exit(Sound *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundCave
//
//------------------------------------------------------------------------
SoundCave *SoundCave::Instance()
{
	static SoundCave instance;
	return &instance;
}

void SoundCave::Enter(Sound *sound){}
bool SoundCave::Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundCave::Render(Sound *sound){}
void SoundCave::Exit(Sound *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundRest
//
//------------------------------------------------------------------------
SoundRest *SoundRest::Instance()
{
	static SoundRest instance;
	return &instance;
}

void SoundRest::Enter(Sound *sound){}
bool SoundRest::Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void SoundRest::Render(Sound *sound)
{
	// Pause for Rest Music
#ifndef DEV
	usleep(1750000);
#endif
}
void SoundRest::Exit(Sound *sound){}

//------------------------------------------------------------------------
//
// Methods for SoundQuit
//
//------------------------------------------------------------------------
SoundQuit *SoundQuit::Instance()
{
	static SoundQuit instance;
	return &instance;
}

void SoundQuit::Enter(Sound *sound){}
bool SoundQuit::Update(Sound *sound, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return false;}
void SoundQuit::Render(Sound *sound){}
void SoundQuit::Exit(Sound *sound){}
