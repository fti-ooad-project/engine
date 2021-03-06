#pragma once

#include <list>
#include <functional>

#include "playerhandlebase.hpp"

#include "../storage.hpp"

#include "divisionhandleimpl.hpp"

class PlayerHandleImpl : public PlayerHandleBase
{
private:
	
public:
	PlayerHandleImpl(int _id, Storage *s);
	virtual ~PlayerHandleImpl();
	
	// PlayerHandle methods
	virtual void forEachDivisionHandle(std::function<void(DivisionHandle *dh)> func) override;
	virtual bool forDivisionHandleID(DivisionID id, std::function<void(DivisionHandle *dh)> func) override;
	virtual std::pair<DivisionID,DivisionID> splitDivision(DivisionID id, std::function<bool(UnitSpectator*)> ind) override;
	virtual DivisionID mergeDivisions(DivisionID one, DivisionID two) override;
	/* Unavailable in battle mode */
	virtual DivisionID purchaseDivision(DivisionID did, UnitType type, int unit_count) override;
	virtual bool removeDivision(DivisionID id) override;
};
