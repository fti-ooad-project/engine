#include "spectatorimpl.hpp"

SpectatorImpl::SpectatorImpl(Storage *s, PlayerSpectator **ps, int pc)
  : storage(s), players(ps), players_count(pc)
{
	
}

SpectatorImpl::~SpectatorImpl()
{
	
}

void SpectatorImpl::forEachObjectSpectator(std::function<void(ObjectSpectator*)> func)
{
	storage->forObjectsConst([func](const Object *o)
	{
		ObjectSpectatorImpl os(o);
		func(&os);
	});
}

bool SpectatorImpl::forObjectSpectatorID(ObjectID id, std::function<void(ObjectSpectator*)> func)
{
	bool done = false;
	storage->forObjectsConst([id,func,&done](const Object *o)
	{
		if(id == o->getID())
		{
			ObjectSpectatorImpl os(o);
			func(&os);
			done = true;
		}
	});
	return done;
}

PlayerSpectator *SpectatorImpl::getPlayerSpectator(int num)
{
	if(num < 0 || num >= players_count)
	{
		return nullptr;
	}
	return players[num];
}

int SpectatorImpl::getPlayersCount() const
{
	return players_count;
}

void SpectatorImpl::setCallbackOnObjectCreate(std::function<void(ObjectSpectator*)>)
{
	// TODO: Callback in storage
}

void SpectatorImpl::setCallbackOnObjectRemove(std::function<void(ObjectSpectator*)>)
{
	// TODO: Callback in storage
}
