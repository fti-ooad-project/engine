#include "objectspectatorimpl.hpp"

ObjectSpectatorImpl::ObjectSpectatorImpl(const Object *o)
  : object(o)
{
	
}

ObjectSpectatorImpl::~ObjectSpectatorImpl()
{
	
}

ObjectID ObjectSpectatorImpl::getID() const
{
	return object->getID();
}
vec2 ObjectSpectatorImpl::getPosition() const
{
	return object->getPos();
}
double ObjectSpectatorImpl::getSize() const
{
	return object->getSize();
}
ObjectType ObjectSpectatorImpl::getObjectType() const
{
	return object->getType();
}
