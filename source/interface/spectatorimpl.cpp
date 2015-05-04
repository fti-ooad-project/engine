#include "spectatorimpl.hpp"

SpectatorImpl::SpectatorImpl(Storage *s)
  : storage(s)
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
	// TODO: Access to PlayerHandle list
	return nullptr;
}

int SpectatorImpl::getPlayersCount() const
{
	// TODO: Access to PlayerHandle list
	return 1;
}

void SpectatorImpl::setCallbackOnObjectCreate(std::function<void(ObjectSpectator*)>)
{
	// TODO: Callback in storage
}

void SpectatorImpl::setCallbackOnObjectRemove(std::function<void(ObjectSpectator*)>)
{
	// TODO: Callback in storage
}
