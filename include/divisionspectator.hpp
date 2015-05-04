#pragma once

#include <functional>

#include <4u/la/vec.hpp>

#include "unitspectator.hpp"

typedef unsigned int DivisionID;

enum DivisionMode
{
	HOLD,
	FREE
};

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
	
	virtual int getWidth() const = 0;
	virtual DivisionMode getMode() const = 0;
};
