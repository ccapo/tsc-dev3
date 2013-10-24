#include "Main.hpp"

void Entity::Attack(Object *owner, Object *target)
{
	TCODColor colour = TCODColor::lightGrey;
	if( owner == engine->player ) colour = TCODColor::blue;

	if( target->entity && !target->entity->IsDead() )
	{
		int damage = target->entity->TakeDamage(stats.ap + stats.str/5 + stats.spd/10);
		if( damage > 0 )
		{
			engine->menu->MessageLog(colour, "%s Attacks %s", owner->name.c_str(), target->name.c_str());
			if( target->entity->IsDead() )
			{
				owner->entity->status.xp += target->entity->status.xp;
				Death(target);
			}
		}
		else
		{
			engine->menu->MessageLog(colour, "%s Attacks %s In Vain", owner->name.c_str(), target->name.c_str());			
		}
	}
}

int Entity::TakeDamage(int amount)
{
	amount -= stats.dp + stats.str/5 + stats.spd/10;
	if( amount > 0 )
	{
		status.hp -= amount;
	}
	else
	{
		amount = 0;
	}
	return amount;
}

int Entity::Heal(int amount)
{
	status.hp += amount;
	if( status.hp > stats.hpmax )
	{
		amount -= status.hp - stats.hpmax;
		status.hp = stats.hpmax;
	}
	return amount;
}

void Entity::Death(Object *owner)
{
	MapData *mapdata = &engine->map->mapData[engine->mapID];

	// Determine Cell Type
	int featuretype;
	for(int i = 0; i < owner->sym.size(); i++) featuretype = mapdata->FeatureType(owner->x.get(i), owner->y.get(i));

	// Send Notice to Message Log
	switch( featuretype )
	{
		case FEATURE_WALL:
		{
			engine->menu->MessageLog(TCODColor::lightGrey, "The Wall Crumbles Away");
			break;
		}
		case FEATURE_DOOR:
		{
			engine->menu->MessageLog(TCODColor::lightGrey, "The Door Crumbles Away");
			break;
		}
		default:
		{
			engine->menu->MessageLog(TCODColor::red, "%s Died", owner->name.c_str());
			break;
		}
	}

	// Transform the Entity into a corpse!
	if( owner->entity->ai != NULL )
	{
		if( owner->entity->ai->subordinates.size() > 0 )
		{
			for(int i = 0; i < owner->entity->ai->subordinates.size(); i++)
			{
				Object *subordinate = owner->entity->ai->subordinates.get(i);
				delete subordinate->entity->ai->superior;
				subordinate->entity->ai->superior = NULL;
			}
		}

		if( owner->entity->ai->superior != NULL )
		{
			Object *superior = owner->entity->ai->superior;
			superior->entity->ai->subordinates.remove(owner);

			delete owner->entity->ai->superior;
			owner->entity->ai->superior = NULL;
		}

		delete owner->entity->ai;
		owner->entity->ai = NULL;
	}

	for(int i = 0; i < owner->sym.size(); i++) owner->sym.set(owner->entity->corpseSym,i);
	owner->entity->status.hp = 0;
	owner->colour = owner->entity->corpseColour;	
	owner->name = owner->entity->corpseName;
	owner->obstructs = false;

	// Reset the Action for this Cell
	for(int i = 0; i < owner->sym.size(); i++)
	{
		mapdata->RevertCell(owner->x.get(i), owner->y.get(i));
		mapdata->Activated(owner->x.get(i), owner->y.get(i), false);
	}

	// Make sure corpses are drawn before living entities
	mapdata->SendToBack(owner);
}

void Entity::updateConditionList(Object *owner)
{
	for(list<Condition>::iterator it = owner->entity->conditionList2.inventory.begin(); it != owner->entity->conditionList2.inventory.end(); it++)
	{
		// Apply Condition
		if( (*it).first || (*it).counter == (*it).interval || (*it).interval == 0 )
		{
			(*it).first = false;
			(*it).counter = 0;

			switch( (*it).type )
			{
				case Condition::MP_REGEN:
				{
					(*it).status.mp = owner->entity->stats.acu;
					(*it).interval = 2*(WILMAX - owner->entity->stats.wil);
					break;
				}
				case Condition::POISON_ANTIDOTE:
				{
					if( owner->entity->hasCondition(Condition::POISON) )
					{
						list<Condition>::iterator itout;
						if( owner->entity->getCondition(Condition::POISON, itout) )
						{
							owner->entity->conditionList2.remove(itout);
						}
						owner->colour = TCODColor::white;
					}
					break;
				}
				case Condition::POISON:
				{
					owner->colour = TCODColor::green;
					break;
				}
				default: break;
			}

			owner->entity->stats += (*it).stats;
			owner->entity->status += (*it).status;
		}
		else
		{
			if( (*it).interval > 0 ) (*it).counter++;
		}

		// Update Condition
		bool finished = (*it).Update();

		// Remove Condition if Finished
		if( finished )
		{
			if( owner == engine->player && (*it).displayMsgStop ) engine->menu->MessageLog(TCODColor::green, "%s", (*it).msgStop.c_str());

			switch( (*it).type )
			{
				case Condition::POISON:
				{
					owner->colour = TCODColor::white;
					break;
				}
				default: break;
			}

			owner->entity->conditionList2.remove(it);
		}
	}

	owner->entity->status.hp = Clamp<int>(owner->entity->status.hp, 0, owner->entity->stats.hpmax);
	owner->entity->status.mp = Clamp<int>(owner->entity->status.mp, 0, owner->entity->stats.mpmax);
}

void Entity::addConditionList(Object *owner)
{
	for(int i = 0; i < owner->container->inventory.size(); i++)
	{
		Object *object = owner->container->inventory.get(i);

		if( object->wearable && object->wearable->worn )
		{
			if( object->wearable->conditionList2.first && owner == engine->player )
			{
				object->wearable->conditionList2.first = false;

				engine->menu->MessageLog(TCODColor::lightGrey, "You Put On %s", object->name.c_str());
			}

			for(list<Condition>::iterator it = object->wearable->conditionList2.inventory.begin(); it != object->wearable->conditionList2.inventory.end(); it++)
			{
				if( (*it).first )
				{
					(*it).first = false;

					if( owner == engine->player && (*it).displayMsgStart ) engine->menu->MessageLog(TCODColor::red, "%s", (*it).msgStart.c_str());

					//cout << (*it).category << ", " << (*it).type << endl;

					if( (*it).category == Condition::STATS )
					{
						owner->entity->conditionList2.addToBack(*it);
					}
					else
					{
						owner->entity->conditionList2.addToFront(*it);
					}
				}
			}
		}

		if( object->wieldable && object->wieldable->wielded )
		{
			if( object->wieldable->conditionList2.first && owner == engine->player )
			{
				object->wieldable->conditionList2.first = false;

				engine->menu->MessageLog(TCODColor::lightGrey, "You Wield %s", object->name.c_str());
			}

			for(list<Condition>::iterator it = object->wieldable->conditionList2.inventory.begin(); it != object->wieldable->conditionList2.inventory.end(); it++)
			{
				if( (*it).first )
				{
					(*it).first = false;

					if( owner == engine->player && (*it).displayMsgStart ) engine->menu->MessageLog(TCODColor::red, "%s", (*it).msgStart.c_str());
					
					if( (*it).category == Condition::STATS )
					{
						owner->entity->conditionList2.addToBack(*it);
					}
					else
					{
						owner->entity->conditionList2.addToFront(*it);
					}
				}
			}
		}
	}

	//cout << endl;
	//for(list<Condition>::iterator it = owner->entity->conditionList2.inventory.begin(); it != owner->entity->conditionList2.inventory.end(); it++)
	//{
	//	cout << (*it).category << ", " << (*it).type << "; " << owner->entity->status.hp << "/" << owner->entity->stats.hpmax << endl;
	//}
	//cout << endl;

	if( owner->container->mass >= owner->entity->stats.str )
	{
		Condition condition = Condition(Condition::BURDENED);

		if( owner->entity->hasCondition(Condition::BURDENED) )
		{
			condition.duration = 0;
			condition.displayMsgStart = false;
		}

		if( owner == engine->player && condition.displayMsgStart ) engine->menu->MessageLog(TCODColor::red, "%s", condition.msgStart.c_str());

		owner->entity->conditionList2.addToBack(condition);
	}
}

bool Entity::hasCondition(Condition::ConditionType type)
{
	bool result = false;

	for(list<Condition>::iterator it = conditionList2.inventory.begin(); it != conditionList2.inventory.end(); it++)
	{
		if( (*it).type == type ) result = true;
	}

	return result;
}

bool Entity::getCondition(Condition::ConditionType type, list<Condition>::iterator &itout)
{
	bool result = false;
	for(list<Condition>::iterator it = conditionList2.inventory.begin(); it != conditionList2.inventory.end(); it++)
	{
		if( (*it).type == type )
		{
			result = true;
			itout = it;
		}
	}
	return result;
}