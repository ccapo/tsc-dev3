#include "Main.hpp"

bool Container::add(Object *owner, Object *object)
{
	// Inventory is full
	if( ( max_size > 0 && inventory.size() >= max_size ) || ( owner->entity && owner->entity->stats.str <= mass ) ) return false;

	mass += object->mass;
	inventory.push(object);
	return true;
}
	
void Container::remove(Object *object)
{
	mass -= object->mass;
	inventory.remove(object);
}

Consumable::Consumable(ConsumableType type): type(type)
{
	int ctype = type;
	if( ctype == MUSHROOM_UNKNOWN ) ctype = RNG->getInt(MUSHROOM_HEALTH, MUSHROOM_PARALYSIS);

	//conditionList = new ConditionList();

	switch( ctype )
	{
		case POTION_ELIXIR:
		{
			// Condition *condition = new Condition(Condition::ELIXIR);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::ELIXIR);
			conditionList2.addToBack(condition);
			break;
		}
		case POTION_HEALTH:
		{
			// Condition *condition = new Condition(Condition::HP_PLUS);
			// condition->duration = 0;
			// condition->interval = -1;
			// condition->stats.hpmax = 0;
			// condition->status.hp = 10;
			// condition->msgStart = "Physically, You Feel A Little Better";
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::HP_PLUS);
			condition.duration = 0;
			condition.interval = -1;
			condition.stats.hpmax = 0;
			condition.status.hp = 10;
			condition.msgStart = "Physically, You Feel A Little Better";
			conditionList2.addToBack(condition);
			break;
		}
		case POTION_HEALTH_STRONG:
		{
			// Condition *condition = new Condition(Condition::HP_PLUS);
			// condition->duration = 0;
			// condition->interval = -1;
			// condition->stats.hpmax = 0;
			// condition->status.hp = 50;
			// condition->msgStart = "Physically, You Feel A Lot Better!";
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::HP_PLUS);
			condition.duration = 0;
			condition.interval = -1;
			condition.stats.hpmax = 0;
			condition.status.hp = 50;
			condition.msgStart = "Physically, You Feel A Lot Better!";
			conditionList2.addToBack(condition);
			break;
		}
		case POTION_MAGIC:
		{
			// Condition *condition = new Condition(Condition::MP_PLUS);
			// condition->duration = 0;
			// condition->interval = -1;
			// condition->stats.mpmax = 0;
			// condition->status.mp = 5;
			// condition->msgStart = "Mentally, You Feel A Little Sharper";
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::MP_PLUS);
			condition.duration = 0;
			condition.interval = -1;
			condition.stats.mpmax = 0;
			condition.status.mp = 5;
			condition.msgStart = "Mentally, You Feel A Little Sharper";
			conditionList2.addToBack(condition);
			break;
		}
		case POTION_MAGIC_STRONG:
		{
			// Condition *condition = new Condition(Condition::MP_PLUS);
			// condition->duration = 0;
			// condition->interval = -1;
			// condition->stats.mpmax = 0;
			// condition->status.mp = 25;
			// condition->msgStart = "Mentally, You Feel A Lot Sharper!";
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::MP_PLUS);
			condition.duration = 0;
			condition.interval = -1;
			condition.stats.mpmax = 0;
			condition.status.mp = 25;
			condition.msgStart = "Mentally, You Feel A Lot Sharper!";
			conditionList2.addToBack(condition);
			break;
		}
		case POTION_POISON_ANTIDOTE:
		{
			// Condition *condition = new Condition(Condition::POISON_ANTIDOTE);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::POISON_ANTIDOTE);
			conditionList2.addToBack(condition);
			break;
		}
		case MUSHROOM_HEALTH:
		{
			// Condition *condition = new Condition(Condition::HP_PLUS);
			// condition->duration = 0;
			// condition->interval = -1;
			// condition->stats.hpmax = 0;
			// condition->status.hp = 5;
			// condition->msgStart = "Physically, You Feel A Little Better";
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::HP_PLUS);
			condition.duration = 0;
			condition.interval = -1;
			condition.stats.hpmax = 0;
			condition.status.hp = 5;
			condition.msgStart = "Physically, You Feel A Little Better";
			conditionList2.addToBack(condition);
			break;
		}
		case MUSHROOM_MAGIC:
		{
			// Condition *condition = new Condition(Condition::MP_PLUS);
			// condition->duration = 0;
			// condition->interval = -1;
			// condition->stats.mpmax = 0;
			// condition->status.mp = 2;
			// condition->msgStart = "Mentally, You Feel A Little Sharper";
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::MP_PLUS);
			condition.duration = 0;
			condition.interval = -1;
			condition.stats.mpmax = 0;
			condition.status.mp = 2;
			condition.msgStart = "Mentally, You Feel A Little Sharper";
			conditionList2.addToBack(condition);
			break;
		}
		case MUSHROOM_POISON:
		{
			// Condition *condition = new Condition(Condition::POISON);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::POISON);
			conditionList2.addToBack(condition);
			break;
		}
		case MUSHROOM_WEAKNESS:
		{
			// Condition *condition = new Condition(Condition::STR_MINUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::STR_MINUS);
			conditionList2.addToBack(condition);
			break;
		}
		case MUSHROOM_SLUGGISHNESS:
		{
			// Condition *condition = new Condition(Condition::SPD_MINUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::SPD_MINUS);
			conditionList2.addToBack(condition);
			break;
		}
		case MUSHROOM_FEEBLENESS:
		{
			// Condition *condition = new Condition(Condition::WIL_MINUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::WIL_MINUS);
			conditionList2.addToBack(condition);
			break;
		}
		case MUSHROOM_INEPTNESS:
		{
			// Condition *condition = new Condition(Condition::ACU_MINUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::ACU_MINUS);
			conditionList2.addToBack(condition);
			break;
		}
		case MUSHROOM_CONFUSION:
		{
			// Condition *condition = new Condition(Condition::CONFUSION);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::CONFUSION);
			conditionList2.addToBack(condition);
			break;
		}
		case MUSHROOM_PARALYSIS:
		{
			// Condition *condition = new Condition(Condition::PARALYSIS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::PARALYSIS);
			conditionList2.addToBack(condition);
			break;
		}
		case ENTRAILS:
		{
			// Condition *condition = new Condition(Condition::POISON);
			// condition->duration = 10*FPSMAX;
			// condition->interval = FPSMAX;
			// condition->msgStart = "I Don't Think That Was Such A Good Idea";
			// condition->msgStop = "You Begin To Feel A Lot Less Queasy";
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::POISON);
			condition.duration = 10*FPSMAX;
			condition.interval = FPSMAX;
			condition.msgStart = "I Don't Think That Was Such A Good Idea";
			condition.msgStop = "You Begin To Feel A Lot Less Queasy";
			conditionList2.addToBack(condition);
			break;
		}
		case ROCKS:
		{
			// Condition *condition = new Condition(Condition::NONE);
			// condition->msgStart = "*CRUNCH* *CRUNCH* *CRUNCH* Hmmm ... Not Bad";
			// condition->displayMsgStart = true;
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::NONE);
			condition.msgStart = "*CRUNCH* *CRUNCH* *CRUNCH* Hmmm ... Not Bad";
			condition.displayMsgStart = true;
			conditionList2.addToBack(condition);
			break;
		}
		default:
		{
			// Condition *condition = new Condition(Condition::NONE);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::NONE);
			conditionList2.addToBack(condition);
			break;
		}
	}
}

Wearable::Wearable(WearableType type): type(type), worn(false)
{
	//conditionList = new ConditionList();

	switch( type )
	{
		case RING_HP_PLUS:
		{
			// Condition *condition = new Condition(Condition::HP_PLUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::HP_PLUS);
			conditionList2.addToBack(condition);
			break;
		}
		case RING_MP_PLUS:
		{
			// Condition *condition = new Condition(Condition::MP_PLUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::MP_PLUS);
			conditionList2.addToBack(condition);		
			break;
		}
		case RING_HP_REGEN:
		{
			// Condition *condition = new Condition(Condition::HP_REGEN);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::HP_REGEN);
			conditionList2.addToBack(condition);
			break;
		}
		case RING_MP_REGEN:
		{
			// Condition *condition = new Condition(Condition::MP_REGEN);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::MP_REGEN);
			conditionList2.addToBack(condition);
			break;
		}
		case RING_STR_PLUS:
		{
			// Condition *condition = new Condition(Condition::STR_PLUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::STR_PLUS);
			conditionList2.addToBack(condition);	
			break;
		}
		case RING_SPD_PLUS:
		{
			// Condition *condition = new Condition(Condition::SPD_PLUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::SPD_PLUS);
			conditionList2.addToBack(condition);
			break;
		}
		case RING_WIL_PLUS:
		{
			// Condition *condition = new Condition(Condition::WIL_PLUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::WIL_PLUS);
			conditionList2.addToBack(condition);
			break;
		}
		case RING_ACU_PLUS:
		{
			// Condition *condition = new Condition(Condition::ACU_PLUS);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::ACU_PLUS);
			conditionList2.addToBack(condition);			
			break;
		}
		case RING_CURSED:
		{
			// Condition *condition = new Condition(Condition::POISON);
			// condition->duration = -1;
			// condition->interval = 5*FPSMAX;
			// condition->msgStart = "The Ring Is Cursed!";
			// condition->msgStop = "You Manage To Remove The Cursed Ring";
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::POISON);
			condition.duration = 10*FPSMAX;
			condition.interval = FPSMAX;
			condition.msgStart = "The Ring Is Cursed!";
			condition.msgStop = "You Manage To Remove The Cursed Ring";
			conditionList2.addToBack(condition);
			break;
		}
		case RING_MISC:
		{
			// Condition *condition = new Condition(Condition::MISC);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::MISC);
			int hp = condition.stats.hpmax;
			int mp = condition.stats.mpmax;
			condition.stats.hpmax = 0;
			condition.stats.mpmax = 0;
			condition.duration = -1;
			condition.interval = 0;
			conditionList2.addToBack(condition);

			Condition condition2 = Condition(Condition::HPMAX_PLUS);
			condition2.stats.hpmax = hp;
			condition2.msgStart = "msgStart";
			condition2.msgStop = "msgStop";
			condition2.displayMsgStart = false;
			condition2.displayMsgStop = false;
			conditionList2.addToBack(condition2);

			Condition condition3 = Condition(Condition::HP_PLUS);
			condition3.status.hp = hp;
			condition3.msgStart = "msgStart";
			condition3.msgStop = "msgStop";
			condition3.displayMsgStart = false;
			condition3.displayMsgStop = false;
			conditionList2.addToBack(condition3);

			Condition condition4 = Condition(Condition::MPMAX_PLUS);
			condition4.stats.mpmax = mp;
			condition4.msgStart = "msgStart";
			condition4.msgStop = "msgStop";
			condition4.displayMsgStart = false;
			condition4.displayMsgStop = false;
			conditionList2.addToBack(condition4);

			Condition condition5 = Condition(Condition::MP_PLUS);
			condition5.status.mp = mp;
			condition5.msgStart = "msgStart";
			condition5.msgStop = "msgStop";
			condition5.displayMsgStart = false;
			condition5.displayMsgStop = false;
			conditionList2.addToBack(condition5);
			break;
		}
		case LEATHER_ARMOUR:
		{
			// Condition *condition = new Condition(Condition::HP_PLUS);
			// condition->msgStart = "msgStart";
			// condition->msgStop = "msgStop";
			// condition->displayMsgStart = false;
			// condition->displayMsgStop = false;
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::HPMAX_PLUS);
			condition.msgStart = "msgStart";
			condition.msgStop = "msgStop";
			condition.displayMsgStart = false;
			condition.displayMsgStop = false;
			conditionList2.addToBack(condition);

			Condition condition2 = Condition(Condition::HP_PLUS);
			condition2.msgStart = "msgStart";
			condition2.msgStop = "msgStop";
			condition2.displayMsgStart = false;
			condition2.displayMsgStop = false;
			conditionList2.addToBack(condition2);
			break;
		}
		default:
		{
			// Condition *condition = new Condition(Condition::NONE);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::NONE);
			conditionList2.addToBack(condition);
			break;
		}
	}
}

Wieldable::Wieldable(WieldableType type): type(type), wielded(false)
{
	//conditionList = new ConditionList();

	switch( type )
	{
		case CURSED_SWORD:
		{
			// Condition *condition = new Condition(Condition::POISON);
			// condition->duration = -1;
			// condition->interval = 5*FPSMAX;
			// condition->msgStart = "The Sword Is Cursed!";
			// condition->msgStop = "You Manage To Release The Cursed Sword";
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::POISON);
			condition.duration = -1;
			condition.interval = 5*FPSMAX;
			condition.msgStart = "The Sword Is Cursed!";
			condition.msgStop = "You Manage To Release The Cursed Sword";
			conditionList2.addToBack(condition);
			break;
		}
		default:
		{
			// Condition *condition = new Condition(Condition::NONE);
			// conditionList->addToBack(condition);
			// delete condition;
			// condition = NULL;

			Condition condition = Condition(Condition::NONE);
			conditionList2.addToBack(condition);
			break;
		}
	}
}