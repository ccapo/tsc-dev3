#include "Main.hpp"

//------------------------------------------------------------------------
//
// Methods for Idle
//
//------------------------------------------------------------------------
NpcIdle *NpcIdle::Instance()
{
	static NpcIdle instance;
	return &instance;
}

void NpcIdle::Enter(Npc *npc){}

bool NpcIdle::Update(Npc *npc, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse){return true;}

void NpcIdle::Render(Npc *npc)
{
	for(int i = 0; i < npc->sym.size(); i++)
	{
		TCODConsole::root->setChar(npc->x.get(i), npc->y.get(i) + 3, npc->sym.get(i));
		TCODConsole::root->setCharForeground(npc->x.get(i), npc->y.get(i) + 3, npc->colour);
	}
}

//------------------------------------------------------------------------
//
// Methods for Active
//
//------------------------------------------------------------------------
NpcActive *NpcActive::Instance()
{
	static NpcActive instance;
	return &instance;
}

void NpcActive::Enter(Npc *npc){}

bool NpcActive::Update(Npc *npc, float elapsed, TCOD_key_t &key, TCOD_mouse_t &mouse)
{
	return npc->entity->ai->Update(npc);
}

void NpcActive::Render(Npc *npc)
{
	for(int i = 0; i < npc->sym.size(); i++)
	{
		TCODConsole::root->setChar(npc->x.get(i), npc->y.get(i) + 3, npc->sym.get(i));
		TCODConsole::root->setCharForeground(npc->x.get(i), npc->y.get(i) + 3, npc->colour);
	}
}