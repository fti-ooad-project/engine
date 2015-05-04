#include "../processor.hpp"
#include "../storage.hpp"

#define ProcessorWrapper Processor
#define StorageWrapper Storage

#include <engine/session.hpp>

#include "spectatorimpl.hpp"
#include "playerhandleimpl.hpp"

Session::Session(int c_players_count)
  : players_count(c_players_count)
{
	storage = new Storage;
	processor = new Processor;
	processor->setStorage(storage);
	players = new PlayerHandle*[players_count];
	for(int i = 0 ;i < players_count; ++i)
	{
		players[i] = new PlayerHandleImpl(storage);
	}
	spectator = new SpectatorImpl(storage);
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
