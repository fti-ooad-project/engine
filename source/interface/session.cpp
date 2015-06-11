#include "../processor.hpp"
#include "../storage.hpp"

#define ProcessorWrapper Processor
#define StorageWrapper Storage

#include <engine/session.hpp>

#include "spectatorimpl.hpp"
#include "playerhandleimpl.hpp"

#include <view.hpp>

Session::Session(int c_players_count)
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
}

Session::~Session()
{
	delete spectator;
	for(int i = 0; i < players_count; ++i)
	{
		delete players[i];
	}
	delete[] players;
	delete processor;
	delete storage;
}

PlayerHandle *Session::getPlayerHandle(int num)
{
	if(num >= 0 && num < players_count)
	{
		return players[num];
	}
	return nullptr;
}

int Session::getPlayersCount() const
{
	return players_count;
}

Spectator *Session::getSpectator()
{
	return spectator;
}

void Session::process(double dt)
{
	int iter = 0x1;
	for(int i = 0; i < iter; ++i)
	{
		processor->attract();
		processor->move(dt/iter);
		processor->interact();
	}
}

bool Session::loadMap()
{
	for(int i = 0; i < 0xa; ++i)
	{
		Object *o = new Object();
		o->setInvMass(0.0001);
		o->setSize(2.0);
		o->setPos(5.0*vec2(i%5 - 2,i/5));
		storage->addObject(o);
	}
	return true;
}
