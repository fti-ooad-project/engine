#pragma once

#include "divisionhandlebase.hpp"

#include "../division.hpp"

#include "../tcp/connection.hpp"

class DivisionHandleClient : public DivisionHandleBase
{
private:
	TCPConnection *conn;
	
public:
	DivisionHandleClient(Division *d, TCPConnection *c);
	virtual ~DivisionHandleClient();
	
	// DivisionHandle methods
	
	virtual void setPosition(const vec2 &pos) override;
	virtual void setDirection(const vec2 &dir) override;
	virtual void setDestination(const vec2 &dst) override;
	virtual void setDistance(double dist) override;
	
	virtual void setWidth(int width) override;
	virtual void setMode(DivisionMode mode) override;
};
