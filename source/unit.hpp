#pragma once

#include "object.hpp"

#include<4u/la/vec.hpp>

class Unit : public Object
{
private:
	vec2 dir = vec2(0,1);
	vec2 dst = nullvec2;
	vec2 intension = nullvec2;
	
	double spd = 2.4;
	bool alive = true;

public:
	Unit(unsigned int t = 0x0101);
	Unit(unsigned int _id, unsigned int t);
	virtual ~Unit();
	
	vec2 getDir() const;
	void setDir(const vec2 &d);
	
	vec2 getDst() const;
	void setDst(const vec2 &d);
	
	double getSpd() const;
	void setSpd(double s);
	
	vec2 getIntension() const;
	void setIntension(const vec2 &v);
};
