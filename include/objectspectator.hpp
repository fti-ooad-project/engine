#pragma once

#include <4u/la/vec.hpp>

typedef unsigned int ObjectID;
typedef int ObjectType;

class ObjectSpectator
{
public:
	virtual ObjectID getID() const = 0;
	virtual vec2 getPosition() const = 0;
	virtual double getSize() const = 0;
	virtual ObjectType getObjectType() const = 0;
};
