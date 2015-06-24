#include "divisionhandlebase.hpp"

#include "unitspectatorimpl.hpp"

DivisionHandleBase::DivisionHandleBase(Division *d)
  : division(d)
{
	
}

DivisionHandleBase::~DivisionHandleBase()
{
	
}

Division *DivisionHandleBase::getDivision()
{
	return division;
}

// DivisionSpectator methods

void DivisionHandleBase::forEachUnitSpectator(std::function<void(UnitSpectator*)> f)
{
	for(Unit *u : *division)
	{
		UnitSpectatorImpl us(u);
		f(&us);
	}
}

bool DivisionHandleBase::forUnitSpectatorID(UnitID id, std::function<void(UnitSpectator*)> f)
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

int DivisionHandleBase::getUnitsCount() const
{
	return division->getNumber();
}

DivisionID DivisionHandleBase::getID() const
{
	return division->getID();
}

vec2 DivisionHandleBase::getPosition() const
{
	return division->getPosition();
}

vec2 DivisionHandleBase::getDirection() const
{
	return division->getDirection();
}

vec2 DivisionHandleBase::getDestination() const
{
	return division->getDestination();
}

double DivisionHandleBase::getDistance() const
{
	return division->getDistance();
}

int DivisionHandleBase::getWidth() const
{
	return division->getWidth();
}

DivisionMode DivisionHandleBase::getMode() const
{
	return division->getMode();
}

