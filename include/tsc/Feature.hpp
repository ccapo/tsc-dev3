#ifndef FEATURE_HPP
#define FEATURE_HPP

#include "Global.hpp"
#include "Object.hpp"
#include "Condition.hpp"

class Object;

class Feature
{
public:
	int type;
	int trapType;

	bool explored;		// Has this feature been explored?
	bool activated;		// Has this feature been activated?
	TCODColor colour;	// The background colour for this feature

	static TCODColor darkWall;
	static TCODColor darkGround;

	bool open;
	int mapID;
	int xTo, yTo;
	TCODColor flashColor;

	Condition condition1;	// Trap's List of ConditionList
	Condition condition2;	// Trap's List of ConditionList

	Feature(): type(-1), trapType(-1), explored(false), activated(false), colour(darkGround), open(false), mapID(0), xTo(0), yTo(0), flashColor(TCODColor::red), condition1(Condition(Condition::NONE)), condition2(Condition(Condition::NONE)) {}
	Feature(int type, int trapType, TCODColor colour): type(type), trapType(trapType), explored(false), activated(false), colour(colour), open(false), mapID(0), xTo(0), yTo(0), flashColor(TCODColor::red), condition1(Condition(Condition::NONE)), condition2(Condition(Condition::NONE)) {}
	Feature(int type, int trapType, TCODColor colour, int mapID, int xTo, int yTo): type(type), trapType(trapType), explored(false), activated(false), colour(colour), open(false), mapID(mapID), xTo(xTo), yTo(yTo), flashColor(flashColor), condition1(Condition(Condition::NONE)), condition2(Condition(Condition::NONE)) {}
	virtual ~Feature() {}
	virtual Feature *clone() const = 0;
	virtual Feature *create() const = 0;
	virtual void Action(Object *owner, int x, int y) = 0;
};

class FloorFeature: public Feature
{
public:
	FloorFeature(): Feature(FEATURE_FLOOR, -1, darkGround) {}
	virtual ~FloorFeature() {}
	virtual FloorFeature *clone() const
	{
		return new FloorFeature(*this);
	}
	virtual FloorFeature *create() const
	{
		return new FloorFeature();
	}
	void Action(Object *owner, int x, int y);
};

class WallFeature: public Feature
{
public:
	WallFeature(): Feature(FEATURE_WALL, -1, darkWall) {}
	virtual ~WallFeature() {}
	virtual WallFeature *clone() const
	{
		return new WallFeature(*this);
	}
	virtual WallFeature *create() const
	{
		return new WallFeature();
	}
	void Action(Object *owner, int x, int y);
};
 
class DoorFeature: public Feature
{
public:
	DoorFeature(): Feature(FEATURE_DOOR, -1, darkGround) {}
	virtual ~DoorFeature() {}
	virtual DoorFeature *clone() const
	{
		return new DoorFeature(*this);
	}
	virtual DoorFeature *create() const
	{
		return new DoorFeature();
	}
	void Action(Object *owner, int x, int y);
};

class TrapFeature: public Feature
{
public:
	TrapFeature(): Feature(FEATURE_TRAP, 0, darkGround, 0, 0, 0) {}
	TrapFeature(int type, int mapID, int xTo, int yTo);
	virtual ~TrapFeature() {}
	virtual TrapFeature *clone() const
	{
		return new TrapFeature(*this);
	}
	virtual TrapFeature *create() const
	{
		return new TrapFeature();
	}
	void Action(Object *owner, int x, int y);
};

class CreatureFeature: public Feature
{
public:
	CreatureFeature(): Feature(FEATURE_CREATURE, -1, darkGround) {}
	virtual ~CreatureFeature() {}
	virtual CreatureFeature *clone() const
	{
		return new CreatureFeature(*this);
	}
	virtual CreatureFeature *create() const
	{
		return new CreatureFeature();
	}
	void Action(Object *owner, int x, int y);
};

class NpcFeature: public Feature
{
public:
	NpcFeature(): Feature(FEATURE_NPC, -1, darkGround) {}
	virtual ~NpcFeature() {}
	virtual NpcFeature *clone() const
	{
		return new NpcFeature(*this);
	}
	virtual NpcFeature *create() const
	{
		return new NpcFeature();
	}
	void Action(Object *owner, int x, int y);
};

#endif