#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for MapIdle
//
//------------------------------------------------------------------------
MapIdle *MapIdle::Instance()
{
	static MapIdle instance;
	return &instance;
}

bool MapIdle::Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}
void MapIdle::Render(Map *map){}

//------------------------------------------------------------------------
//
// Methods for MapWorld
//
//------------------------------------------------------------------------
MapWorld *MapWorld::Instance()
{
	static MapWorld instance;
	return &instance;
}

void MapWorld::Enter(Map *map)
{
	int w, h;
	map->mapData[engine->mapID].img = new TCODImage("data/img/worldmap.png");
	map->mapData[engine->mapID].imgThumb = new TCODImage("data/img/worldmap.png");
	map->mapData[engine->mapID].imgThumb->getSize(&w, &h);
	map->mapData[engine->mapID].imgThumb->scale(2*w/31, 2*h/31);
}

bool MapWorld::Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	// Update all the objects
	for(int i = 0; i < map->mapData[engine->mapID].objects.size(); i++)
	{
		Object *object = map->mapData[engine->mapID].objects.get(i);
		object->Update(elapsed, key, mouse);
	}

	return true;
}

void MapWorld::Render(Map *map)
{
	int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
	int w2 = DISPLAY_WIDTH/4 + 3, h2 = NMSGS + 4;
	int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 5;

	map->mapData[engine->mapID].img->blit2x(TCODConsole::root, 0, 3, 0, 0, w, h);
	map->mapData[engine->mapID].imgThumb->blit2x(TCODConsole::root, tx, ty);
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->printFrame(tx - 1, ty - 1, w2, h2, false, TCOD_BKGND_SET, "World Map");

	// for(int x = 0; x < map->mapData[engine->mapID].width; x++)
	// {
	// 	for(int y = 0; y < map->mapData[engine->mapID].height; y++)
	// 	{
	// 		TCODConsole::root->setCharBackground(x, y + 3, map->mapData[engine->mapID].Colour(x, y), TCOD_BKGND_SCREEN);
	// 	}
	// }

	// Draw all the objects
	for(int i = 0; i < map->mapData[engine->mapID].objects.size(); i++)
	{
		Object *object = map->mapData[engine->mapID].objects.get(i);
		object->Render();
	}
}

void MapWorld::Exit(Map *map)
{
	if( map->mapData[engine->mapID].img != NULL )
	{
		delete map->mapData[engine->mapID].img;
		map->mapData[engine->mapID].img = NULL;
	}

	if( map->mapData[engine->mapID].imgThumb )
	{
		delete map->mapData[engine->mapID].imgThumb;
		map->mapData[engine->mapID].imgThumb = NULL;
	}
}

//------------------------------------------------------------------------
//
// Methods for MapTemple
//
//------------------------------------------------------------------------
MapTemple *MapTemple::Instance()
{
	static MapTemple instance;
	return &instance;
}

void MapTemple::Enter(Map *map)
{
	int w, h;
	map->mapData[engine->mapID].img = new TCODImage("data/img/templemap.png");
	map->mapData[engine->mapID].imgThumb = new TCODImage("data/img/templemap.png");
	map->mapData[engine->mapID].imgThumb->getSize(&w, &h);
	map->mapData[engine->mapID].imgThumb->scale(2*w/15, 2*h/15);
}

bool MapTemple::Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	// Update all the objects
	for(int i = 0; i < map->mapData[engine->mapID].objects.size(); i++)
	{
		Object *object = map->mapData[engine->mapID].objects.get(i);
		object->Update(elapsed, key, mouse);
	}

	return true;
}

void MapTemple::Render(Map *map)
{
	int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
	int w2 = DISPLAY_WIDTH/4 + 3, h2 = NMSGS + 4;
	int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 5;

	map->mapData[engine->mapID].img->blit2x(TCODConsole::root, 0, 3, 0, 0, w, h);
	map->mapData[engine->mapID].imgThumb->blit2x(TCODConsole::root, tx, ty);
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->printFrame(tx - 1, ty - 1, w2, h2, false, TCOD_BKGND_SET, "Temple Map");

	// for(int x = 0; x < map->mapData[engine->mapID].width; x++)
	// {
	// 	for(int y = 0; y < map->mapData[engine->mapID].height; y++)
	// 	{
	// 		TCODConsole::root->setCharBackground(x, y + 3, map->mapData[engine->mapID].Colour(x, y), TCOD_BKGND_SCREEN);
	// 	}
	// }

	// Draw all the objects
	for(int i = 0; i < map->mapData[engine->mapID].objects.size(); i++)
	{
		Object *object = map->mapData[engine->mapID].objects.get(i);
		object->Render();
	}
}

void MapTemple::Exit(Map *map)
{
	if( map->mapData[engine->mapID].img != NULL )
	{
		delete map->mapData[engine->mapID].img;
		map->mapData[engine->mapID].img = NULL;
	}

	if( map->mapData[engine->mapID].imgThumb )
	{
		delete map->mapData[engine->mapID].imgThumb;
		map->mapData[engine->mapID].imgThumb = NULL;
	}
}

//------------------------------------------------------------------------
//
// Methods for MapTown
//
//------------------------------------------------------------------------
MapTown *MapTown::Instance()
{
	static MapTown instance;
	return &instance;
}

void MapTown::Enter(Map *map)
{
	int w, h;
	map->mapData[engine->mapID].img = new TCODImage("data/img/townmap.png");
	map->mapData[engine->mapID].imgThumb = new TCODImage("data/img/townmap.png");
	map->mapData[engine->mapID].imgThumb->getSize(&w, &h);
	map->mapData[engine->mapID].imgThumb->scale(2*w/15, 2*h/15);
}

bool MapTown::Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	// Update all the objects
	for(int i = 0; i < map->mapData[engine->mapID].objects.size(); i++)
	{
		Object *object = map->mapData[engine->mapID].objects.get(i);
		object->Update(elapsed, key, mouse);
	}

	return true;
}

void MapTown::Render(Map *map)
{
	int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
	int w2 = DISPLAY_WIDTH/4 + 3, h2 = NMSGS + 4;
	int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 5;

	map->mapData[engine->mapID].img->blit2x(TCODConsole::root, 0, 3, 0, 0, w, h);
	map->mapData[engine->mapID].imgThumb->blit2x(TCODConsole::root, tx, ty);
	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->printFrame(tx - 1, ty - 1, w2, h2, false, TCOD_BKGND_SET, "Town Map");

	// for(int x = 0; x < map->mapData[engine->mapID].width; x++)
	// {
	// 	for(int y = 0; y < map->mapData[engine->mapID].height; y++)
	// 	{
	// 		TCODConsole::root->setCharBackground(x, y + 3, map->mapData[engine->mapID].Colour(x, y), TCOD_BKGND_SCREEN);
	// 	}
	// }

	// Draw all the objects
	for(int i = 0; i < map->mapData[engine->mapID].objects.size(); i++)
	{
		Object *object = map->mapData[engine->mapID].objects.get(i);
		object->Render();
	}
}

void MapTown::Exit(Map *map)
{
	if( map->mapData[engine->mapID].img != NULL )
	{
		delete map->mapData[engine->mapID].img;
		map->mapData[engine->mapID].img = NULL;
	}

	if( map->mapData[engine->mapID].imgThumb )
	{
		delete map->mapData[engine->mapID].imgThumb;
		map->mapData[engine->mapID].imgThumb = NULL;
	}
}

//------------------------------------------------------------------------
//
// Methods for MapCave
//
//------------------------------------------------------------------------
MapCave *MapCave::Instance()
{
	static MapCave instance;
	return &instance;
}

void MapCave::Enter(Map *map){}

bool MapCave::Update(Map *map, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	// Update all the objects
	for(int i = 0; i < map->mapData[engine->mapID].objects.size(); i++)
	{
		Object *object = map->mapData[engine->mapID].objects.get(i);
		object->Update(elapsed, key, mouse);
	}

	return true;
}

void MapCave::Render(Map *map)
{
	int w = 2*DISPLAY_WIDTH, h = 2*DISPLAY_HEIGHT;
	int w2 = DISPLAY_WIDTH/4 + 3, h2 = NMSGS + 4;
	int tx = 3*DISPLAY_WIDTH/4 - 1, ty = DISPLAY_HEIGHT + 5;

	TCODConsole::root->setDefaultBackground(TCODColor::black);
	TCODConsole::root->setDefaultForeground(TCODColor::white);
	TCODConsole::root->printFrame(tx - 1, ty - 1, w2, h2, false, TCOD_BKGND_SET, "Cave Map");

	for(int x = 0; x < map->mapData[engine->mapID].width; x++)
	{
		for(int y = 0; y < map->mapData[engine->mapID].height; y++)
		{
			TCODConsole::root->setCharBackground(x, y + 3, map->mapData[engine->mapID].Colour(x, y), TCOD_BKGND_SCREEN);
		}
	}

	// Draw all the objects
	for(int i = 0; i < map->mapData[engine->mapID].objects.size(); i++)
	{
		Object *object = map->mapData[engine->mapID].objects.get(i);
		object->Render();
	}
}

void MapCave::Exit(Map *map){}