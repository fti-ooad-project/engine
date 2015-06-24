#include "../processor.hpp"
#include "../storage.hpp"
#include "../tcp/client.hpp"

#define ProcessorWrapper Processor
#define StorageWrapper Storage
#define TCPConnectionWrapper TCPConnection

#include <engine/remotesession.hpp>

#include "spectatorimpl.hpp"
#include "playerhandleclient.hpp"

#include "../clientstream.hpp"

#include <stdio.h>

RemoteSession::RemoteSession(const std::string &host, int port)
{
	storage = new Storage;
	processor = new Processor;
	processor->setStorage(storage);
	
	try
	{
		connection = TCPClient::connect(host,port);
	}
	catch(TCPException e)
	{
		connection = nullptr;
		fprintf(stderr,"TCPException: %s\n",e.getMessage().data());
	}
	
	players_count = 1;
	players = new PlayerHandle*[players_count];
	players[0] = new PlayerHandleClient(0,storage,connection);
	spectator = new SpectatorImpl(storage,reinterpret_cast<PlayerSpectator**>(players),players_count);
	
	state = SessionState::ENABLE;
	
	thread = new std::thread([this]()
	{
		ClientStream(this,storage)(connection);
	});
}

RemoteSession::~RemoteSession()
{
	state = SessionState::DISABLE;
	
	thread->join();
	
	try
	{
		TCPClient::disconnect(connection);
	}
	catch(TCPException e)
	{
		fprintf(stderr,"TCPException: %s\n",e.getMessage().data());
	}
	
	for(int i = 0; i < players_count; ++i)
	{
		delete players[i];
	}
	delete[] players;
	
	delete spectator;
	delete storage;
}

void RemoteSession::process(double dt)
{
	int iter = 0x1;
	for(int i = 0; i < iter; ++i)
	{
		processor->move(dt/iter);
	}
}

PlayerHandle *RemoteSession::getPlayerHandle(int num)
{
	if(num >= 0 && num < players_count)
	{
		return nullptr;
	}
	return nullptr;
}

int RemoteSession::getPlayersCount() const
{
	return players_count;
}

Spectator *RemoteSession::getSpectator()
{
	return spectator;
}

SessionState RemoteSession::getState() const
{
	return state;
}
