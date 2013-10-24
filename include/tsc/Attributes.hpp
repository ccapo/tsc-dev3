#ifndef ATTRIBUTES_HPP
#define ATTRIBUTES_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Condition.hpp"

class Object;

class Consumable
{
	public:
	enum ConsumableType
	{
		POTION_ELIXIR,
		POTION_HEALTH,
		POTION_HEALTH_STRONG,
		POTION_MAGIC,
		POTION_MAGIC_STRONG,
		POTION_POISON_ANTIDOTE,
		MUSHROOM_HEALTH,
		MUSHROOM_MAGIC,
		MUSHROOM_POISON,
		MUSHROOM_WEAKNESS,
		MUSHROOM_SLUGGISHNESS,
		MUSHROOM_FEEBLENESS,
		MUSHROOM_INEPTNESS,
		MUSHROOM_CONFUSION,
		MUSHROOM_PARALYSIS,
		MUSHROOM_UNKNOWN,
		ENTRAILS,
		ROCKS,
		NCONSUMABLETYPES
	} type;

	//ConditionList *conditionList;
	ConditionList2 conditionList2;

	Consumable(ConsumableType type);
	virtual ~Consumable()
	{
		// if( conditionList != NULL )
		// {
		// 	delete conditionList;
		// 	conditionList = NULL;
		// }
	}
};

class Container
{
	public:
	int max_size;					// Maximum number of Objects. 0 = Unlimited
	float mass;						// Mass of contents
	TCODList<Object *> inventory;	// Inventory of contents

	Container(int size): max_size(size), mass(0.0f) {}
	virtual ~Container()
	{
		inventory.clear();
	}

	bool add(Object *owner, Object *object);
	void remove(Object *object);
};

class Traversable
{
	public :
	int mapID, xTo, yTo;

	Traversable(int mapID, int xTo, int yTo): mapID(mapID), xTo(xTo), yTo(yTo) {}
	virtual ~Traversable() {}
};

class Wearable
{
	public:
	enum WearableType
	{
		WOODEN_SHIELD,
		REINFORCED_SHIELD,
		LEATHER_SHIELD,
		BRONZE_SHIELD,
		IRON_SHIELD,
		MITHRIL_SHIELD,
		HYDRASCALE_SHIELD,
		DRAGONSCALE_SHEILD,
		COTTON_ARMOUR,
		PADDED_ARMOUR,
		LEATHER_ARMOUR,
		BRONZE_ARMOUR,
		IRON_ARMOUR,
		MITHRIL_ARMOUR,
		HYDRASCALE_ARMOUR,
		DRAGONSCALE_ARMOUR,
		RING_HP_PLUS,
		RING_MP_PLUS,
		RING_HP_REGEN,
		RING_MP_REGEN,
		RING_STR_PLUS,
		RING_SPD_PLUS,
		RING_WIL_PLUS,
		RING_ACU_PLUS,
		RING_CURSED,
		RING_MISC,
		NWEARABLETYPES
	} type;
	bool worn;

	//ConditionList *conditionList;
	ConditionList2 conditionList2;

	Wearable(WearableType type);
	virtual ~Wearable()
	{
		// if( conditionList != NULL )
		// {
		// 	delete conditionList;
		// 	conditionList = NULL;
		// }
	}
};

class Wieldable
{
	public:
	enum WieldableType
	{
		WOODEN_SWORD,
		BRONZE_SWORD,
		IRON_SWORD,
		ANCIENT_SWORD,
		ICE_SWORD,
		FIRE_SWORD,
		MITHRIL_SWORD,
		HYDRASLAYER_SWORD,
		DRAGONSLAYER_SWORD,
		CURSED_SWORD,
		MISC_SWORD,
		NWIELDABLETYPES
	} type;
	bool wielded;

	//ConditionList *conditionList;
	ConditionList2 conditionList2;

	Wieldable(WieldableType type);
	virtual ~Wieldable()
	{
		// if( conditionList != NULL )
		// {
		// 	delete conditionList;
		// 	conditionList = NULL;
		// }
	}
};

#endif