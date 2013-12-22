#include "Main.hpp"

TCODColor Feature::darkGround = TCODColor(50, 50, 150);
TCODColor Feature::darkWall = TCODColor(0, 0, 100);

// Floor Feature: Action
void FloorFeature::Action(Object *owner, int x, int y)
{
	owner->xc = 0.0f; owner->yc = 0.0f;
	int x0 = owner->x.get(0), y0 = owner->y.get(0);
	for(int i = 0; i < owner->sym.size(); i++)
	{
	 	int dx = owner->x.get(i) - x0;
	 	int dy = owner->y.get(i) - y0;
	 	owner->x.set(x + dx,i);
	 	owner->y.set(y + dy,i);
	 	owner->xc += owner->x.get(i);
	 	owner->yc += owner->y.get(i);
	}

	if( owner->sym.size() > 0 )
	{
		owner->xc /= static_cast<float>(owner->sym.size());
		owner->yc /= static_cast<float>(owner->sym.size());
	}

	if( owner == engine->player )
	{
		MapData *mapdata = &engine->map->mapData[engine->mapID];
		if( !activated && engine->mapID > TOWN_12 )
		{
			activated = true;

			string buffer;
			buffer.clear();
			bool first = true;
			int nobjects = 0;

			// Look for any objects on the floor
			for(int i = mapdata->objects.size() - 1; i >= 0; i--)
			{
				Object *object = mapdata->objects.get(i);
				for(int j = 0; j < object->sym.size(); j++)
				{
					if( object->x.get(j) == x && object->y.get(j) == y )
					{
						nobjects++;
						if( !first )
						{
							buffer.append(" And ");
						}
						else
						{
							first = false;
						}
						buffer.append(object->name);
					}
				}
			}
			if( nobjects > 0 ) engine->menu->MessageLog(TCODColor::lightGrey, "There's %s Here", buffer.c_str());
		}

		Object *tunnel = mapdata->GetObject(x, y);
		if( tunnel && tunnel->traversable && engine->key.vk == TCODK_ENTER )
		{
			owner->entity->mapID = tunnel->traversable->mapID;
			owner->xc = 0.0f; owner->yc = 0.0f;
			int x0 = owner->x.get(0), y0 = owner->y.get(0);
			for(int i = 0; i < owner->sym.size(); i++)
			{
				int dx = owner->x.get(i) - x0;
				int dy = owner->y.get(i) - y0;
				owner->x.set(tunnel->traversable->xTo + dx,i);
				owner->y.set(tunnel->traversable->yTo + dy,i);
				owner->xc += owner->x.get(i);
				owner->yc += owner->y.get(i);
			}

			if( owner->sym.size() > 0 )
			{
				owner->xc /= static_cast<float>(owner->sym.size());
				owner->yc /= static_cast<float>(owner->sym.size());
			}
			engine->key.vk = TCODK_NONE;
		}
	}
}

// Wall Feature: Display bump message
void WallFeature::Action(Object *owner, int x, int y)
{
	if( owner == engine->player )
	{
		if( !activated )
		{
			activated = true;
			engine->menu->MessageLog(TCODColor::lightGrey, "You Bump Into A Wall");
		}
		else
		{
			Object *wall = engine->map->mapData[engine->mapID].GetEntity(x, y);
			if( wall ) owner->entity->Attack(owner, wall);
		}
	}
}

// Door Feature: Either open or move onto the cell
void DoorFeature::Action(Object *owner, int x, int y)
{
	if( open )
	{
		owner->xc = 0.0f; owner->yc = 0.0f;
		int x0 = owner->x.get(0), y0 = owner->y.get(0);
		for(int i = 0; i < owner->sym.size(); i++)
		{
			int dx = owner->x.get(i) - x0;
			int dy = owner->y.get(i) - y0;
			owner->x.set(x + dx,i);
			owner->y.set(y + dy,i);
			owner->xc += owner->x.get(i);
			owner->yc += owner->y.get(i);
		}

		if( owner->sym.size() > 0 )
		{
			owner->xc /= static_cast<float>(owner->sym.size());
			owner->yc /= static_cast<float>(owner->sym.size());
		}
	}
	else
	{
		open = true;
		engine->menu->MessageLog(TCODColor::lightGrey, "You Open A Door");
	}
}

// Trap Feature
TrapFeature::TrapFeature(int type, int mapID, int xTo, int yTo): Feature(FEATURE_TRAP, type, darkGround, mapID, xTo, yTo)
{
	switch( trapType )
	{
		case TRAP_INVISIBLEBARRIER:
		{
			flashColor = TCODColor::yellow;

			colour = TCODColor::white;

			condition1 = Condition(Condition::STUNNED);
			condition1.msgStart = "An Invisible Barrier Blocks Your Path";
			condition1.displayMsgStart = true;
			break;
		}
		case TRAP_DARKTUNNEL:
		{
			flashColor = TCODColor::red;

			colour = TCODColor::black;

			condition1 = Condition(Condition::STUNNED);
			condition1.msgStart = "You Plummet Down A Dark Tunnel!";
			condition1.displayMsgStart = true;

			condition2 = Condition(Condition::NONE);
			condition2.status.hp = -2;
			break;
		}
		default: break;
	}
}

// Trap Feature: Activate Trap
void TrapFeature::Action(Object *owner, int x, int y)
{
	// Reset the trap conditionList
	condition1.first = true;
	condition1.duration = FPSMAX/2;
	condition2.first = true;
	condition2.duration = FPSMAX/2;

	if( trapType != TRAP_INVISIBLEBARRIER )
	{
		owner->xc = 0.0f; owner->yc = 0.0f;
		int x0 = owner->x.get(0), y0 = owner->y.get(0);
		for(int i = 0; i < owner->sym.size(); i++)
		{
			int dx = owner->x.get(i) - x0;
			int dy = owner->y.get(i) - y0;
			owner->x.set(x + dx,i);
			owner->y.set(y + dy,i);
			owner->xc += owner->x.get(i);
			owner->yc += owner->y.get(i);
		}

		if( owner->sym.size() > 0 )
		{
			owner->xc /= static_cast<float>(owner->sym.size());
			owner->yc /= static_cast<float>(owner->sym.size());
		}
	}

	if( !activated || trapType == TRAP_INVISIBLEBARRIER )
	{
		if( trapType == TRAP_DARKTUNNEL )
		{
			engine->map->mapData[engine->mapID].Activated(xTo, yTo, true);
			owner->entity->mapID = mapID;
			owner->xc = 0.0f; owner->yc = 0.0f;
			int x0 = owner->x.get(0), y0 = owner->y.get(0);
			for(int i = 0; i < owner->sym.size(); i++)
			{
				int dx = owner->x.get(i) - x0;
				int dy = owner->y.get(i) - y0;
				owner->x.set(xTo + dx,i);
				owner->y.set(yTo + dy,i);
				owner->xc += owner->x.get(i);
				owner->yc += owner->y.get(i);
			}

			if( owner->sym.size() > 0 )
			{
				owner->xc /= static_cast<float>(owner->sym.size());
				owner->yc /= static_cast<float>(owner->sym.size());
			}
		}
		else
		{
			activated = true;
		}

		if( owner == engine->player && condition1.displayMsgStart ) engine->menu->MessageLog(TCODColor::green, "%s", condition1.msgStart.c_str());
		if( owner == engine->player && condition2.displayMsgStart ) engine->menu->MessageLog(TCODColor::green, "%s", condition2.msgStart.c_str());
		owner->entity->conditionList2.addToBack(condition1);
		owner->entity->conditionList2.addToBack(condition2);

		TCODConsole::root->setCharBackground(x, y + 3, flashColor);
		TCODConsole::root->flush();

		if( owner->entity->IsDead() )
		{
			for(int i = 0; i < owner->sym.size(); i++) engine->map->mapData[engine->mapID].SetCreature(owner->x.get(i), owner->y.get(i));
			owner->entity->Death(owner);
		}
	}
}

// Creature Feature: Attack!
void CreatureFeature::Action(Object *owner, int x, int y)
{
	// Attack the creature in this cell
	Object *creature = engine->map->mapData[engine->mapID].GetEntity(x, y);
	if( creature != NULL && creature != owner ) owner->entity->Attack(owner, creature);
}

// Npc Feature: Display Dialog
void NpcFeature::Action(Object *owner, int x, int y)
{
	if(owner == engine->player) engine->menu->MessageLog(TCODColor::lightGrey, "You converse with the NPC");
}
