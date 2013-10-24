#ifndef ENTITY_HPP
#define ENTITY_HPP
//------------------------------------------------------------------------
//
// Name: Entity.hpp
//
// Desc: Base class to define a common interface for all game entities
//
// Author: Mat Buckland (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "libtcod.hpp"
#include "Object.hpp"
#include "AI.hpp"
#include "Message.hpp"
#include "Stats.hpp"
#include "Utils.hpp"

class Entity
{
private:

	// Copy constructor and assignment should be private
	Entity(const Entity&);
	Entity &operator=(const Entity&);

public:

	enum EntityType
	{
		PLAYER,
		GUARDIAN,
		SHOPKEEPER,
		TOWNSPERSON,
		INANIMATE,
		INSECT,
		VERMIN,
		REPTILE,
		BEAST,
		HUMANOID,
		TROGLODYTE,
		ETHEREAL,
		UNKNOWN,
		BOSS,
		NENTITYTYPES
	};
	int type;						// Entity Type

	Stats base_stats;				// Base Entity Stats
	Stats stats;					// Current Entity Stats
	Status status;					// Current Entity Status

	int mapID;						// Map ID
	float displacement;				// Entity's Movement Displacement

	int corpseSym;					// Entity's Corpse Symbol
	TCODColor corpseColour;			// Entity's Corpse Colour
	string corpseName;				// Entity's Corpse Name

	AI *ai;							// Entity's AI
	//ConditionList *conditionList;	// Entity's ConditionList
	ConditionList2 conditionList2;	// Entity's ConditionList

	Entity(int type, Stats stats, Status status, int mapID, int corpseSym, const TCODColor &corpseColour, string corpseName): type(type), base_stats(stats), stats(stats), status(status), mapID(mapID), displacement(0.0f), corpseSym(corpseSym), corpseColour(corpseColour), corpseName(corpseName), ai(NULL)
	{
		// Setup ConditionList
		//conditionList = new ConditionList();
	}

	virtual ~Entity()
	{
		if( ai != NULL )
		{
			delete ai;
			ai = NULL;
		}

		// if( conditionList != NULL )
		// {
		// 	delete conditionList;
		// 	conditionList = NULL;
		// }
	}

	virtual bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
	virtual void Render(){}
	virtual bool Receive(const Message &msg){return true;}

	// Entity Methods
	void Attack(Object *owner, Object *target);
	int TakeDamage(int amount);
	int Heal(int amount);
	inline bool IsDead() { return status.hp <= 0; }
	void Death(Object *owner);

	// Condition functions
	void updateConditionList(Object *owner);
	void addConditionList(Object *owner);
	bool hasCondition(Condition::ConditionType type);
	bool getCondition(Condition::ConditionType type, list<Condition>::iterator &itout);
};
 
#endif