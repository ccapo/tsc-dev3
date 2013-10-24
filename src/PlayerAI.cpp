#include "Main.hpp"

bool PlayerAI::Update(Object *owner)
{
	const float elapsed = 1.0f/50.0f;
	int dx = 0, dy = 0;
	static int counter = 0;

	// Check if player is dead
	if( owner->entity && owner->entity->IsDead() ) return false;

	// Add ConditionList From Worn or Wielded Items
	owner->entity->addConditionList(owner);

	// Reset Player Stats
	owner->entity->stats = owner->entity->base_stats;

	// Update and Apply ConditionList
	owner->entity->updateConditionList(owner);

	//cout << owner->entity->stats.hpmax << ", " << owner->entity->stats.ap << ", " << owner->entity->stats.dp << ", " << owner->entity->stats.str << ", " << owner->entity->stats.spd << endl;
	//cout << owner->entity->stats.mpmax << ", " << owner->entity->stats.map << ", " << owner->entity->stats.mdp << ", " << owner->entity->stats.wil << ", " << owner->entity->stats.acu << endl;
	//cout << owner->entity->status.hp << ", " << owner->entity->status.mp << ", " << owner->entity->status.xp << ", " << owner->entity->status.xpnext << endl;
	//cout << endl;

	// Increment displacement
	owner->entity->displacement += elapsed*static_cast<float>(owner->entity->stats.spd);

	if( owner->entity->displacement >= 1.0f )
	{
      	owner->entity->displacement = 0.0f;

		if( !owner->entity->hasCondition(Condition::CONFUSION) )
		{
			if( TCODConsole::isKeyPressed(TCODK_UP) )
			{
				dy = -1;
				owner->sym.set(CHAR_PLAYER_UP,0);
			}
			if( TCODConsole::isKeyPressed(TCODK_DOWN) )
			{
				dy = +1;
				owner->sym.set(CHAR_PLAYER_DOWN,0);
			}
			if( TCODConsole::isKeyPressed(TCODK_LEFT) )
			{
				dx = -1;
				owner->sym.set(CHAR_PLAYER_LEFT,0);
			}
			if( TCODConsole::isKeyPressed(TCODK_RIGHT) )
			{
				dx = +1;
				owner->sym.set(CHAR_PLAYER_RIGHT,0);
			}
		}
		else
		{
			bool moved = false;
			moved = moved || TCODConsole::isKeyPressed(TCODK_UP);
			moved = moved || TCODConsole::isKeyPressed(TCODK_DOWN);
			moved = moved || TCODConsole::isKeyPressed(TCODK_LEFT);
			moved = moved || TCODConsole::isKeyPressed(TCODK_RIGHT);
			if( moved )
			{
				dx = RNG->getInt(-1, 1);
				dy = RNG->getInt(-1, 1);
				owner->sym.set(RNG->getInt(CHAR_PLAYER_RIGHT, CHAR_PLAYER_UP), 0);
			}
		}
	}

	MapData *mapdata = &engine->map->mapData[engine->mapID];
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			mapdata->RevertCell(owner->x.get(i), owner->y.get(i));
			mapdata->Activated(owner->x.get(i), owner->y.get(i), false);
		}
	}

	mapdata->Action(owner, owner->x.get(0) + dx, owner->y.get(0) + dy);

	//cout << engine->mapID << ", " << owner->entity->mapID << endl;
	if( engine->mapID != owner->entity->mapID )
	{
		if( engine->mapID == WORLD_MAP )
		{
			if( owner->entity->mapID >= TEMPLE_LIGHT && owner->entity->mapID <= TEMPLE_EARTH )
			{
				string tmp = "Entered ";
				tmp.append(engine->map->mapData[WORLD_MAP].LocationNames[owner->entity->mapID]);
				engine->menu->MessageLog(TCODColor::lightGrey, tmp.c_str());
				engine->mapID = owner->entity->mapID;
				Transmit->Send(engine, MSG_ENTERTEMPLE);
			}
			else if( owner->entity->mapID >= TOWN_01 && owner->entity->mapID <= TOWN_12 )
			{
				string tmp = "Entered ";
				tmp.append(engine->map->mapData[WORLD_MAP].LocationNames[owner->entity->mapID]);
				engine->menu->MessageLog(TCODColor::lightGrey, tmp.c_str());
				engine->mapID = owner->entity->mapID;
				Transmit->Send(engine, MSG_ENTERTOWN);
			}
			else
			{
				string tmp = "Entered ";
				tmp.append(engine->map->mapData[WORLD_MAP].LocationNames[owner->entity->mapID]);
				engine->menu->MessageLog(TCODColor::lightGrey, tmp.c_str());
				engine->mapID = owner->entity->mapID;
				Transmit->Send(engine, MSG_ENTERCAVE);
			}
		}

		if( owner->entity->mapID == WORLD_MAP )
		{
			string tmp = "Exited ";
			tmp.append(engine->map->mapData[WORLD_MAP].LocationNames[engine->mapID]);
			engine->menu->MessageLog(TCODColor::lightGrey, tmp.c_str());
			engine->mapID = owner->entity->mapID;
			Transmit->Send(engine, MSG_SAVEGAME);
		}

		engine->mapID = owner->entity->mapID;
	}

	return true;
}