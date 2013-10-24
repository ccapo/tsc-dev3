#ifndef TRANSMITTER_HPP
#define TRANSMITTER_HPP
//------------------------------------------------------------------------
//
// Name: Transmitter.hpp
//
// Desc: A message Transmitter. Manages messages of the type Message.
//		Instantiated as a singleton.
//
// Author: Mat Buckland (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"
#include "Entity.hpp"
#include "Module.hpp"
#include "Engine.hpp"

class Engine;

// To make life easier...
#define Transmit Transmitter::Instance()

class Transmitter
{
private:

	Transmitter(){}

	// Copy constructor and assignment should be private
	Transmitter(const Transmitter&);
	Transmitter &operator=(const Transmitter&);

public:

	static Transmitter *Instance();

	// Send message index to entity pReceiver
	void Send(Entity *pReceiver, int index);

	// Send message index to Engine pReceiver
	void Send(Engine *pReceiver, int index);

	// Send message index w/ data to module pReceiver
	void Send(Module *pReceiver, int index, string data);
};

#endif