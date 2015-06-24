#pragma once

#include <list>
#include <functional>

#include <engine/playerhandle.hpp>

#include "../storage.hpp"

#include "divisionhandleimpl.hpp"

class PlayerHandleBase : public PlayerHandle
{
private:
	Storage *storage = nullptr;
	int money = 0;
	int id = 0;
	
public:
	PlayerHandleBase(int _id, Storage *s);
	virtual ~PlayerHandleBase();
	
	Storage *getStorage();
	
	// PlayerHandle methods
	virtual int getID() const override;
	virtual int getMoneyAmount() const override;
	virtual DivisionID purchaseDivision(UnitType type, int unit_count) override;
	virtual DivisionID purchaseDivision(DivisionID id, UnitType unit_type, int unit_count) = 0;
	
	// PlayerSpectator methods
	virtual void forEachDivisionSpectator(std::function<void(DivisionSpectator*)> func) override;
	virtual bool forDivisionSpectatorID(DivisionID id, std::function<void(DivisionSpectator*)> func) override;
	virtual int getDivisionCount() const override;
};
