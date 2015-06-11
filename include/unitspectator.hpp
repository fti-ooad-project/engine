#pragma once

#include <4u/la/vec.hpp>

#include "objectspectator.hpp"

typedef ObjectID UnitID;

typedef ObjectType UnitType;
static const UnitType
  UNIT_SWORDSMAN = 0x0101,
	UNIT_ARCHER    = 0x0102;

class UnitSpectator : public ObjectSpectator
{
public:
	virtual UnitType getUnitType() const = 0;
	virtual vec2 getDirection() const = 0;
	virtual vec2 getDestination() const = 0;
};
