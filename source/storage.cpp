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
	objects.push_back(o);
	tree.insert(TreeKey(o->getPos(),o->getSize()),o);
}

void Storage::removeObject(Object *o)
{
	objects.remove(o);
	tree.remove(TreeKey(o->getPos(),o->getSize()),o);
}

void Storage::addUnit(Unit *u)
{
	units.push_back(u);
}

void Storage::removeUnit(Unit *u)
{
	units.remove(u);
}

void Storage::addDivision(Division *d)
{
	divisions.push_back(d);
}

void Storage::removeDivision(Division *d)
{
	divisions.remove(d);
}

void Storage::forObjects(std::function<void(Object*)> func)
{
	for(Object *o : objects)
	{
		func(o);
	}
}

void Storage::forObjectsConst(std::function<void(const Object*)> func) const
{
	for(const Object *co : objects)
	{
		func(co);
	}
}

void Storage::forUnits(std::function<void(Unit*)> func)
{
	for(Unit *u : units)
	{
		func(u);
	}
}

void Storage::forUnitsConst(std::function<void(const Unit*)> func) const
{
	for(const Unit *cu : units)
	{
		func(cu);
	}
}

void Storage::forDivisions(std::function<void(Division*)> func)
{
	for(Division *d : divisions)
	{
		func(d);
	}
}

void Storage::forDivisionsConst(std::function<void(const Division*)> func) const
{
	for(const Division *cd : divisions)
	{
		func(cd);
	}
}

void Storage::updateTreeObject(const TreeKey &old_key, const TreeKey &new_key, Object *o)
{
	tree.replace(old_key,new_key,o);
}

void Storage::forNearObjects(const Object *o, std::function<void(Object*)> func)
{
	tree.for_nearest(TreeKey(o->getPos(),o->getSize()),[func](std::list<std::pair<TreeKey,Object*>> &lst)
	{
		for(auto pair : lst)
		{
			func(pair.second);
		}
	});
}

/*
void Storage::forNearObjectsConst(const Object *o, std::function<void(const Object*)> func) const
{
	
}
*/

void Storage::updateTree()
{
	tree.update();
}
