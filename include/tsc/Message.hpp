#ifndef MESSAGE_HPP
#define MESSAGE_HPP
//------------------------------------------------------------------------
//
// Name: Message.hpp
//
// Desc: This defines a Message. A Message is a data structure that
//			 records information required to dispatch messages. Messages 
//			 are used by game agents to communicate with each other.
//
// Author: Mat Buckland (fup@ai-junkie.com)
//
// Modified: Chris Capobianco, 2012-09-29
//
//------------------------------------------------------------------------
#include "Global.hpp"

struct Message
{
	// The message index. These are all enumerated in the file "MessageTypes.h"
	int index;

	// Extra data passed along with the message (e.g. Content)
	string text;

	Message() : index(MSG_DEFAULT), text("") {}

	Message(int index) : index(index), text("") {}

	Message(int index, string str) : index(index), text(str) {}

};

#endif