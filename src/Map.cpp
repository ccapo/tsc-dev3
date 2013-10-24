#include "Main.hpp"

void MapData::Action(Object *owner, int x, int y)
{
	if( x + y*width < height*width ) cells[x + y*width].feature->Action(owner, x, y);
}

int MapData::FeatureType(int x, int y) const
{
	if( x + y*width < height*width )
	{
		return cells[x + y*width].feature->type;
	}
	else
	{
		return -1;
	}
}

int MapData::TrapType(int x, int y) const
{
	if( x + y*width < height*width )
	{
		return cells[x + y*width].feature->trapType;
	}
	else
	{
		return -1;
	}
}

TCODColor MapData::Colour(int x, int y) const
{
	if( x + y*width < height*width )
	{
		return cells[x + y*width].feature->colour;
	}
	else
	{
		return TCODColor::black;
	}
}

void MapData::Colour(int x, int y, TCODColor colour)
{
	if( x + y*width < height*width ) cells[x + y*width].feature->colour = colour;
}

bool MapData::Activated(int x, int y) const
{
	if( x + y*width < height*width )
	{
		return cells[x + y*width].feature->activated;
	}
	else
	{
		return false;
	}
}

void MapData::Activated(int x, int y, bool lvalue)
{
	if( x + y*width < height*width ) cells[x + y*width].feature->activated = lvalue;
}

bool MapData::Explored(int x, int y) const
{
	if( x + y*width < height*width )
	{
		return cells[x + y*width].feature->explored;
	}
	else
	{
		return false;
	}
}

void MapData::Explored(int x, int y, bool lvalue)
{
	if( x + y*width < height*width ) cells[x + y*width].feature->explored = lvalue;
}

void MapData::RevertCell(int x, int y)
{
	if( x + y*width < height*width ) cells[x + y*width].RevertToDefaultFeature();
}

void MapData::SetFloor(int x, int y)
{
	Feature *feature = new FloorFeature();
	Cell cell;
	cell.SetFeature(feature);
	cell.SetDefaultFeature(feature);
	if( x + y*width < height*width ) cells[x + y*width] = cell;
	delete feature;
	feature = NULL;
}

void MapData::SetWall(int x, int y)
{
	Feature *feature = new WallFeature();
	Cell cell;
	cell.SetFeature(feature);
	if( x + y*width < height*width ) cells[x + y*width] = cell;
	delete feature;
	feature = NULL;
}

void MapData::SetDoor(int x, int y)
{
	Feature *feature = new DoorFeature();
	Cell cell;
	cell.SetFeature(feature);
	if( x + y*width < height*width ) cells[x + y*width] = cell;
	delete feature;
	feature = NULL;
}

void MapData::SetTrap(int x, int y, int type, int mapID, int xTo, int yTo)
{
	Feature *feature = new TrapFeature(type, mapID, xTo, yTo);
	Cell cell;
	cell.SetFeature(feature);
	cell.SetDefaultFeature(feature);
	if( x + y*width < height*width ) cells[x + y*width] = cell;
	delete feature;
	feature = NULL;
}

void MapData::SetCreature(int x, int y)
{
	Feature *feature = new CreatureFeature();
	Cell cell;
	cell.SetFeature(feature);
	if( x + y*width < height*width ) cells[x + y*width] = cell;
	delete feature;
	feature = NULL;
}

void MapData::SetNpc(int x, int y)
{
	Feature *feature = new NpcFeature();
	Cell cell;
	cell.SetFeature(feature);
	if( x + y*width < height*width ) cells[x + y*width] = cell;
	delete feature;
	feature = NULL;
}

void MapData::GetItemChances(int caveType)
{
	switch( caveType )
	{
		case CAVETYPE_01:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Object::CONSUMABLE,	30));
			object_chances.insert(pair<int, int>(Object::CONTAINER,		30));
			object_chances.insert(pair<int, int>(Object::ENTITY,		10));
			object_chances.insert(pair<int, int>(Object::WIELDABLE,		10));
			object_chances.insert(pair<int, int>(Object::WEARABLE,		10));
			object_chances.insert(pair<int, int>(Object::MISC,			10));
			break;
		}
		case CAVETYPE_02:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Object::CONSUMABLE,	30));
			object_chances.insert(pair<int, int>(Object::CONTAINER,		30));
			object_chances.insert(pair<int, int>(Object::ENTITY,		10));
			object_chances.insert(pair<int, int>(Object::WIELDABLE,		10));
			object_chances.insert(pair<int, int>(Object::WEARABLE,		10));
			object_chances.insert(pair<int, int>(Object::MISC,			10));
			break;
		}
		case CAVETYPE_03:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Object::CONSUMABLE,	30));
			object_chances.insert(pair<int, int>(Object::CONTAINER,		30));
			object_chances.insert(pair<int, int>(Object::ENTITY,		10));
			object_chances.insert(pair<int, int>(Object::WIELDABLE,		10));
			object_chances.insert(pair<int, int>(Object::WEARABLE,		10));
			object_chances.insert(pair<int, int>(Object::MISC,			10));
			break;
		}
		case CAVETYPE_04:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(Object::CONSUMABLE,	30));
			object_chances.insert(pair<int, int>(Object::CONTAINER,		30));
			object_chances.insert(pair<int, int>(Object::ENTITY,		10));
			object_chances.insert(pair<int, int>(Object::WIELDABLE,		10));
			object_chances.insert(pair<int, int>(Object::WEARABLE,		10));
			object_chances.insert(pair<int, int>(Object::MISC,			10));
			break;
		}
		default: break;
	}
}

void MapData::GetTrapChances(int caveType)
{
	switch( caveType )
	{
		case CAVETYPE_01:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(TRAP_INVISIBLEBARRIER,	100));
			object_chances.insert(pair<int, int>(TRAP_DARKTUNNEL,		  0));
			break;
		}
		case CAVETYPE_02:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(TRAP_INVISIBLEBARRIER,	 75));
			object_chances.insert(pair<int, int>(TRAP_DARKTUNNEL,		 25));
			break;
		}
		case CAVETYPE_03:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(TRAP_INVISIBLEBARRIER,	 50));
			object_chances.insert(pair<int, int>(TRAP_DARKTUNNEL,		 50));
			break;
		}
		case CAVETYPE_04:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(TRAP_INVISIBLEBARRIER,	 25));
			object_chances.insert(pair<int, int>(TRAP_DARKTUNNEL,		 75));
			break;
		}
		default: break;
	}
}

void MapData::GetCreatureChances(int caveType)
{
	switch( caveType )
	{
		case CAVETYPE_01:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(AI_SKITTISH,   50));
			object_chances.insert(pair<int, int>(AI_REGULAR,    50));
			object_chances.insert(pair<int, int>(AI_AGGRESSIVE,  0));
			object_chances.insert(pair<int, int>(AI_PATROLLER,   0));
			object_chances.insert(pair<int, int>(AI_SPAWNER,     0));
			object_chances.insert(pair<int, int>(AI_SEEKER,      0));
			break;
		}
		case CAVETYPE_02:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(AI_SKITTISH,   25));
			object_chances.insert(pair<int, int>(AI_REGULAR,    50));
			object_chances.insert(pair<int, int>(AI_AGGRESSIVE,  0));
			object_chances.insert(pair<int, int>(AI_PATROLLER,  25));
			object_chances.insert(pair<int, int>(AI_SPAWNER,     0));
			object_chances.insert(pair<int, int>(AI_SEEKER,      0));
			break;
		}
		case CAVETYPE_03:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(AI_SKITTISH,    0));
			object_chances.insert(pair<int, int>(AI_REGULAR,     0));
			object_chances.insert(pair<int, int>(AI_AGGRESSIVE, 25));
			object_chances.insert(pair<int, int>(AI_PATROLLER,  50));
			object_chances.insert(pair<int, int>(AI_SPAWNER,    25));
			object_chances.insert(pair<int, int>(AI_SEEKER,      0));
			break;
		}
		case CAVETYPE_04:
		{
			object_chances.clear();
			object_chances.insert(pair<int, int>(AI_SKITTISH,    0));
			object_chances.insert(pair<int, int>(AI_REGULAR,     0));
			object_chances.insert(pair<int, int>(AI_AGGRESSIVE, 25));
			object_chances.insert(pair<int, int>(AI_PATROLLER,  25));
			object_chances.insert(pair<int, int>(AI_SPAWNER,    25));
			object_chances.insert(pair<int, int>(AI_SEEKER,     25));
			break;
		}
		default: break;
	}
}

void MapData::AddWall(int x, int y, bool imprevious)
{
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(' ');
	Object *wall = new Object(xlist, ylist, symlist, TCODColor::white, "A Wall", 2.0f, true);
	if( !imprevious )
	{
					//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
		Stats stats = Stats(100, 0, 5, 0, 0, 0, 0, 0, 0, 0);
					//  Status(hp, mp, xpnext)
		Status status = Status(100, 0, -1);
		wall->entity = new Entity(Entity::INANIMATE, stats, status, engine->mapID, CHAR_RUBBLE_PILE, TCODColor::white, "A Pile Of Rubble");
	}
	objects.push(wall);

	SetWall(x, y);
}

void MapData::AddTunnelUp(int x, int y, int mapID, int xTo, int yTo)
{
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(CHAR_STAIRS_UP);
	Object *tunnel = new Object(xlist, ylist, symlist, TCODColor::white, "A Tunnel Up", 1000.0f, false);
	tunnel->traversable = new Traversable(mapID, xTo, yTo);
	objects.push(tunnel);
	SendToBack(tunnel);
}

void MapData::AddTunnelDown(int x, int y, int mapID, int xTo, int yTo)
{
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(CHAR_STAIRS_DOWN);
	Object *tunnel = new Object(xlist, ylist, symlist, TCODColor::white, "A Tunnel Down", 1000.0f, false);
	tunnel->traversable = new Traversable(mapID, xTo, yTo);
	objects.push(tunnel);
	SendToBack(tunnel);
}

void MapData::AddTunnelSurface(int x, int y, int mapID, int xTo, int yTo)
{
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y); symlist.push(CHAR_STAIRS_UP);
	Object *tunnel = new Object(xlist, ylist, symlist, TCODColor::sepia, "A Tunnel To The Surface", 1000.0f, false);
	tunnel->traversable = new Traversable(mapID, xTo, yTo);
	objects.push(tunnel);
	SendToBack(tunnel);
}

void MapData::AddMapLocation(int x, int y, int mapID, int xTo, int yTo)
{
	string desc;
	TCODColor colour = TCODColor::white;
	TCODList<int> xlist, ylist, symlist;
	xlist.push(x); ylist.push(y);
	if( mapID >= TEMPLE_LIGHT && mapID <= TEMPLE_EARTH )
	{
		symlist.push(CHAR_TEMPLE);
		desc = LocationNames[mapID];
		switch( mapID )
		{
			case TEMPLE_LIGHT:
			{
				colour = TCODColor::lightestYellow;
				break;
			}
			case TEMPLE_FIRE:
			{
				colour = TCODColor::red;
				break;
			}
			case TEMPLE_WATER:
			{
				colour = TCODColor::blue;
				break;
			}
			case TEMPLE_WIND:
			{
				colour = TCODColor::yellow;
				break;
			}
			case TEMPLE_EARTH:
			{
				colour = TCODColor::green;
				break;
			}
			default: break;
		}
	}
	else if( mapID >= TOWN_01 && mapID <= TOWN_12 )
	{
		desc = LocationNames[mapID];
		symlist.push(CHAR_TOWN);
	}
	else
	{
		desc = LocationNames[CAVE_01];
		symlist.push(CHAR_CAVE);
	}
	Object *tunnel = new Object(xlist, ylist, symlist, colour, desc, 1000.0f, false);
	tunnel->traversable = new Traversable(mapID, xTo, yTo);
	objects.push(tunnel);
	SendToBack(tunnel);
}

void MapData::AddItem(int x, int y)
{
	int itemType = RandomChoice(object_chances);
	TCODList<int> xlist, ylist, symlist;
	switch( itemType )
	{
		// Consumable Item
		case Object::CONSUMABLE:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_MUSHROOM);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "A Mushroom", 0.05f, false);
			item->consumable = new Consumable(Consumable::MUSHROOM_UNKNOWN);
			objects.push(item);
			break;
		}
		// Container Item
		case Object::CONTAINER:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_CHEST_CLOSED);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "A Small Wooden Chest", 2.0f, false);
			item->container = new Container(8);
			objects.push(item);
			break;
		}
		// Entity Item
		case Object::ENTITY:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_GOBLIN_PEON);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "An Orc", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
						//  Status(hp, mp, xpnext)
			Status status = Status(0, 0, 0);
			item->entity = new Entity(Entity::TROGLODYTE, stats, status, engine->mapID, CHAR_RUBBLE_PILE, TCODColor::peach, "A Pile of Entrails");
			int size = item->sym.size();
			item->sym.clear();
			for(int i = 0; i < size; i++) item->sym.push(item->entity->corpseSym);
			item->colour = item->entity->corpseColour;	
			item->name = item->entity->corpseName;
			item->obstructs = false;
			objects.push(item);
			break;
		}
		// Wieldable Item
		case Object::WIELDABLE:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_SWORD_BASIC);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "A Bronze Sword", 1.0f, false);
			item->wieldable = new Wieldable(Wieldable::BRONZE_SWORD);
			objects.push(item);
			break;
		}
		// Wearable Item
		case Object::WEARABLE:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_ARMOUR_YELLOW);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "Leather Armour", 1.0f, false);
			item->wearable = new Wearable(Wearable::LEATHER_ARMOUR);
			objects.push(item);
			break;
		}
		// A Pile Of Rubble
		case Object::MISC:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_RUBBLE_PILE);
			Object *item = new Object(xlist, ylist, symlist, TCODColor::white, "A Pile Of Rubble", 2.0f, false);
			objects.push(item);
			break;
		}
		default: break;
	}
}

void MapData::AddTrap(int x, int y)
{
	int trapType = RandomChoice(object_chances);
	SetTrap(x, y, trapType);
}

void MapData::AddCreature(int x, int y)
{
	int creatureType = RandomChoice(object_chances);
	TCODList<int> xlist, ylist, symlist;
	switch( creatureType )
	{
		// Orc
		case AI_SKITTISH:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_GOBLIN_PEON);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Goblin", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(10, 4, 2, 5, 5, 0, 0, 0, 0, 0);
						//  Status(hp, mp, xpnext)
			Status status = Status(10, 0, -5);
			creature->entity = new Entity(Entity::TROGLODYTE, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "A Goblin Corpse");
			creature->entity->ai = new CreatureAI(creatureType, RNG->getInt(IQMIN, IQMAX));
			creature->container = new Container(5);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		// Goblin
		case AI_REGULAR:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_ORC_PEON);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "An Orc", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(15, 5, 3, 5, 5, 0, 0, 0, 0, 0);
						//  Status(hp, mp, xpnext)
			Status status = Status(15, 0, -7);
			creature->entity = new Entity(Entity::TROGLODYTE, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "An Orc Corpse");
			creature->entity->ai = new CreatureAI(creatureType, RNG->getInt(IQMIN, IQMAX));
			creature->container = new Container(5);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		// Warg
		case AI_AGGRESSIVE:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_VERMIN_BROWN);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Warg", 0.75f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(20, 8, 3, 10, 8, 0, 0, 0, 0, 0);
						//  Status(hp, mp, xpnext)
			Status status = Status(20, 0, -10);
			creature->entity = new Entity(Entity::BEAST, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "A Warg Carcass");
			creature->entity->ai = new CreatureAI(creatureType, RNG->getInt(IQMIN, IQMAX));
			creature->container = new Container(5);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		// Troll
		case AI_PATROLLER:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_ORGE_PEON_GREEN);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Troll", 1.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(30, 8, 4, 15, 4, 0, 0, 0, 0, 0);
						//  Status(hp, mp, xpnext)
			Status status = Status(30, 0, -15);
			creature->entity = new Entity(Entity::TROGLODYTE, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "A Troll Corpse");
			creature->entity->ai = new CreatureAI(creatureType, RNG->getInt(IQMIN, IQMAX));
			creature->container = new Container(5);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		// Demon
		case AI_SPAWNER:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_FLAYER_MAGE);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Flayer Mage", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(30, 6, 5, 10, 6, 0, 0, 0, 0, 0);
						//  Status(hp, mp, xpnext)
			Status status = Status(30, 0, -15);
			creature->entity = new Entity(Entity::HUMANOID, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "A Flayer Corpse");
			creature->entity->ai = new CreatureAI(creatureType, RNG->getInt(IQMIN, IQMAX));
			creature->container = new Container(5);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		case AI_SEEKER:
		{
			xlist.push(x); ylist.push(y); symlist.push(CHAR_DEMON_MAGE);
			Object *creature = new Object(xlist, ylist, symlist, TCODColor::white, "A Demon Mage", 0.5f, true);
						//Stats(hpmax, ap, dp, str, spd, mpmax, map, mdp, wil, acu)
			Stats stats = Stats(30, 6, 5, 10, 6, 0, 0, 0, 0, 0);
						//  Status(hp, mp, xpnext)
			Status status = Status(30, 0, -15);
			creature->entity = new Entity(Entity::HUMANOID, stats, status, engine->mapID, CHAR_SKULL, TCODColor::white, "A Demon Corpse");
			creature->entity->ai = new CreatureAI(creatureType, RNG->getInt(IQMIN, IQMAX));
			creature->container = new Container(5);
			objects.push(creature);
			for(int i = 0; i < creature->sym.size(); i++) SetCreature(creature->x.get(i), creature->y.get(i));
			break;
		}
		default: break;
	}
}

void MapData::AddBoss(int x, int y)
{
	TCODList<int> xlist, ylist, symlist;

	xlist.push(x + 0); ylist.push(y + 0); symlist.push(CHAR_DEMONLORD_RED_UL);
	xlist.push(x + 1); ylist.push(y + 0); symlist.push(CHAR_DEMONLORD_RED_UR);
	xlist.push(x + 0); ylist.push(y + 1); symlist.push(CHAR_DEMONLORD_RED_LL);
	xlist.push(x + 1); ylist.push(y + 1); symlist.push(CHAR_DEMONLORD_RED_LR);

	Object *boss = new Object(xlist, ylist, symlist, TCODColor::white, "Red Demon Lord", 1000.0f, true);
	Stats stats = Stats(100, 10, 10, 10, 25, 100, 5, 5, 5, 5);
	Status status = Status(100, 100, -50);
	boss->entity = new Entity(Entity::BOSS, stats, status, engine->mapID, CHAR_RUBBLE_PILE, TCODColor::peach, "A Pile of Entrails");
	boss->entity->ai = new BossAI(RNG->getInt(BossAI::VERTICAL_PATTERN, BossAI::NPATTERNTYPES - 1));
	boss->container = new Container(5);
	objects.push(boss);
	for(int i = 0; i < boss->sym.size(); i++) SetCreature(boss->x.get(i), boss->y.get(i));
}

void MapData::AddNpc(int type, int x, int y)
{
	Npc *npc = new Npc(type, x, y);
	objects.push(npc);
	for(int i = 0; i < npc->sym.size(); i++) SetNpc(npc->x.get(i), npc->y.get(i));
}

int MapData::RandomChoiceIndex(TCODList<int> chances)
{
	int chances_sum = 0;
	int running_sum = 0;
	int choice = 0;
	int dice = 1;

	for(int i = 0; i < chances.size(); i++) chances_sum += chances.get(i);
	dice = RNG->getInt(1, chances_sum);
 
	// Go through all chances, keeping the sum so far
	for(int i = 0; i < chances.size(); i++)
	{
		running_sum += chances.get(i);

		// See if the dice landed in the part that corresponds to this choice
		if( dice <= running_sum )
		{
			break;
		}
		else
		{
			choice++;
		}
	}
	if(choice >= chances.size()) choice = chances.size() - 1;
	return choice;
}

int MapData::RandomChoice(map<int, int> object_chances)
{
	TCODList<int> keys, chances;
	for(map<int, int>::iterator it = object_chances.begin(); it != object_chances.end(); it++)
	{
		keys.push(it->first);
		chances.push(it->second);
	}
	return keys.get(RandomChoiceIndex(chances));
}

void MapData::SendToBack(Object *object)
{
	objects.remove(object);
	objects.insertBefore(object, 0);
}

bool MapData::IsObstructed(int x, int y) const
{
	Object *object = GetObject(x, y);
	if( object )
	{
		return object->obstructs;
	}
	else
	{
		return false;
	}
}

Object *MapData::GetObject(int x, int y) const
{
	for(int i = objects.size() - 1; i >= 0; i--)
	{
		Object *object = objects.get(i);
		for(int j = 0; j < object->sym.size(); j++)
		{
			if( object->x.get(j) == x && object->y.get(j) == y ) return object;
		}
	}
	return NULL;
}

Object *MapData::GetEntity(int x, int y) const
{
	for(int i = objects.size() - 1; i >= 0; i--)
	{
		Object *object = objects.get(i);
		if( object->entity && !object->entity->IsDead() )
		{
			for(int j = 0; j < object->sym.size(); j++)
			{
				if( object->x.get(j) == x && object->y.get(j) == y ) return object;
			}
		}
	}
	return NULL;
}

Object *MapData::GetEntity(int id) const
{
	for(int i = objects.size() - 1; i >= 0; i--)
	{
		Object *object = objects.get(i);
		if( object->entity && !object->entity->IsDead() )
		{
			for(int j = 0; j < object->sym.size(); j++)
			{
				if( object->id == id ) return object;
			}
		}
	}
	return NULL;
}

void MapData::GenerateMap(int locationID, int mapType)
{
	const int dx[NBLOCK] = {-1, 0, +1, -1, 0, +1, -1, 0, +1};
	const int dy[NBLOCK] = {-1, -1, -1, 0, 0, 0, +1, +1, +1};

	type = mapType;

	// Assign Features to each cell
	Feature *feature = new FloorFeature();
	for(int i = 0; i < width*height; i++)
	{
		Cell cell;
		cell.SetFeature(feature);
		cell.SetDefaultFeature(feature);
		cells.push_back(cell);
	}
	delete feature;
	feature = NULL;

	for(int x = 0; x < width; x++)
	{
		AddWall(x, 0, true);
		AddWall(x, height - 1, true);
	}

	for(int y = 1; y < height - 1; y++)
	{
		AddWall(0, y, true);
		AddWall(width - 1, y, true);
	}

	if( locationID < CAVE_01 )
	{
		switch( type )
		{
			case WORLD_TYPE:
			{
				// Generate names of equipment
				string tmp;
				TCODNamegen::parse("data/namegen/equip_names.cfg");
				for(int i = 0; i < NWEAPONS; i++)
				{
					tmp.clear();
					tmp.append("%c");
					tmp.append(TCODNamegen::generate("Weapon Name", RNG));
					tmp.resize(18,' ');
					tmp.append("%c");
					WeaponNames.push_back(tmp);
				}

				for(int i = 0; i < NSHIELDS; i++)
				{
					tmp.clear();
					tmp.append("%c");
					tmp.append(TCODNamegen::generate("Shield Name", RNG));
					tmp.resize(18,' ');
					tmp.append("%c");
					ShieldNames.push_back(tmp);
				}

				for(int i = 0; i < NARMOUR; i++)
				{
					tmp.clear();
					tmp.append("%c");
					tmp.append(TCODNamegen::generate("Armour Name", RNG));
					tmp.resize(18,' ');
					tmp.append("%c");
					ArmourNames.push_back(tmp);
				}

				for(int i = 0; i < NACCESSORY; i++)
				{
					tmp.clear();
					tmp.append("%c");
					tmp.append(TCODNamegen::generate("Accessory Name", RNG));
					tmp.resize(18,' ');
					tmp.append("%c");
					AccessoryNames.push_back(tmp);
				}

				LocationNames.push_back("The World Map");
				LocationNames.push_back("The Temple Of Light");
				LocationNames.push_back("The Temple Of Fire");
				LocationNames.push_back("The Temple Of Water");
				LocationNames.push_back("The Temple Of Wind");
				LocationNames.push_back("The Temple Of Earth");

				TCODNamegen::parse("data/namegen/town_names.cfg");
				for(int i = 0; i < NTOWNS; i++)
				{
					tmp.clear();
					tmp.append("Town Of ");
					tmp.append(TCODNamegen::generate("mingos town", RNG));
					LocationNames.push_back(tmp);
				}

				for(int i = 0; i < NCAVE_REGIONS*NLEVELS_REGION*NCAVES; i++) LocationNames.push_back("A Cave");
				break;
			}
			case TEMPLE_TYPE:
			{
				break;
			}
			case TOWN_TYPE:
			{
				break;
			}
			default: break;
		}
	}
	else
	{
		switch( type )
		{
			case CAVETYPE_01:
			{
				for(int i = 0; i < NBLOCK; i++)
				{
					AddWall(width/2 + dx[i], height/3 + dy[i], false);
					AddWall(width/2 + dx[i], 2*height/3 + dy[i], false);
					AddWall(width/3 + dx[i], height/2 + dy[i], false);
					AddWall(2*width/3 + dx[i], height/2 + dy[i], false);
				}

				//nTraps = 6;
				GetTrapChances(type);
				for(int i = 0; i < nTraps; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) || FeatureType(x, y) == FEATURE_TRAP )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddTrap(x, y);
				}

				//nItems = 16;
				GetItemChances(type);
				for(int i = 0; i < nItems; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddItem(x, y);
				}

				//nCreatures = 3;
				GetCreatureChances(type);
				for(int i = 0; i < nCreatures; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) || FeatureType(x, y) == FEATURE_TRAP )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddCreature(x, y);
				}
				break;
			}
			case CAVETYPE_02:
			{
				for(int i = 0; i < 50; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddWall(x, y, false);
				}

				//nTraps = 6;
				GetTrapChances(type);
				for(int i = 0; i < nTraps; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) || FeatureType(x, y) == FEATURE_TRAP )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddTrap(x, y);
				}

				//nItems = 16;
				GetItemChances(type);
				for(int i = 0; i < nItems; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddItem(x, y);
				}

				//nCreatures = 2;
				GetCreatureChances(type);
				for(int i = 0; i < nCreatures; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) || FeatureType(x, y) == FEATURE_TRAP )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddCreature(x, y);
				}
				break;
			}
			case CAVETYPE_03:
			{
				for(int i = 0; i < 25; i++)
				{
					int x = RNG->getInt(3, width - 4);
					int y = RNG->getInt(3, height - 4);
					while( IsObstructed(x, y) )
					{
						x = RNG->getInt(3, width - 4);
						y = RNG->getInt(3, height - 4);
					}
					for(int j = 0; j < NBLOCK; j++) AddWall(x + dx[j], y + dy[j], false);
				}

				//nTraps = 6;
				GetTrapChances(type);
				for(int i = 0; i < nTraps; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) || FeatureType(x, y) == FEATURE_TRAP )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddTrap(x, y);
				}

				//nItems = 16;
				GetItemChances(type);
				for(int i = 0; i < nItems; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddItem(x, y);
				}

				//nCreatures = 5;
				GetCreatureChances(type);
				for(int i = 0; i < nCreatures; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) || FeatureType(x, y) == FEATURE_TRAP )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddCreature(x, y);
				}
				break;
			}
			case CAVETYPE_04:
			{
				for(int i = 0; i < 25; i++)
				{
					int x = RNG->getInt(3, width - 4);
					int y = RNG->getInt(3, height - 4);
					while( IsObstructed(x, y) )
					{
						x = RNG->getInt(3, width - 4);
						y = RNG->getInt(3, height - 4);
					}
					for(int j = 0; j < NBLOCK; j++) AddWall(x + dx[j], y + dy[j], false);
				}

				//nTraps = 6;
				GetTrapChances(type);
				for(int i = 0; i < nTraps; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) || FeatureType(x, y) == FEATURE_TRAP )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddTrap(x, y);
				}

				//nItems = 16;
				GetItemChances(type);
				for(int i = 0; i < nItems; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddItem(x, y);
				}

				//nCreatures = 5;
				GetCreatureChances(type);
				for(int i = 0; i < nCreatures; i++)
				{
					int x = RNG->getInt(2, width - 3);
					int y = RNG->getInt(2, height - 3);
					while( IsObstructed(x, y) || FeatureType(x, y) == FEATURE_TRAP )
					{
						x = RNG->getInt(2, width - 3);
						y = RNG->getInt(2, height - 3);
					}
					AddCreature(x, y);
				}
				break;
			}
			case BOSS_TYPE:
			{
				nCreatures = 3;

				// Add Boss
				int x = RNG->getInt(width/2 - 1, width/2 + 1);
				int y = RNG->getInt(height/2 - 1, height/2 + 1);
				while( IsObstructed(x, y) || FeatureType(x, y) == FEATURE_TRAP )
				{
					x = RNG->getInt(width/2 - 1, width/2 + 1);
					y = RNG->getInt(height/2 - 1, height/2 + 1);
				}
				//AddBoss(x, y);

				break;
			}
			default: break;
		}
	}
}