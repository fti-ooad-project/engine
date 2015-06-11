#pragma once

#include <4u/la/vec.hpp>

#include "divisionspectator.hpp"

class DivisionHandle : public DivisionSpectator
{
public:
	virtual ~DivisionHandle() {}
	
	virtual void setPosition(const vec2 &pos) = 0;
	virtual void setDirection(const vec2 &dir) = 0;
	virtual void setDestination(const vec2 &dst) = 0;
	virtual void setDistance(double dist) = 0;
	
	virtual void setMode(DivisionMode mode) = 0;
	
	virtual void setWidth(int width) = 0;
};
