#include "divisionhandleimpl.hpp"

#include "unitspectatorimpl.hpp"

DivisionHandleImpl::DivisionHandleImpl(Division *d)
  : division(d)
{
	
}

DivisionHandleImpl::~DivisionHandleImpl()
{
	
}

// DivisionHandle methods

void DivisionHandleImpl::setPosition(const vec2 &pos)
{
	division->setPosition(pos);
}

void DivisionHandleImpl::setDirection(const vec2 &dir)
{
	division->setDirection(dir);
	division->redistribute();
}

void DivisionHandleImpl::setDestination(const vec2 &dst)
{
	division->setDestination(dst);
	division->updatePositions();
}

void DivisionHandleImpl::setDistance(double dist)
{
	division->setDistance(dist);
	division->updatePositions();
}

void DivisionHandleImpl::setWidth(int width)
{
	division->setWidth(width);
	division->redistribute();
}

void DivisionHandleImpl::setMode(DivisionMode m)
{
	division->setMode(m);
}


// DivisionSpectator methods

void DivisionHandleImpl::forEachUnitSpectator(std::function<void(UnitSpectator*)> f)
{
	for(Unit *u : *division)
	{
		UnitSpectatorImpl us(u);
		f(&us);
	}
}

bool DivisionHandleImpl::forUnitSpectatorID(UnitID id, std::function<void(UnitSpectator*)> f)
{
	bool done = false;
	for(Unit *u : *division)
	{
		if(u->getID() == id)
		{
			UnitSpectatorImpl us(u);
			f(&us);
			done = true;
			break;
		}
	}
	return done;
}

int DivisionHandleImpl::getUnitsCount() const
{
	return division->getNumber();
}

DivisionID DivisionHandleImpl::getID() const
{
	return division->getID();
}

vec2 DivisionHandleImpl::getPosition() const
{
	return division->getPosition();
}

vec2 DivisionHandleImpl::getDirection() const
{
	return division->getDirection();
}

vec2 DivisionHandleImpl::getDestination() const
{
	return division->getDestination();
}

double DivisionHandleImpl::getDistance() const
{
	return division->getDistance();
}

int DivisionHandleImpl::getWidth() const
{
	return division->getWidth();
}

DivisionMode DivisionHandleImpl::getMode() const
{
	return division->getMode();
}
