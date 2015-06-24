#include "playerhandlebase.hpp"

#include <cmath>

PlayerHandleBase::PlayerHandleBase(int _id, Storage *s)
  : id(_id), storage(s)
{
	
}

PlayerHandleBase::~PlayerHandleBase()
{
	
}

Storage *PlayerHandleBase::getStorage()
{
	return storage;
}

int PlayerHandleBase::getID() const
{
	return id;
}

// PlayerHandle methods
int PlayerHandleBase::getMoneyAmount() const
{
	return money;
}

DivisionID PlayerHandleBase::purchaseDivision(UnitType type, int unit_count)
{
	return purchaseDivision(-1,type,unit_count);
}

// PlayerSpectator methods
void PlayerHandleBase::forEachDivisionSpectator(std::function<void(DivisionSpectator*)> func)
{
	storage->forDivisions([func](Division *d)
	{
		DivisionHandleImpl dh(d);
		func(static_cast<DivisionSpectator*>(&dh));
	});
}

bool PlayerHandleBase::forDivisionSpectatorID(DivisionID id, std::function<void(DivisionSpectator*)> func)
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

int PlayerHandleBase::getDivisionCount() const
{
	int counter = 0;
	storage->forDivisionsConst([&counter](const Division*)
	{
		++counter;
	});
	return counter;
}

