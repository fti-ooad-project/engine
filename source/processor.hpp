#pragma once

#include "storage.hpp"

class Processor
{
private:
	Storage *storage = nullptr;
	
public:
	Processor();
	virtual ~Processor();
	
	void setStorage(Storage *s);
	
	void attract();
	void move(double dt);
	void interact(double dt);
};
