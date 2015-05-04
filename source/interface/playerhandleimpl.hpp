#pragma once

#include <list>
#include <functional>

#include <engine/playerhandle.hpp>

#include "../storage.hpp"

#include "divisionhandleimpl.hpp"

class PlayerHandleImpl : public PlayerHandle
{
private:
	Storage *storage = nullptr;
	int money = 0;
	
public:
	PlayerHandleImpl(Storage *s);
	virtual ~PlayerHandleImpl();
	
	// PlayerHandle methods
	virtual int getMoneyAmount() const override;
	virtual void forEachDivisionHandle(std::function<void(DivisionHandle *dh)> func) override;
	virtual bool forDivisionHandleID(DivisionID id, std::function<void(DivisionHandle *dh)> func) override;
	virtual std::pair<DivisionID,DivisionID> splitDivision(DivisionID id, std::function<bool(UnitSpectator*)> ind) override;
	virtual DivisionID mergeDivisions(DivisionID one, DivisionID two) override;
	/* Unavailable in battle mode */
	virtual DivisionID purchaseDivision(UnitType unit_type, int unit_count) override;
	virtual bool removeDivision(DivisionID id) override;
	
	// PlayerSpectator methods
	virtual void forEachDivisionSpectator(std::function<void(DivisionSpectator*)> func) override;
	virtual bool forDivisionSpectatorID(DivisionID id, std::function<void(DivisionSpectator*)> func) override;
	virtual int getDivisionCount() const override;
};
