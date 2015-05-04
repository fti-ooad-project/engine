#pragma once

#include <functional>
#include <list>
#include "tree.hpp"

#include "object.hpp"
#include "unit.hpp"
#include "division.hpp"

class Storage
{
private:
	Tree<Object*> tree;
	std::list<Object*> objects;
	std::list<Unit*> units;
	std::list<Division*> divisions;
	
public:
	Storage();
	~Storage();
	
	void addObject(Object *o);
	void removeObject(Object *o);
	
	void addUnit(Unit *u);
	void removeUnit(Unit *u);
	
	void addDivision(Division *d);
	void removeDivision(Division *d);
	
	// TODO: Use mutexes
	void forObjects(std::function<void(Object*)> func);
	void forObjectsConst(std::function<void(const Object*)> func) const;
	
	void forUnits(std::function<void(Unit*)> func);
	void forUnitsConst(std::function<void(const Unit*)> func) const;
	
	void forDivisions(std::function<void(Division*)> func);
	void forDivisionsConst(std::function<void(const Division*)> func) const;
	
	void forNearObjects(const Object *o, std::function<void(Object*)> func);
	// void forNearObjectsConst(const Object *o, std::function<void(const Object*)> func) const;
	
	void updateTreeObject(const TreeKey &old_key, const TreeKey &new_key, Object *o);
	void updateTree();
};
