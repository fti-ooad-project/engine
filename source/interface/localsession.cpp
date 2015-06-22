#include "../processor.hpp"
#include "../storage.hpp"
#include "../tcp/server.hpp"

#include <media/log.h>

#define ProcessorWrapper Processor
#define StorageWrapper Storage
#define TCPServerWrapper TCPServer

#include <engine/localsession.hpp>

#include "spectatorimpl.hpp"
#include "playerhandleimpl.hpp"

#include "../serverstream.hpp"

LocalSession::LocalSession(int c_players_count, int port)
  : players_count(c_players_count)
{
	storage = new Storage;
	processor = new Processor;
	processor->setStorage(storage);
	players = new PlayerHandle*[players_count];
	for(int i = 0; i < players_count; ++i)
	{
		players[i] = new PlayerHandleImpl(storage);
	}
	spectator = new SpectatorImpl(storage,reinterpret_cast<PlayerSpectator**>(players),players_count);
	
	state = SessionState::ENABLE;
	
	auto handler = [this](TCPConnection *conn)
	{
		ServerStream(this,storage)(conn);
	};
	auto error_handler = [](const std::string &msg)
	{
		printWarn("LocalSession: %s\n",msg.data());
	};
	try
	{
		server = new TCPServer(port,handler,error_handler);
	}
	catch(TCPException e)
	{
		server = nullptr;
		printWarn("LocalSession: %s\n",e.getMessage().data());
	}
}

LocalSession::~LocalSession()
{
	state = SessionState::DISABLE;
	if(server != nullptr)
	{
		delete server;
	}
	
	delete spectator;
	for(int i = 0; i < players_count; ++i)
	{
		delete players[i];
	}
	delete[] players;
	delete processor;
	delete storage;
}

PlayerHandle *LocalSession::getPlayerHandle(int num)
{
	if(num >= 0 && num < players_count)
	{
		return players[num];
	}
	return nullptr;
}

int LocalSession::getPlayersCount() const
{
	return players_count;
}

Spectator *LocalSession::getSpectator()
{
	return spectator;
}

SessionState LocalSession::getState() const
{
	return state;
}

void LocalSession::process(double dt)
{
	int iter = 0x1;
	for(int i = 0; i < iter; ++i)
	{
		processor->attract();
		processor->move(dt/iter);
		processor->interact();
	}
}

void LocalSession::loadMap()
{
	for(int i = 0; i < 0x8; ++i)
	{
		Object *o = new Object();
		o->setInvMass(0.0001);
		o->setSize(1.2);
		o->setPos(10.0*vec2(i%4 - 1.5,i/4));
		storage->addObject(o);
	}
}

