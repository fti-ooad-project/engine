#include "object.hpp"

static unsigned int id_counter = 0;

Object::Object(unsigned int t)
  : id(++id_counter), type(t)
{
	
}

Object::Object(unsigned int _id, unsigned int t)
  : id(_id), type(t)
{
	++id_counter;
}

Object::~Object()
{
	
}

unsigned int Object::getID() const
{
	return id;
}

unsigned int Object::getType() const
{
	return type;
}

double Object::getInvMass() const
{
	return inv_mass;
}

void Object::setInvMass(double im)
{
	inv_mass = im;
}

vec2 Object::getPos() const
{
    return pos;
}

void Object::setPos(const vec2 &p)
{
    pos = p;
}

vec2 Object::getVel() const
{
    return vel;
}

void Object::setVel(const vec2 &v)
{
    vel = v;
}

double Object::getSize() const
{
	return size;
}

void Object::setSize(double s)
{
	size = s;
}
