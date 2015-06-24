#include "divisionhandleimpl.hpp"

#include "unitspectatorimpl.hpp"

DivisionHandleImpl::DivisionHandleImpl(Division *d)
  : DivisionHandleBase(d)
{
	
}

DivisionHandleImpl::~DivisionHandleImpl()
{
	
}

// DivisionHandle methods

void DivisionHandleImpl::setPosition(const vec2 &pos)
{
	getDivision()->setPosition(pos);
}

void DivisionHandleImpl::setDirection(const vec2 &dir)
{
	getDivision()->setDirection(dir);
	getDivision()->redistribute();
}

void DivisionHandleImpl::setDestination(const vec2 &dst)
{
	getDivision()->setDestination(dst);
	getDivision()->updatePositions();
}

void DivisionHandleImpl::setDistance(double dist)
{
	getDivision()->setDistance(dist);
	getDivision()->updatePositions();
}

void DivisionHandleImpl::setWidth(int width)
{
	getDivision()->setWidth(width);
	getDivision()->redistribute();
}

void DivisionHandleImpl::setMode(DivisionMode m)
{
	getDivision()->setMode(m);
}
