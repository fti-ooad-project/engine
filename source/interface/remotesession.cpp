#include "../storage.hpp"
#include "../tcp/client.hpp"

#include <media/log.h>

#define StorageWrapper Storage
#define TCPConnectionWrapper TCPConnection

#include <engine/remotesession.hpp>

#include "spectatorimpl.hpp"

#include "../clientstream.hpp"

RemoteSession::RemoteSession(const std::string &host, int port)
  : players_count(0)
{
	storage = new Storage;
	
	spectator = new SpectatorImpl(storage,nullptr,players_count);
	
	state = SessionState::ENABLE;
	
	try
	{
		connection = TCPClient::connect(host,port);
	}
	catch(TCPException e)
	{
		connection = nullptr;
		printWarn("TCPException: %s\n",e.getMessage().data());
	}
	
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
		printWarn("TCPException: %s\n",e.getMessage().data());
	}
	
	delete spectator;
	delete storage;
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
