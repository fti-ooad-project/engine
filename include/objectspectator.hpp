#pragma once

#include <4u/la/vec.hpp>

typedef unsigned int ObjectID;

typedef unsigned int ObjectType;
static const ObjectType
	OBJECT_STONE = 0x0001;

class ObjectSpectator
{
public:
	virtual ObjectID getID() const = 0;
	virtual vec2 getPosition() const = 0;
	virtual double getSize() const = 0;
	virtual ObjectType getObjectType() const = 0;
};
