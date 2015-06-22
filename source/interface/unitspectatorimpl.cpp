#include "unitspectatorimpl.hpp"

UnitSpectatorImpl::UnitSpectatorImpl(const Unit *u)
  : unit(u)
{
	
}

UnitSpectatorImpl::~UnitSpectatorImpl()
{
	
}

UnitType UnitSpectatorImpl::getUnitType() const
{
	return 1;
}

vec2 UnitSpectatorImpl::getDirection() const
{
	return unit->getDir();
}

vec2 UnitSpectatorImpl::getDestination() const
{
	return unit->getDst();
}

// ObjectSpectator methods
ObjectID UnitSpectatorImpl::getID() const
{
	return unit->getID();
}

vec2 UnitSpectatorImpl::getPosition() const
{
	return unit->getPos();
}

vec2 UnitSpectatorImpl::getVelocity() const
{
	return unit->getVel();
}

double UnitSpectatorImpl::getSize() const
{
	return unit->getSize();
}

ObjectType UnitSpectatorImpl::getObjectType() const
{
	return 1;
}
