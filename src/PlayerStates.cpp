#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for PlayerIdle
//
//------------------------------------------------------------------------
PlayerIdle *PlayerIdle::Instance()
{
	static PlayerIdle instance;
	return &instance;
}
void PlayerIdle::Enter(Player *player){}
bool PlayerIdle::Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void PlayerIdle::Render(Player *player)
{
	if( engine->game->inGame )
	{
		for(int i = 0; i < player->sym.size(); i++)
		{
			TCODConsole::root->setChar(player->x.get(i), player->y.get(i) + 3, player->sym.get(i));
			TCODConsole::root->setCharForeground(player->x.get(i), player->y.get(i) + 3, player->colour);
		}
	}
}

//------------------------------------------------------------------------
//
// Methods for PlayerIntro
//
//------------------------------------------------------------------------
PlayerIntro *PlayerIntro::Instance()
{
	static PlayerIntro instance;
	return &instance;
}

void PlayerIntro::Enter(Player *player){}
bool PlayerIntro::Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void PlayerIntro::Render(Player *player)
{
	for(int i = 0; i < player->sym.size(); i++)
	{
		TCODConsole::root->setChar(player->x.get(i), player->y.get(i) + 3, player->sym.get(i));
		TCODConsole::root->setCharForeground(player->x.get(i), player->y.get(i) + 3, player->colour);
	}
}

//------------------------------------------------------------------------
//
// Methods for PlayerWorld
//
//------------------------------------------------------------------------
PlayerWorld *PlayerWorld::Instance()
{
	static PlayerWorld instance;
	return &instance;
}

void PlayerWorld::Enter(Player *player){}

bool PlayerWorld::Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = false;

	if( player->entity->ai != NULL ) status = player->entity->ai->Update(player);

	switch( key.vk )
	{
		case TCODK_PAUSE:
		{
			Transmit->Send(engine, MSG_PAUSE);
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(engine, MSG_GAMEMENU);
			break;
		}
		case TCODK_CONTROL:
		{
			engine->menu->IncrementMagicID();
			break;
		}
		case TCODK_BACKSPACE:
  		{
    		// Save a screenshot
    		TCODSystem::saveScreenshot(NULL);
			break;
  		}
		case TCODK_CHAR:
		{
			switch( key.c )
			{
				case '?':
				{
					Transmit->Send(engine, MSG_GAMEHELP);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	key.vk = TCODK_NONE;
	key.c = 0;
	return status;
}

void PlayerWorld::Render(Player *player)
{
	for(int i = 0; i < player->sym.size(); i++)
	{
		TCODConsole::root->setChar(player->x.get(i), player->y.get(i) + 3, player->sym.get(i));
		TCODConsole::root->setCharForeground(player->x.get(i), player->y.get(i) + 3, player->colour);
	}
}

//------------------------------------------------------------------------
//
// Methods for PlayerTemple
//
//------------------------------------------------------------------------
PlayerTemple *PlayerTemple::Instance()
{
	static PlayerTemple instance;
	return &instance;
}

void PlayerTemple::Enter(Player *player){}

bool PlayerTemple::Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = false;

	if( player->entity->ai != NULL ) status = player->entity->ai->Update(player);

	switch( key.vk )
	{
		case TCODK_PAUSE:
		{
			Transmit->Send(engine, MSG_PAUSE);
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(engine, MSG_GAMEMENU);
			break;
		}
		case TCODK_CONTROL:
		{
			engine->menu->IncrementMagicID();
			break;
		}
		case TCODK_BACKSPACE:
  		{
    		// Save a screenshot
    		TCODSystem::saveScreenshot(NULL);
			break;
  		}
		case TCODK_CHAR:
		{
			switch( key.c )
			{
				case '?':
				{
					Transmit->Send(engine, MSG_GAMEHELP);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	key.vk = TCODK_NONE;
	key.c = 0;
	return status;
}

void PlayerTemple::Render(Player *player)
{
	for(int i = 0; i < player->sym.size(); i++)
	{
		TCODConsole::root->setChar(player->x.get(i), player->y.get(i) + 3, player->sym.get(i));
		TCODConsole::root->setCharForeground(player->x.get(i), player->y.get(i) + 3, player->colour);
	}
}

//------------------------------------------------------------------------
//
// Methods for PlayerTown
//
//------------------------------------------------------------------------
PlayerTown *PlayerTown::Instance()
{
	static PlayerTown instance;
	return &instance;
}

void PlayerTown::Enter(Player *player){}

bool PlayerTown::Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = false;

	if( player->entity->ai != NULL ) status = player->entity->ai->Update(player);

	switch( key.vk )
	{
		case TCODK_PAUSE:
		{
			Transmit->Send(engine, MSG_PAUSE);
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(engine, MSG_GAMEMENU);
			break;
		}
		case TCODK_CONTROL:
		{
			engine->menu->IncrementMagicID();
			break;
		}
		case TCODK_BACKSPACE:
		{
    		// Save a screenshot
    		TCODSystem::saveScreenshot(NULL);
			break;
  		}
		case TCODK_CHAR:
		{
			switch( key.c )
			{
				case 'i':
				{
					Transmit->Send(engine, MSG_ITEMSHOP);
					break;
				}
				case 'e':
				{
					Transmit->Send(engine, MSG_EQUIPSHOP);
					break;
				}
				case 'n':
				{
					Transmit->Send(engine, MSG_INNMENU);
					break;
				}
				case 'f':
				{
					Transmit->Send(engine, MSG_FERRYMENU);
					break;
				}
				case '?':
				{
					Transmit->Send(engine, MSG_GAMEHELP);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	key.vk = TCODK_NONE;
	key.c = 0;
	return status;
}

void PlayerTown::Render(Player *player)
{
	for(int i = 0; i < player->sym.size(); i++)
	{
		TCODConsole::root->setChar(player->x.get(i), player->y.get(i) + 3, player->sym.get(i));
		TCODConsole::root->setCharForeground(player->x.get(i), player->y.get(i) + 3, player->colour);
	}
}

//------------------------------------------------------------------------
//
// Methods for PlayerCave
//
//------------------------------------------------------------------------
PlayerCave *PlayerCave::Instance()
{
	static PlayerCave instance;
	return &instance;
}

void PlayerCave::Enter(Player *player){}

bool PlayerCave::Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = false;

	// Check player's status
	if( player->entity->status.hp <= 0 )
	{
		player->sym.set(CHAR_SKULL,0);
		player->colour = TCODColor::darkRed;
		engine->menu->MessageLog(TCODColor::darkRed, "You Died");
		Transmit->Send(engine, MSG_DEATH);
		key.vk = TCODK_NONE;
		key.c = 0;
		return status;
	}

	if( player->entity->ai != NULL ) status = player->entity->ai->Update(player);

	switch( key.vk )
	{
		case TCODK_INSERT:
		{
			player->entity->status.hp -= 1;
			break;
		}
		case TCODK_DELETE:
		{
			player->entity->status.mp -= 1;
			break;
		}
		case TCODK_PAUSE:
		{
			Transmit->Send(engine, MSG_PAUSE);
			break;
		}
		case TCODK_ESCAPE:
		{
			Transmit->Send(engine, MSG_GAMEMENU);
			break;
		}
		case TCODK_CONTROL:
		{
			engine->menu->IncrementMagicID();
			break;
		}
		case TCODK_BACKSPACE:
		{
			// Save a screenshot
			TCODSystem::saveScreenshot(NULL);
			break;
		}
		case TCODK_CHAR:
		{
			switch( key.c )
			{
				case '?':
				{
					Transmit->Send(engine, MSG_GAMEHELP);
					break;
				}
				default: break;
			}
			break;
		}
		default: break;
	}
	key.vk = TCODK_NONE;
	key.c = 0;
	return status;
}

void PlayerCave::Render(Player *player)
{
	for(int i = 0; i < player->sym.size(); i++)
	{
		TCODConsole::root->setChar(player->x.get(i), player->y.get(i) + 3, player->sym.get(i));
		TCODConsole::root->setCharForeground(player->x.get(i), player->y.get(i) + 3, player->colour);
	}
}

//------------------------------------------------------------------------
//
// Methods for PlayerRest
//
//------------------------------------------------------------------------
PlayerRest *PlayerRest::Instance()
{
	static PlayerRest instance;
	return &instance;
}

void PlayerRest::Enter(Player *player){}

bool PlayerRest::Update(Player *player, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	bool status = true;
	if(player->entity->status.hp < player->entity->stats.hpmax)
	{
		player->entity->status.hp = player->entity->stats.hpmax;
		player->entity->status.mp = player->entity->stats.mpmax;
	}
	else	
	{
		engine->menu->MessageLog(TCODColor::lightGrey, "Rested at Town Inn");
		Transmit->Send(engine, MSG_REST);
	}
	key.vk = TCODK_NONE;
	key.c = 0;
	return status;
}

void PlayerRest::Render(Player *player){}