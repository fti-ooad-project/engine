#pragma once

#include <4u/la/vec.hpp>

#include "objectspectator.hpp"

typedef ObjectID UnitID;
typedef int UnitType;

class UnitSpectator : public ObjectSpectator
{
public:
	virtual UnitType getUnitType() const = 0;
	virtual vec2 getDirection() const = 0;
	virtual vec2 getDestination() const = 0;
};
