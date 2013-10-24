#include "Main.hpp"

bool CreatureAI::Update(Object *owner)
{
	const float elapsed = 1.0f/50.0f;

	if( owner->entity && owner->entity->IsDead() ) return false;

	// Add ConditionList From Worn or Wielded Items
	owner->entity->addConditionList(owner);

	// Reset Creature Stats
	owner->entity->stats = owner->entity->base_stats;

	// Update and Apply ConditionList
	owner->entity->updateConditionList(owner);

	// Increment displacement
	owner->entity->displacement += elapsed*static_cast<float>(owner->entity->stats.spd);

	// Increment spawn delay
	owner->entity->ai->spawnDelay += elapsed*owner->entity->ai->spawnRate;

	if( owner->entity->displacement >= 1.0f )
	{
      	owner->entity->displacement = 0.0f;

		switch( type )
		{
			case AI_SKITTISH:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target closest entity
					Object *target = ClosestEntity(owner);
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							RunAway(owner, target);
						}
						else
						{
							RandomWalk(owner);
						}
					}
					else
					{
						RandomWalk(owner);
					}
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case AI_REGULAR:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target Player Only
					Object *target = engine->player;
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							ChaseOrAttack(owner, target);
						}
						else
						{
							RandomWalk(owner);
						}
					}
					else
					{
						RandomWalk(owner);
					}
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case AI_AGGRESSIVE:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target closest entity
					Object *target = ClosestEntity(owner);
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							ChaseOrAttack(owner, target);
						}
						else
						{
							RandomWalk(owner);
						}
					}
					else
					{
						RandomWalk(owner);
					}
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case AI_PATROLLER:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target Player Only
					Object *target = engine->player;
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							ChaseOrAttack(owner, target);
						}
						else
						{
							MoveToTarget(owner);
						}
					}
					else
					{
						MoveToTarget(owner);
					}
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case AI_SPAWNER:
			{
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					// Target Player Only
					Object *target = engine->player;
					if( target && !target->entity->IsDead() )
					{
						float dx = owner->xc - target->xc, dy = owner->yc - target->yc, d = sqrtf(dx*dx + dy*dy);
						if( d < 10.0f )
						{
							ChaseOrAttack(owner, target);
						}
						else
						{
							RandomWalk(owner);
						}
					}
					else
					{
						RandomWalk(owner);
					}

					// If number of subordinates is less than max, then spawn more
					if( owner->entity->ai->subordinates.size() < owner->entity->ai->nMaxSubordinates )
					{
						owner->entity->ai->spawnDelay = MIN(owner->entity->ai->spawnDelay, 1.0f);

						if( owner->entity->ai->spawnDelay >= 1.0f )
						{
					      	owner->entity->ai->spawnDelay = 0.0f;

							SpawnSubordinates(owner);
						}
					}
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			case AI_SEEKER:
			{
				// Target Player Only
				Object *target = engine->player;
				if( !owner->entity->hasCondition(Condition::CONFUSION) )
				{
					ChaseOrAttack(owner, target);
				}
				else
				{
					RandomWalk(owner);
				}
				break;
			}
			default: break;
		}
	}

	return true;
}

Object *CreatureAI::ClosestEntity(Object *owner) const
{
	int imin = -1;
	float dmin = 9999.0f;
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	// Search the object list first
	for(int i = mapdata->objects.size() - 1; i >= 0; i--)
	{
		Object *object = mapdata->objects.get(i);
		if( object != owner && object->entity && object->entity->type != Entity::INANIMATE && !object->entity->IsDead() )
		{
			float dx = owner->xc - object->xc, dy = owner->yc - object->yc, d = sqrtf(dx*dx + dy*dy);
			if( d < dmin )
			{
				dmin = d;
				imin = i;
			}
		}
	}

	// Search for the player
	float dx = owner->xc - engine->player->xc, dy = owner->yc - engine->player->yc, d = sqrtf(dx*dx + dy*dy);
	if( d < dmin )
	{
		dmin = d;
		imin = mapdata->objects.size() + 1;
	}

	if( imin >= 0 )
	{
		Object *object;
		if( imin < mapdata->objects.size() )
		{
			object = mapdata->objects.get(imin);
		}
		else
		{
			object = engine->player;
		}
		return object;
	}
	else
	{
		return NULL;
	}
}

void CreatureAI::RunAway(Object *owner, Object *target)
{
	int ox = owner->x.get(0), oy = owner->y.get(0);
	int dx = target->x.get(0) - ox;
	int dy = target->y.get(0) - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = sqrtf(dx*dx + dy*dy);
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	owner->entity->ai->arrived = true;

				//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
	Stats stats = Stats(0, 0, 0, 0, 15, 0, 0, 0, 0, 0);
				//  Status(hp, mp, xpnext)
	Status status = Status(0, 0, 0);
	Condition condition = Condition(Condition::NONE, 0, -1, stats, status, "msgStart", "msgStop");
	owner->entity->conditionList2.addToBack(condition);

	if( distance > sqrt(2.0f) )
	{
		dx = (int)(round(dx/distance));
		dy = (int)(round(dy/distance));
		if( !mapdata->IsObstructed(ox - dx, oy - dy) )
		{
			ox -= dx;
			oy -= dy;
		}
		else if( !mapdata->IsObstructed(ox - stepdx, oy) )
		{
			ox -= stepdx;
		}
		else if( !mapdata->IsObstructed(ox, oy - stepdy) )
		{
			oy -= stepdy;
		}
	}

	dx = ox - owner->x.get(0);
	dy = oy - owner->y.get(0);
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			mapdata->RevertCell(owner->x.get(i), owner->y.get(i));
			mapdata->Activated(owner->x.get(i), owner->y.get(i), false);
		}
		mapdata->Action(owner, ox, oy);
		if( !owner->entity->IsDead() ) for(int i = 0; i < owner->sym.size(); i++) mapdata->SetCreature(owner->x.get(i), owner->y.get(i));
	}

	if( distance <= sqrt(2.0f) ) owner->entity->Attack(owner, target);
}

void CreatureAI::RandomWalk(Object *owner)
{
	const int dx[NBLOCK] = {-1,  0, +1, -1, 0, +1, -1,  0, +1};
	const int dy[NBLOCK] = {-1, -1, -1,  0, 0,  0, +1, +1, +1};
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	owner->entity->ai->arrived = true;

	int i = RNG->getInt(0, NBLOCK - 1);
	owner->obstructs = false;
	bool obstructed = mapdata->IsObstructed(owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
	for(int j = 1; j < owner->sym.size(); j++)
	{
		obstructed = obstructed || mapdata->IsObstructed(owner->x.get(j) + dx[i], owner->y.get(j) + dy[i]);
	}
	while( obstructed )
	{
		i = RNG->getInt(0, NBLOCK - 1);
		obstructed = mapdata->IsObstructed(owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
		for(int j = 1; j < owner->sym.size(); j++)
		{
			obstructed = obstructed || mapdata->IsObstructed(owner->x.get(j) + dx[i], owner->y.get(j) + dy[i]);
		}
	}
	owner->obstructs = true;

	if( dx[i] != 0 || dy[i] != 0 )
	{
		for(int j = 0; j < owner->sym.size(); j++)
		{
			mapdata->RevertCell(owner->x.get(j), owner->y.get(j));
			mapdata->Activated(owner->x.get(j), owner->y.get(j), false);
		}
		mapdata->Action(owner, owner->x.get(0) + dx[i], owner->y.get(0) + dy[i]);
		if( !owner->entity->IsDead() ) for(int j = 0; j < owner->sym.size(); j++) mapdata->SetCreature(owner->x.get(j), owner->y.get(j));
	}
}

void CreatureAI::ChaseOrAttack(Object *owner, Object *target)
{
	int ox = owner->x.get(0), oy = owner->y.get(0);
	int dx = target->x.get(0) - ox;
	int dy = target->y.get(0) - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = sqrtf(dx*dx + dy*dy);
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	owner->entity->ai->arrived = true;

				//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
	Stats stats = Stats(0, 0, 0, 0, 25, 0, 0, 0, 0, 0);
				//  Status(hp, mp, xpnext)
	Status status = Status(0, 0, 0);
	Condition condition = Condition(Condition::NONE, 0, -1, stats, status, "msgStart", "msgStop");
	owner->entity->conditionList2.addToBack(condition);

	if( distance > sqrt(2.0f) )
	{
		dx = (int)(round(dx/distance));
		dy = (int)(round(dy/distance));
		if( !mapdata->IsObstructed(ox + dx, oy + dy) )
		{
			ox += dx;
			oy += dy;
		}
		else if( !mapdata->IsObstructed(ox + stepdx, oy) )
		{
			ox += stepdx;
		}
		else if( !mapdata->IsObstructed(ox, oy + stepdy) )
		{
			oy += stepdy;
		}
	}

	dx = ox - owner->x.get(0);
	dy = oy - owner->y.get(0);
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			mapdata->RevertCell(owner->x.get(i), owner->y.get(i));
			mapdata->Activated(owner->x.get(i), owner->y.get(i), false);
		}
		mapdata->Action(owner, ox, oy);
		if( !owner->entity->IsDead() ) for(int i = 0; i < owner->sym.size(); i++) mapdata->SetCreature(owner->x.get(i), owner->y.get(i));
	}

	if( distance <= sqrt(2.0f) ) owner->entity->Attack(owner, target);
}

void CreatureAI::MoveToTarget(Object *owner)
{
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	int ox = owner->x.get(0), oy = owner->y.get(0);
	ox = Clamp<int>(ox, 1, mapdata->width - 2);
	oy = Clamp<int>(oy, 1, mapdata->height - 2);
	owner->x.set(ox, 0);
	owner->y.set(oy, 0);

	if( owner->entity->ai->arrived )
	{
		owner->entity->ai->arrived = false;

		int direction = RNG->getInt(1, 4);
		int xTarget, yTarget;
		switch( direction )
		{
			case 1:
			{	// Up
				xTarget = ox;
				yTarget = oy - 10;
				break;
			}
			case 2:
			{	// Down
				xTarget = ox;
				yTarget = oy + 10;
				break;
			}
			case 3:
			{	// Left
				xTarget = ox - 10;
				yTarget = oy;
				break;
			}
			case 4:
			{	// Right
				xTarget = ox + 10;
				yTarget = oy;
				break;
			}
			default: break;
		}
		xTarget = Clamp<int>(xTarget, 1, mapdata->width - 2);
		yTarget = Clamp<int>(yTarget, 1, mapdata->height - 2);
		owner->entity->ai->xTarget = xTarget;
		owner->entity->ai->yTarget = yTarget;
	}

	int dx = owner->entity->ai->xTarget - ox;
	int dy = owner->entity->ai->yTarget - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = MAX(1.0f, sqrtf(dx*dx + dy*dy));

	dx = (int)(round(dx/distance));
	dy = (int)(round(dy/distance));
	if( !mapdata->IsObstructed(ox + dx, oy + dy) )
	{
		ox += dx;
		oy += dy;
	}
	else if( !mapdata->IsObstructed(ox + stepdx, oy) )
	{
		ox += stepdx;
	}
	else if( !mapdata->IsObstructed(ox, oy + stepdy) )
	{
		oy += stepdy;
	}
	else
	{
		owner->entity->ai->arrived = true;
	}

	dx = ox - owner->x.get(0);
	dy = oy - owner->y.get(0);
	if( dx != 0 || dy != 0 )
	{
		for(int i = 0; i < owner->sym.size(); i++)
		{
			mapdata->RevertCell(owner->x.get(i), owner->y.get(i));
			mapdata->Activated(owner->x.get(i), owner->y.get(i), false);
		}
		mapdata->Action(owner, ox, oy);
		for(int i = 0; i < owner->sym.size(); i++) mapdata->SetCreature(owner->x.get(i), owner->y.get(i));
	}

	if( distance <= 1.0f ) owner->entity->ai->arrived = true;
}

void CreatureAI::SpawnSubordinates(Object *owner)
{
	int x0 = owner->x.get(0), y0 = owner->y.get(0);
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	//mapdata->GetCreatureChances(mapdata->type);
	int x = x0 + RNG->getInt(-5, 5);
	int y = y0 + RNG->getInt(-5, 5);
	x = Clamp<int>(x, 1, mapdata->width - 2);
	y = Clamp<int>(y, 1, mapdata->height - 2);
	while( mapdata->IsObstructed(x, y) || mapdata->FeatureType(x, y) == FEATURE_TRAP )
	{
		x = x0 + RNG->getInt(-5, 5);
		y = y0 + RNG->getInt(-5, 5);
		x = Clamp<int>(x, 1, mapdata->width - 2);
		y = Clamp<int>(y, 1, mapdata->height - 2);
	}
	//mapdata->AddCreature(x, y);

	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(CHAR_FLAYER_WARRIOR);
	Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Flayer Warrior", 0.5f, true);
				//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
	Stats stats = Stats(15, 5, 3, 5, 5, 0, 0, 0, 0, 0);
				//  Status(hp, mp, xpnext)
	Status status = Status(15, 0, -7);
	creature->entity = new Entity(Entity::TROGLODYTE, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "A Flayer Corpse");
	creature->container = new Container(10);
	creature->entity->ai = new CreatureAI(AI_REGULAR, RNG->getInt(75,125));
	mapdata->objects.push(creature);
	for(int i = 0; i < creature->sym.size(); i++) mapdata->SetCreature(creature->x.get(i), creature->y.get(i));

	creature->entity->ai->superior = owner;

	owner->entity->ai->subordinates.push(creature);
}