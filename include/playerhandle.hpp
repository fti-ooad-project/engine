#pragma once

#include <functional>

#include "playerspectator.hpp"
#include "divisionhandle.hpp"

class PlayerHandle : public PlayerSpectator
{
public:
	virtual ~PlayerHandle() {}
	
	virtual int getID() const = 0;
	
	/* Money management */
	virtual int getMoneyAmount() const = 0;
	
	/* Division management */
	virtual void forEachDivisionHandle(std::function<void(DivisionHandle *dh)> func) = 0;
	virtual bool forDivisionHandleID(DivisionID id, std::function<void(DivisionHandle *dh)> func) = 0;
	virtual std::pair<DivisionID,DivisionID> splitDivision(DivisionID id, std::function<bool(UnitSpectator*)> ind) = 0;
	virtual DivisionID mergeDivisions(DivisionID one, DivisionID two) = 0;
	/* Unavailable in battle mode */
	virtual DivisionID purchaseDivision(UnitType unit_type, int unit_count) = 0;
	virtual DivisionID purchaseDivision(DivisionID id, UnitType unit_type, int unit_count) = 0;
	virtual bool removeDivision(DivisionID id) = 0;
};
