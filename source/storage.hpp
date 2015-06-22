#pragma once

#include <functional>
#include <map>
#include <mutex>

#include "tree.hpp"

#include "object.hpp"
#include "unit.hpp"
#include "division.hpp"

class Storage
{
private:
	class recursive_mutex_placeholder
	{
	public:
		void lock(){}
		void unlock(){}
	};
	
	Tree<Object*> tree;
	std::list<Object*> objects;
	std::list<Unit*> units;
	std::list<Division*> divisions;
	mutable /*std::*/recursive_mutex_placeholder rmutex;
	
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
	Object *getObject(unsigned id);
	const Object *getObjectConst(unsigned id) const;
	int getObjectCount() const;
	
	void forUnits(std::function<void(Unit*)> func);
	void forUnitsConst(std::function<void(const Unit*)> func) const;
	Unit *getUnit(unsigned id);
	const Unit *getUnitConst(unsigned id) const;
	int getUnitCount() const;
	
	void forDivisions(std::function<void(Division*)> func);
	void forDivisionsConst(std::function<void(const Division*)> func) const;
	Division *getDivision(unsigned id);
	const Division *getDivisionConst(unsigned id) const;
	int getDivisionCount() const;
	
	void forNearObjects(const Object *o, std::function<void(Object*)> func);
	// void forNearObjectsConst(const Object *o, std::function<void(const Object*)> func) const;
	
	void updateTreeObject(const TreeKey &old_key, const TreeKey &new_key, Object *o);
	void updateTree();
};
