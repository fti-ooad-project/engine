#include "storage.hpp"

Storage::Storage()
  : tree(TreeKey(nullvec2,64.0),4)
{
	
}

Storage::~Storage()
{
	
}

void Storage::addObject(Object *o)
{
	rmutex.lock();
	{
		objects.push_back(o);
		tree.insert(TreeKey(o->getPos(),o->getSize()),o);
	}
	rmutex.unlock();
}

void Storage::removeObject(Object *o)
{
	rmutex.lock();
	{
		objects.remove(o);
		tree.remove(TreeKey(o->getPos(),o->getSize()),o);
	}
	rmutex.unlock();
}

void Storage::addUnit(Unit *u)
{
	rmutex.lock();
	{
		units.push_back(u);
	}
	rmutex.unlock();
}

void Storage::removeUnit(Unit *u)
{
	rmutex.lock();
	{
		units.remove(u);
	}
	rmutex.unlock();
}

void Storage::addDivision(Division *d)
{
	rmutex.lock();
	{
		divisions.push_back(d);
	}
	rmutex.unlock();
}

void Storage::removeDivision(Division *d)
{
	rmutex.lock();
	{
		divisions.remove(d);
	}
	rmutex.unlock();
}

void Storage::forObjects(std::function<void(Object*)> func)
{
	rmutex.lock();
	{
		for(Object *o : objects)
		{
			func(o);
		}
	}
	rmutex.unlock();
}

void Storage::forObjectsConst(std::function<void(const Object*)> func) const
{
	rmutex.lock();
	{
		for(const Object *co : objects)
		{
			func(co);
		}
	}
	rmutex.unlock();
}

Object *Storage::getObject(unsigned id)
{
	Object *ptr = nullptr;
	rmutex.lock();
	{
		for(Object *o : objects)
		{
			if(o->getID() == id)
			{
				ptr = o;
			}
		}
	}
	rmutex.unlock();
	return ptr;
}

const Object *Storage::getObjectConst(unsigned id) const
{
	const Object *ptr = nullptr;
	rmutex.lock();
	{
		for(const Object *o : objects)
		{
			if(o->getID() == id)
			{
				ptr = o;
			}
		}
	}
	rmutex.unlock();
	return ptr;
}

int Storage::getObjectCount() const
{
	int count = 0;
	rmutex.lock();
	{
		count = objects.size();
	}
	rmutex.unlock();
	return count;
}

void Storage::forUnits(std::function<void(Unit*)> func)
{
	rmutex.lock();
	{
		for(Unit *u : units)
		{
			func(u);
		}
	}
	rmutex.unlock();
}

void Storage::forUnitsConst(std::function<void(const Unit*)> func) const
{
	rmutex.lock();
	{
		for(const Unit *cu : units)
		{
			func(cu);
		}
	}
	rmutex.unlock();
}

Unit *Storage::getUnit(unsigned id)
{
	Unit *ptr = nullptr;
	rmutex.lock();
	{
		for(Unit *u : units)
		{
			if(u->getID() == id)
			{
				ptr = u;
			}
		}
	}
	rmutex.unlock();
	return ptr;
}

const Unit *Storage::getUnitConst(unsigned id) const
{
	const Unit *ptr = nullptr;
	rmutex.lock();
	{
		for(const Unit *u : units)
		{
			if(u->getID() == id)
			{
				ptr = u;
			}
		}
	}
	rmutex.unlock();
	return ptr;
}

int Storage::getUnitCount() const
{
	int count = 0;
	rmutex.lock();
	{
		count = units.size();
	}
	rmutex.unlock();
	return count;
}

void Storage::forDivisions(std::function<void(Division*)> func)
{
	rmutex.lock();
	{
		for(Division *d : divisions)
		{
			func(d);
		}
	}
	rmutex.unlock();
}

void Storage::forDivisionsConst(std::function<void(const Division*)> func) const
{
	rmutex.lock();
	{
		for(const Division *cd : divisions)
		{
			func(cd);
		}
	}
	rmutex.unlock();
}

Division *Storage::getDivision(unsigned id)
{
	Division *ptr = nullptr;
	rmutex.lock();
	{
		for(Division *d : divisions)
		{
			if(d->getID() == id)
			{
				ptr = d;
			}
		}
	}
	rmutex.unlock();
	return ptr;
}

const Division *Storage::getDivisionConst(unsigned id) const
{
	const Division *ptr = nullptr;
	rmutex.lock();
	{
		for(const Division *d : divisions)
		{
			if(d->getID() == id)
			{
				ptr = d;
			}
		}
	}
	rmutex.unlock();
	return ptr;
}

int Storage::getDivisionCount() const
{
	int count = 0;
	rmutex.lock();
	{
		count = divisions.size();
	}
	rmutex.unlock();
	return count;
}

void Storage::updateTreeObject(const TreeKey &old_key, const TreeKey &new_key, Object *o)
{
	rmutex.lock();
	{
		tree.replace(old_key,new_key,o);
	}
	rmutex.unlock();
}

void Storage::forNearObjects(const Object *o, std::function<void(Object*)> func)
{
	rmutex.lock();
	{
		tree.for_nearest(TreeKey(o->getPos(),o->getSize()),[func](std::list<std::pair<TreeKey,Object*>> &lst)
		{
			for(auto pair : lst)
			{
				func(pair.second);
			}
		});
	}
	rmutex.unlock();
}

/*
void Storage::forNearObjectsConst(const Object *o, std::function<void(const Object*)> func) const
{
	
}
*/

void Storage::updateTree()
{
	rmutex.lock();
	{
		tree.update();
	}
	rmutex.unlock();
}
