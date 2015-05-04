#pragma once

#include "spectator.hpp"
#include "playerhandle.hpp"

#ifndef StorageWrapper
#define StorageWrapper void
#endif

#ifndef ProcessorWrapper
#define ProcessorWrapper void
#endif

class Session
{
private:
	StorageWrapper *storage = nullptr;
	ProcessorWrapper *processor = nullptr;
	PlayerHandle **players = nullptr;
	Spectator *spectator = nullptr;
	const int players_count;
	
public:
	Session(int c_players_count);
	~Session();
	
	PlayerHandle *getPlayerHandle(int num);
	int getPlayersCount() const;
	
	Spectator *getSpectator();
};
