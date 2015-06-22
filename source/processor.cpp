#include "processor.hpp"

#include <4u/la/vec.hpp>
#include <4u/la/mat.hpp>

#define USE_TREE

static const double 
  DELTA = 1e-1,
  DELTA2 = 1e-2,
	RDELTA = 1e-4;

Processor::Processor()
{
	
}

Processor::~Processor()
{
	
}

void Processor::setStorage(Storage *s)
{
	storage = s;
}

void Processor::attract()
{
	storage->forUnits([](Unit *u)
	{
		vec2 dist = u->getDst() - u->getPos();
		double len2 = dist*dist;
		if(len2 > DELTA2)
		{
			double len = sqrt(len2);
			vec2 dir = dist/len;
			u->setDir(dir);
			vec2 vel = dir*u->getSpd();
			
			double msd = 0.5;
			if(len < msd)
			{
				vel *= len/msd;
			}
			u->setVel(vel);
		}
		else
		{
			u->setVel(nullvec2);
		}
	});
}

void Processor::move(double dt)
{
	// tree._print();
	storage->forObjects([dt,this](Object *o)
	{
		vec2 pos = o->getPos() + dt*o->getVel();
#ifdef USE_TREE
		storage->updateTreeObject(
		  TreeKey(o->getPos(),o->getSize()),
		  TreeKey(pos,o->getSize()),
		  o
		);
#endif
		o->setPos(pos);
	});
	storage->forDivisions([dt](Division *d)
	{
		d->movePositions(dt);
		d->updatePositions();
	});
}

void Processor::interact()
{
	for(int i = 0; i < 0x1; ++i)
	{
		storage->forObjects([this](Object *o0)
		{
#ifdef USE_TREE
			storage->forNearObjects(o0,[this,o0](Object *o1)
#else
			storage->forObjects([this,o0](Object *o1)
#endif
			{
				if(o0 < o1)
				{
					vec2 dist = o0->getPos() - o1->getPos();
					double mlen = o0->getSize() + o1->getSize();
					if(dist*dist < mlen*mlen)
					{
						if(dist*dist > 1e-8)
						{
							double len = length(dist);
							double dev = (mlen - len)/(o0->getInvMass() + o1->getInvMass());
							vec2 dir = dist/len;
							double d0 = dev*o0->getInvMass(), d1 = dev*o1->getInvMass();
							o0->setPos(o0->getPos() + dir*d0);
							o1->setPos(o1->getPos() - dir*d1);
						}
					}
				}
			});
		});
#ifdef USE_TREE
		storage->updateTree();
#endif
	}
}
