#pragma once

#include <engine/divisionhandle.hpp>
#include <engine/divisionspectator.hpp>

#include "../division.hpp"

class DivisionHandleBase : public DivisionHandle
{
private:
	Division *division;
	
public:
	DivisionHandleBase(Division *d);
	virtual ~DivisionHandleBase();
	
	Division *getDivision();
	
	// DivisionSpectator methods
	
	virtual void forEachUnitSpectator(std::function<void(UnitSpectator*)> f) override;
	virtual bool forUnitSpectatorID(UnitID id, std::function<void(UnitSpectator*)> f) override;
	virtual int getUnitsCount() const override;
	
	virtual DivisionID getID() const override;
	
	virtual vec2 getPosition() const override;
	virtual vec2 getDirection() const override;
	virtual vec2 getDestination() const override;
	virtual double getDistance() const override;
	
	virtual int getWidth() const override;
	virtual DivisionMode getMode() const override;
};
