#pragma once

#include <engine/objectspectator.hpp>

#include "../object.hpp"

class ObjectSpectatorImpl : public ObjectSpectator
{
private:
	const Object *object = nullptr;
public:
	ObjectSpectatorImpl(const Object *o);
	virtual ~ObjectSpectatorImpl();
	
	virtual ObjectID getID() const override;
	virtual vec2 getPosition() const override;
	virtual vec2 getVelocity() const override;
	virtual double getSize() const override;
	virtual ObjectType getObjectType() const override;
};
