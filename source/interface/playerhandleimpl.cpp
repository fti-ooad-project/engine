#include "playerhandleimpl.hpp"

PlayerHandleImpl::PlayerHandleImpl(Storage *s)
  : storage(s)
{
	
}

PlayerHandleImpl::~PlayerHandleImpl()
{
	
}

// PlayerHandle methods
int PlayerHandleImpl::getMoneyAmount() const
{
	return money;
}
void PlayerHandleImpl::forEachDivisionHandle(std::function<void(DivisionHandle *dh)> func)
{
	storage->forDivisions([func](Division *d)
	{
		DivisionHandleImpl dh(d);
		func(&dh);
	});
}
bool PlayerHandleImpl::forDivisionHandleID(DivisionID id, std::function<void(DivisionHandle *dh)> func)
{
	bool done = false;
	storage->forDivisions([id,func,&done](Division *d)
	{
		if(id == d->getID())
		{
			DivisionHandleImpl dh(d);
			func(&dh);
			done = true;
		}
	});
	return done;
}
std::pair<DivisionID,DivisionID> PlayerHandleImpl::splitDivision(DivisionID id, std::function<bool(UnitSpectator*)> ind)
{
	// ???
	return std::pair<DivisionID,DivisionID>(0,0);
}
DivisionID PlayerHandleImpl::mergeDivisions(DivisionID one, DivisionID two)
{
	// ???
	return 0;
}
DivisionID PlayerHandleImpl::purchaseDivision(UnitType, int unit_count)
{
	// TODO: move this to storage methods
	Division *d = new Division;
	for(int i = 0; i < unit_count; ++i)
	{
		d->addUnit(new Unit);
	}
	storage->addDivision(d);
	return d->getID();
}
bool PlayerHandleImpl::removeDivision(DivisionID id)
{
	// TODO: move this to storage methods
	Division *victim = nullptr;
	storage->forDivisions([id,&victim](Division *d)
	{
		if(id == d->getID())
		{
			
		}
	});
	if(victim == nullptr)
	{
		return false;
	}
	storage->removeDivision(victim);
	for(Unit *u : *victim)
	{
		delete u;
	}
	delete victim;
	return true;
}

// PlayerSpectator methods
void PlayerHandleImpl::forEachDivisionSpectator(std::function<void(DivisionSpectator*)> func)
{
	storage->forDivisions([func](Division *d)
	{
		DivisionHandleImpl dh(d);
		func(static_cast<DivisionSpectator*>(&dh));
	});
}

bool PlayerHandleImpl::forDivisionSpectatorID(DivisionID id, std::function<void(DivisionSpectator*)> func)
{
	bool done = false;
	storage->forDivisions([id,func,&done](Division *d)
	{
		if(id == d->getID())
		{
			DivisionHandleImpl dh(d);
			func(static_cast<DivisionSpectator*>(&dh));
			done = true;
		}
	});
	return done;
}

int PlayerHandleImpl::getDivisionCount() const
{
	int counter = 0;
	storage->forDivisionsConst([&counter](const Division*)
	{
		++counter;
	});
	return counter;
}