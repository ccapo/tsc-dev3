#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Global.hpp"
#include "Message.hpp"
#include "Attributes.hpp"
#include "Entity.hpp"

class Object
{
private:

	// Copy constructor and assignment should be private
	Object(const Object&);
	Object &operator=(const Object&);

public:

	// Object Types
	enum ObjectTypes
	{
		CONSUMABLE,
		CONTAINER,
		ENTITY,
		TRAVERSABLE,
		WEARABLE,
		WIELDABLE,
		MISC,
		NOBJECTTYPES
	};

	// Basic Attributes
	int id;							// Object's identifier
	TCODList<int> x, y;				// Object's position list on the map
	float xc, yc;					// Object's central position on the map
	TCODList<int> sym;				// Object's symbol list on the map
	TCODColor colour;				// Object's colour on the map
	string name;					// Object's name
	float mass;						// Object's mass
	bool obstructs;					// Does this object obstruct?
	int counter;					// Object's animation counter

	// Optional Attributes
	Consumable *consumable;			// Pointer to Consumable Attribute
	Container *container;			// Pointer to Container Attribute
	Entity *entity;					// Pointer to Entity Attribute
	Traversable *traversable;		// Pointer to Traversable Attribute
	Wearable *wearable;				// Pointer to Wearable Attribute
	Wieldable *wieldable;			// Pointer to Wieldable Attribute
 
 	Object(): id(0), colour(TCODColor::white), name("name"), mass(0.0f), obstructs(true), counter(-1), consumable(NULL), container(NULL), entity(NULL), traversable(NULL), wearable(NULL), wieldable(NULL) {}
	Object(TCODList<int> x, TCODList<int> y, TCODList<int> sym, const TCODColor &colour, string name, float mass, bool obstructs);
	virtual ~Object();

	virtual bool Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse);
	virtual void Render() const;
	virtual bool Receive(const Message &msg);
};

#endif