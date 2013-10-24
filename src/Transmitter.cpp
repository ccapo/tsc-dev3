#include "Main.hpp"

// Uncomment below to display message info
//#define SHOW_MESSAGING_INFO

//------------------------------- Instance ------------------------------------
//
// This class is a singleton
//
//-----------------------------------------------------------------------------
Transmitter *Transmitter::Instance()
{
	static Transmitter instance; 
	return &instance;
}

//--------------------------------- Send --------------------------------------
//
// This method routes a message to a receiver entity
//
//-----------------------------------------------------------------------------
void Transmitter::Send(Entity *pReceiver, int index)
{
	// Make sure the receiver is valid
	if( pReceiver == NULL )
	{
		cout << "Warning! No Valid Receiver found" << endl;
		return;
	}

	// Create the Message
	Message msg = Message(index);

#ifdef SHOW_MESSAGING_INFO
	// Transmit the message
	cout << "Message Transmited to Entity, Msg: " << index << endl;
#endif

	// Send the Message to the recipient
	if( !pReceiver->Receive(msg) )
	{
		// Message could not be handled
		cout << "Message could not be handled" << endl;
	}
}

//--------------------------------- Send --------------------------------------
//
// This method routes a message with data to a receiver module
//
//-----------------------------------------------------------------------------
void Transmitter::Send(Module *pReceiver, int index, string data)
{
	// Make sure the receiver is valid
	if( pReceiver == NULL )
	{
		cout << "Warning! No Valid Sender Module Found" << endl;
		return;
	}

	// Create the Message
	Message msg = Message(index, data);

#ifdef SHOW_MESSAGING_INFO
	// Transmit the message
	cout << "Message Transmited to Module, Msg: " << data << endl;
#endif

	// Send the Message to the recipient
	if( !pReceiver->Receive(msg) )
	{
		// Message could not be handled
		cout << "Message could not be handled" << endl;
	}
}

//--------------------------------- Send --------------------------------------
//
// This method routes a message to a receiver Engine
//
//-----------------------------------------------------------------------------
void Transmitter::Send(Engine *pReceiver, int index)
{
	// Make sure the receiver is valid
	if( pReceiver == NULL )
	{
		cout << "Warning! No Valid Receiver Engine found" << endl;
		return;
	}

	// Create the Message
	Message msg = Message(index);

#ifdef SHOW_MESSAGING_INFO
	// Transmit the message
	cout << "Message Transmited to Engine, Msg: " << index << endl;
#endif

	// Send the Message to the recipient
	if( !pReceiver->Receive(msg) )
	{
		// Message could not be handled
		cout << "Message could not be handled" << endl;
	}
}