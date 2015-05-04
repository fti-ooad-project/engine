#pragma once

#include <engine/divisionhandle.hpp>
#include <engine/divisionspectator.hpp>

#include "../division.hpp"

class DivisionHandleImpl : public DivisionHandle
{
private:
	Division *division;
	
public:
	DivisionHandleImpl(Division *d);
	virtual ~DivisionHandleImpl();
	
	// DivisionHandle methods
	
	virtual void setPosition(const vec2 &pos) override;
	virtual void setDirection(const vec2 &dir) override;
	virtual void setDestination(const vec2 &dst) override;
	
	virtual void setWidth(int width) override;
	virtual void setMode(DivisionMode mode) override;
	
	// DivisionSpectator methods
	
	virtual void forEachUnitSpectator(std::function<void(UnitSpectator*)> f) override;
	virtual bool forUnitSpectatorID(UnitID id, std::function<void(UnitSpectator*)> f) override;
	virtual int getUnitsCount() const override;
	
	virtual DivisionID getID() const override;
	
	virtual vec2 getPosition() const override;
	virtual vec2 getDirection() const override;
	virtual vec2 getDestination() const override;
	
	virtual int getWidth() const override;
	virtual DivisionMode getMode() const override;
};
