#include "Main.hpp"

bool BossAI::Update(Object *owner)
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

	if( owner->entity->displacement >= 1.0f )
	{
      	owner->entity->displacement = 0.0f;

		WalkPattern(owner);

		if( !engine->player->entity->IsDead() )
		{
			float dx = owner->xc - engine->player->xc, dy = owner->yc - engine->player->yc, d = sqrtf(dx*dx + dy*dy);
			if( d <= 1.5f*sqrt(2.0f) ) owner->entity->Attack(owner, engine->player);
		}
	}

	return true;
}

void BossAI::WalkPattern(Object *owner)
{
	static int x = owner->x.get(0), y = owner->y.get(0);
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	// Increment along prescribed pattern list
	ListPattern(owner, x, y);

	for(int j = 0; j < owner->sym.size(); j++)
	{
		mapdata->RevertCell(owner->x.get(j), owner->y.get(j));
		mapdata->Activated(owner->x.get(j), owner->y.get(j), false);
	}
	mapdata->Action(owner, x, y);
	if( !owner->entity->IsDead() ) for(int j = 0; j < owner->sym.size(); j++) mapdata->SetCreature(owner->x.get(j), owner->y.get(j));
}

void BossAI::ListPattern(Object *owner, int &x, int &y)
{
	static bool second = false;
	static int patternCounter = 0, patternMax = 0;
	static int stepCounter = 0, stepMax = 0;
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	patternMax = patternList.size();
	stepMax = patternData[patternCounter].size();

	int dx = patternData[patternCounter][stepCounter].x;
	int dy = patternData[patternCounter][stepCounter].y;

	owner->obstructs = false;
	bool obstructed = mapdata->IsObstructed(owner->x.get(0) + dx, owner->y.get(0) + dy);
	for(int j = 1; j < owner->sym.size(); j++)
	{
		obstructed = obstructed || mapdata->IsObstructed(owner->x.get(j) + dx, owner->y.get(j) + dy);
	}
	owner->obstructs = true;

	if( !obstructed )
	{
		x += dx;
		y += dy;
	}
	owner->entity->base_stats.spd += patternData[patternCounter][stepCounter].spd;

	stepCounter = (stepCounter + 1) % MAX(1, stepMax);
	if( stepCounter == 0 )
	{
		patternCounter = (patternCounter + 1) % MAX(1, patternMax);
		if( patternCounter == 0 )
		{
			if( second )
			{
				second = false;
				PatternEnsemble(RNG->getInt(VERTICAL_PATTERN, NPATTERNTYPES - 1));
			}
			else
			{
				second = true;
			}
		}
	}
}