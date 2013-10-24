#ifndef NPC_HPP
#define NPC_HPP
//------------------------------------------------------------------------
//
// Name: Npc.hpp
//
// Desc: A class to implement a Npc
//
// Author: Mat Buckland 2003 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "NpcStates.hpp"
#include "StateManager.hpp"
#include "Transmitter.hpp"

class Npc : public Object
{
private:

	// Copy constructor and assignment should be private
	Npc(const Npc&);
	Npc &operator=(const Npc&);

public:

	// An instance of the State Manager class
	StateManager<Npc> *stateMgr;

	Npc(int type, int x0, int y0)
	{
		// Set up the State Manager
		stateMgr = new StateManager<Npc>(this);
		stateMgr->SetCurrentState(NpcIdleState);

		x.push(x0);
		y.push(y0);
		colour = TCODColor::white;
		mass = 100.0f;
		obstructs = true;
		counter = -1;
		consumable = NULL;
		container = NULL;
		entity = NULL;
		traversable = NULL;
		wearable = NULL;
		wieldable = NULL;

		switch( type )
		{
			case Entity::GUARDIAN:
			{
				sym.push(CHAR_GUARDIAN);
				colour = TCODColor::lightestYellow;
				name = "The Guardian";
				Stats stats = Stats(1, 0, 0, 0, 5, 0, 0, 0, 0, 0);
				Status status = Status(1, 0, 0);
				entity = new Entity(type, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "A Corpse");
				break;
			}
			case Entity::SHOPKEEPER:
			{
				sym.push(CHAR_KEEPER);
				name = "A Shopkeeper";
				Stats stats = Stats(1, 0, 0, 0, 5, 0, 0, 0, 0, 0);
				Status status = Status(1, 0, 0);
				entity = new Entity(type, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "A Corpse");
				break;
			}
			case Entity::TOWNSPERSON:
			{
				sym.push(RNG->getInt(0,1) == 0 ? CHAR_PERSON_MALE : CHAR_PERSON_FEMALE);
				name = "A Townsperson";
				Stats stats = Stats(1, 0, 0, 0, 5, 0, 0, 0, 0, 0);
				Status status = Status(1, 0, 0);
				entity = new Entity(type, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "A Corpse");
				break;
			}
			default: break;
		}

		entity->ai = new NpcAI();
	}

	virtual ~Npc()
	{
		if( stateMgr != NULL )
		{
			delete stateMgr;
			stateMgr = NULL;
		}
	}

	// Update the Npc
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return stateMgr->Update(elapsed, key, mouse);}

	// Render the Npc
	void Render(){stateMgr->Render();}

	// Handle Messages for the Npc
	bool Receive(const Message &msg){return stateMgr->Receive(msg);}
};

#endif