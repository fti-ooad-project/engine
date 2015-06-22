#pragma once

#include <functional>

#include <4u/la/vec.hpp>

#include "unitspectator.hpp"

typedef unsigned int DivisionID;
typedef int DivisionMode;

static const DivisionMode
	MODE_HOLD = 0,
	MODE_FREE = 1;

class DivisionSpectator
{
public:
	virtual ~DivisionSpectator() {}
	
	virtual void forEachUnitSpectator(std::function<void(UnitSpectator*)>) = 0;
	virtual bool forUnitSpectatorID(UnitID id, std::function<void(UnitSpectator*)>) = 0;
	virtual int getUnitsCount() const = 0;
	
	virtual DivisionID getID() const = 0;
	
	virtual vec2 getPosition() const = 0;
	virtual vec2 getDirection() const = 0;
	virtual vec2 getDestination() const = 0;
	virtual double getDistance() const = 0;
	
	virtual int getWidth() const = 0;
	virtual DivisionMode getMode() const = 0;
};
