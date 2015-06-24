#pragma once

#include <list>
#include <functional>

#include "playerhandlebase.hpp"

#include "../storage.hpp"

#include "divisionhandleimpl.hpp"

#include "../tcp/connection.hpp"

class PlayerHandleClient : public PlayerHandleBase
{
private:
	TCPConnection *conn = nullptr;
	
public:
	PlayerHandleClient(int _id, Storage *s, TCPConnection *c);
	virtual ~PlayerHandleClient();
	
	// PlayerHandle methods
	virtual void forEachDivisionHandle(std::function<void(DivisionHandle *dh)> func) override;
	virtual bool forDivisionHandleID(DivisionID id, std::function<void(DivisionHandle *dh)> func) override;
	virtual std::pair<DivisionID,DivisionID> splitDivision(DivisionID id, std::function<bool(UnitSpectator*)> ind) override;
	virtual DivisionID mergeDivisions(DivisionID one, DivisionID two) override;
	/* Unavailable in battle mode */
	virtual DivisionID purchaseDivision(DivisionID id, UnitType unit_type, int unit_count) override;
	virtual bool removeDivision(DivisionID id) override;
};
