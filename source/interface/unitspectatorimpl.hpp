#pragma once

#include <engine/unitspectator.hpp>
#include "../unit.hpp"

class UnitSpectatorImpl : public UnitSpectator
{
private:
	const Unit *unit = nullptr;
public:
	UnitSpectatorImpl(const Unit *u);
	virtual ~UnitSpectatorImpl();
	
	virtual UnitType getUnitType() const override;
	virtual vec2 getDirection() const override;
	virtual vec2 getDestination() const override;
	
	// ObjectSpectator methods
	virtual ObjectID getID() const override;
	virtual vec2 getPosition() const override;
	virtual double getSize() const override;
	virtual ObjectType getObjectType() const override;
};
