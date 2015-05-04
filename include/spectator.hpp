#pragma once

#include <functional>

#include "playerspectator.hpp"
#include "objectspectator.hpp"

class Spectator
{
public:
	virtual ~Spectator() {}
	
	virtual void forEachObjectSpectator(std::function<void(ObjectSpectator*)>) = 0;
	virtual bool forObjectSpectatorID(ObjectID id, std::function<void(ObjectSpectator*)>) = 0;
	
	virtual PlayerSpectator *getPlayerSpectator(int num) = 0;
	virtual int getPlayersCount() const = 0;
	
	virtual void setCallbackOnObjectCreate(std::function<void(ObjectSpectator*)>) = 0;
	virtual void setCallbackOnObjectRemove(std::function<void(ObjectSpectator*)>) = 0;
};
