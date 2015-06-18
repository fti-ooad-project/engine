#pragma once

#include <string>

#include "spectator.hpp"
#include "playerhandle.hpp"

enum SessionState
{
	DISABLE = 0,
	ENABLE
};

class Session
{
public:
	virtual ~Session() {}
	
	virtual PlayerHandle *getPlayerHandle(int num) = 0;
	virtual int getPlayersCount() const = 0;
	
	virtual Spectator *getSpectator() = 0;
	virtual SessionState getState() const = 0;
};
