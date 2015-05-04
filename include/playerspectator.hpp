#pragma once

#include <functional>

#include "divisionspectator.hpp"

class PlayerSpectator
{
public:
	virtual void forEachDivisionSpectator(std::function<void(DivisionSpectator*)> func) = 0;
	virtual bool forDivisionSpectatorID(DivisionID id, std::function<void(DivisionSpectator*)> func) = 0;
	virtual int getDivisionCount() const = 0;
};
