#ifndef PLAYER_HPP
#define PLAYER_HPP
//------------------------------------------------------------------------
//
// Name: Player.hpp
//
// Desc: A class defining the Player
//
// Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Message.hpp"
#include "Object.hpp"
#include "Entity.hpp"
#include "StateManager.hpp"
#include "PlayerStates.hpp"

class Entity;

class Player : public Object
{
private:

	// Copy constructor and assignment should be private
	Player(const Player&);
	Player &operator=(const Player&);

public:

	// An instance of the state Manager class
	StateManager<Player> *stateMgr;

	Player()
	{
		// Setup State Manager
		stateMgr = new StateManager<Player>(this);
		stateMgr->SetCurrentState(PlayerIdleState);

		x.push(DISPLAY_WIDTH/2);
		y.push(DISPLAY_HEIGHT/2 + 1);
		sym.push(CHAR_PLAYER_RIGHT);
		colour = TCODColor::white;
		name = "The Player";
		mass = 100.0f;
		obstructs = true;
		counter = -1;
		consumable = NULL;
		container = NULL;
		traversable = NULL;
		wearable = NULL;
		wieldable = NULL;

		Stats stats = Stats(25, 8, 4, 10, 25, 15, 4, 2, 10, 1);
		Status status = Status(stats.hpmax, stats.mpmax, 100);
		status.gp = 100;
		entity = new Entity(Entity::PLAYER, stats, status, TEMPLE_LIGHT, CHAR_SKULL, TCODColor::darkRed, "Your Corpse");
		entity->ai = new PlayerAI();
		Stats stats2 = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
		Status status2 = Status(0, entity->stats.acu, 0);
		Condition condition = Condition(Condition::MP_REGEN, -1, 2*(WILMAX - entity->stats.wil), stats2, status2, "msgStart", "msgStop");
		entity->conditionList2.addToFront(condition);
		container = new Container(-1);

		Object *item;
		item = new Object(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, CHAR_SWORD_BASIC, TCODColor::white, "A Bronze Sword", 1.0f, false);
		item->wieldable = new Wieldable(Wieldable::BRONZE_SWORD);
		container->add(this, item);

		item = new Object(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, CHAR_SWORD_STEEL, TCODColor::white, "An Iron Sword", 1.0f, false);
		item->wieldable = new Wieldable(Wieldable::IRON_SWORD);
		item->wieldable->wielded = true;
		container->add(this, item);

		item = new Object(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, CHAR_ARMOUR_BROWN, TCODColor::white, "A Cotton Tunic", 0.25f, false);
		item->wearable = new Wearable(Wearable::COTTON_ARMOUR);
		//item->wearable->worn = true;
		container->add(this, item);

		item = new Object(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, CHAR_ARMOUR_BROWN, TCODColor::white, "A Leather Tunic", 0.5f, false);
		item->wearable = new Wearable(Wearable::LEATHER_ARMOUR);
		item->wearable->worn = true;
		container->add(this, item);

		item = new Object(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, CHAR_RING_RED, TCODColor::white, "A Mysterious Ring", 0.1f, false);
		item->wearable = new Wearable(Wearable::RING_MISC);
		//item->wearable->worn = true;
		container->add(this, item);

		item = new Object(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, CHAR_MUSHROOM, TCODColor::white, "An Unknown Mushroom", 0.05f, false);
		item->consumable = new Consumable(Consumable::MUSHROOM_UNKNOWN);
		container->add(this, item);

		item = new Object(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, CHAR_POTION_BLUE, TCODColor::white, "A Health Potion", 0.25f, false);
		item->consumable = new Consumable(Consumable::POTION_HEALTH);
		container->add(this, item);

		item = new Object(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, CHAR_RUBBLE_PILE, TCODColor::white, "A Pebble", 0.05f, false);
		item->consumable = new Consumable(Consumable::ROCKS);
		container->add(this, item);

		item = new Object(DISPLAY_WIDTH/2, DISPLAY_HEIGHT/2, CHAR_KEY, TCODColor::white, "A Key", 0.1f, false);
		container->add(this, item);
	}

	virtual ~Player()
	{
		if( stateMgr != NULL )
		{
			delete stateMgr;
			stateMgr = NULL;
		}
	}

	// Update the Player
	bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
	{
		return stateMgr->Update(elapsed, key, mouse);
	}

	// Render the Player
	void Render()
	{
		stateMgr->Render();
	}

	// Handle Messages for the Player
	bool Receive(const Message &msg)
	{
		return stateMgr->Receive(msg);
	}
};

#endif
