#include "Main.hpp"

Object::Object(TCODList<int> x, TCODList<int> y, TCODList<int> sym, const TCODColor &colour, string name, float mass, bool obstructs): id(0), x(x), y(y), sym(sym), colour(colour), name(name), mass(mass), obstructs(obstructs), counter(-1) , consumable(NULL), container(NULL), entity(NULL), traversable(NULL), wearable(NULL), wieldable(NULL)
{
	xc = 0.0f;
	yc = 0.0f;
	for(int i = 0; i < sym.size(); i++)
	{
		xc += x.get(i);
		yc += y.get(i);
	}
	xc /= static_cast<float>(sym.size());
	yc /= static_cast<float>(sym.size());
}

Object::~Object()
{
	if( consumable != NULL )
	{
		delete consumable;
		consumable = NULL;
	}

	if( container != NULL )
	{
		delete container;
		container = NULL;
	}

	if( entity != NULL )
	{
		delete entity;
		entity = NULL;
	}

	if( traversable != NULL )
	{
		delete traversable;
		traversable = NULL;
	}

	if( wearable != NULL )
	{
		delete wearable;
		wearable = NULL;
	}

	if( wieldable != NULL )
	{
		delete wieldable;
		wieldable = NULL;
	}
}

bool Object::Update(float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	if( counter == 0 )
	{
		// Rotate sym list for animated objects
		counter = FPSMAX/2;
		int symbol = sym.get(sym.size() - 1);
		for(int i = 0; i < sym.size() - 1; i++) sym.set(sym.get(i + 1), i);
		sym.set(symbol, sym.size() - 1);
	}
	else if( counter > 0 )
	{
		counter--;
	}

	if( entity != NULL && entity->ai != NULL )
	{
		return entity->ai->Update(this);
	}
	else
	{
		return false;
	}
}

void Object::Render() const
{
	for(int i = 0; i < sym.size(); i++)
	{
		TCODConsole::root->setChar(x.get(i), y.get(i) + 3, sym.get(i));
		TCODConsole::root->setCharForeground(x.get(i), y.get(i) + 3, colour);
	}
}

bool Object::Receive(const Message &msg){return true;}