#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for GameIdle
//
//------------------------------------------------------------------------
GameIdle *GameIdle::Instance()
{
	static GameIdle instance;
	return &instance;
}

bool GameIdle::Update(Game *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void GameIdle::Render(Game *game){}

//------------------------------------------------------------------------
//
// Methods for GameNew
//
//------------------------------------------------------------------------
GameNew *GameNew::Instance()
{
	static GameNew instance;
	return &instance;
}

bool GameNew::Update(Game *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	if( game->IsProgressComplete() )
	{
		game->progress = 0;
		Transmit->Send(engine, MSG_INTROGAME);
	}
	else
	{
		engine->GenerateCaveSystem(game->progress);
	}

	return true;
}

void GameNew::Render(Game *game){}

//------------------------------------------------------------------------
//
// Methods for GameLoad
//
//------------------------------------------------------------------------
GameLoad *GameLoad::Instance()
{
	static GameLoad instance;
	return &instance;
}

bool GameLoad::Update(Game *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	if( game->IsProgressComplete() )
	{
		game->progress = 0;
		game->inGame = true;
		Transmit->Send(engine, MSG_ENTERWORLD);
	}
	else
	{
		game->progress++;
	}

	return true;
}

void GameLoad::Render(Game *game){}

//------------------------------------------------------------------------
//
// Methods for GameSave
//
//------------------------------------------------------------------------
GameSave *GameSave::Instance()
{
	static GameSave instance;
	return &instance;
}

bool GameSave::Update(Game *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	if( game->IsProgressComplete() )
	{
		game->progress = 0;
		Transmit->Send(engine, MSG_ENTERWORLD);
	}
	else
	{
		game->progress++;
	}

	return true;
}

void GameSave::Render(Game *game){}

//------------------------------------------------------------------------
//
// Methods for GameQuit
//
//------------------------------------------------------------------------
GameQuit *GameQuit::Instance()
{
	static GameQuit instance;
	return &instance;
}

bool GameQuit::Update(Game *game, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return false;}
void GameQuit::Render(Game *game){}