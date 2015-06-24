#pragma once

#include <4u/la/vec.hpp>

class Object
{
private:
	double inv_mass = 1.0/80.0;
	vec2 old_pos = nullvec2;
	vec2 pos = nullvec2;
	vec2 vel = nullvec2;
	vec2 velbuf = nullvec2;
	
	double size = 0.25;
	unsigned int id;
	unsigned int type;
	
public:
	Object(unsigned int t = 0x0001);
	Object(unsigned int _id, unsigned int t);
	virtual ~Object();
	
	unsigned int getID() const;
	
	unsigned int getType() const;
	
	double getInvMass() const;
	void setInvMass(double im);
	
	vec2 getOldPos() const;
	vec2 getPos() const;
	void setPos(const vec2 &p);
	
	vec2 getVel() const;
	void setVel(const vec2 &v);
	vec2 getVelBuf() const;
	void setVelBuf(const vec2 &v);
	
	double getSize() const;
	void setSize(double s);
	
	void updatePos();
};
