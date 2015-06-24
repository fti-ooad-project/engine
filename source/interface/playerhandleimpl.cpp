#include "playerhandleimpl.hpp"

#include <cmath>

PlayerHandleImpl::PlayerHandleImpl(int _id, Storage *s)
  : PlayerHandleBase(_id,s)
{
	
}

PlayerHandleImpl::~PlayerHandleImpl()
{
	
}

// PlayerHandle methods
void PlayerHandleImpl::forEachDivisionHandle(std::function<void(DivisionHandle *dh)> func)
{
	Storage *storage = getStorage();
	storage->forDivisions([func](Division *d)
	{
		DivisionHandleImpl dh(d);
		func(&dh);
	});
}

bool PlayerHandleImpl::forDivisionHandleID(DivisionID id, std::function<void(DivisionHandle *dh)> func)
{
	Storage *storage = getStorage();
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
DivisionID PlayerHandleImpl::purchaseDivision(DivisionID did, UnitType type, int unit_count)
{
	Storage *storage = getStorage();
	// TODO: move this to storage methods
	Division *d = nullptr;
	if(did > 0)
		d = new Division(did);
	else
		d = new Division;
	int width = int(sqrt(unit_count)) + 1;
	for(int i = 0; i < unit_count; ++i)
	{
		Unit *u = new Unit(type);
		u->setPos(0.6*(vec2(i/width,i%width) - 0.5*width*vec2(1,1)));
		d->addUnit(u);
		storage->addUnit(u);
		storage->addObject(u);
	}
	d->redistribute();
	d->updatePositions();
	storage->addDivision(d);
	return d->getID();
}
bool PlayerHandleImpl::removeDivision(DivisionID id)
{
	Storage *storage = getStorage();
	// TODO: move this to storage methods
	Division *victim = nullptr;
	storage->forDivisions([id,&victim](Division *d)
	{
		if(id == d->getID())
		{
			victim = d;
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
