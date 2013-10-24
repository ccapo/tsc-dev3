#include "Main.hpp"

bool NpcAI::Update(Object *owner)
{
	MoveToTarget(owner);
	return true;
}

void NpcAI::MoveToTarget(Object *owner)
{
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	if( owner->entity->ai->arrived )
	{
		owner->entity->ai->arrived = false;

		int OldxTarget = owner->x.get(0);
		int OldyTarget = owner->y.get(0);
		int xTarget = RNG->getInt(1, mapdata->width - 2);
		int yTarget = RNG->getInt(1, mapdata->height - 2);
		float distance = sqrtf((OldxTarget - xTarget)*(OldxTarget - xTarget) + (OldyTarget - yTarget)*(OldyTarget - yTarget));

		while( mapdata->IsObstructed(xTarget, yTarget) || mapdata->FeatureType(xTarget, yTarget) == FEATURE_TRAP || distance < 10.0f )
		{
			xTarget = RNG->getInt(1, mapdata->width - 2);
			yTarget = RNG->getInt(1, mapdata->height - 2);
			distance = sqrtf((OldxTarget - xTarget)*(OldxTarget - xTarget) + (OldyTarget - yTarget)*(OldyTarget - yTarget));
		}
		owner->entity->ai->xTarget = xTarget;
		owner->entity->ai->yTarget = yTarget;
	}

	int ox = owner->x.get(0), oy = owner->y.get(0);
	int dx = owner->entity->ai->xTarget - ox;
	int dy = owner->entity->ai->yTarget - oy;
	int stepdx = (dx > 0 ? 1: -1);
	int stepdy = (dy > 0 ? 1: -1);
	float distance = sqrtf(dx*dx + dy*dy);

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
		for(int i = 0; i < owner->sym.size(); i++) mapdata->SetNpc(owner->x.get(i), owner->y.get(i));
	}

	if( distance <= 1.0f ) owner->entity->ai->arrived = true;
}