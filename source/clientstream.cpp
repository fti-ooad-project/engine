#include "clientstream.hpp"

#include <thread>
#include <chrono>

#include <stdio.h>

ClientStream::ClientStream(Session *s, Storage *st)
  : session(s), storage(st)
{
	
}

ClientStream::~ClientStream()
{
	
}

void ClientStream::operator()(TCPConnection *conn)
{
	if(conn == nullptr)
	{
		return;
	}
	
	auto flush = [this,conn]()
	{
		while(conn->read_size() && session->getState() == SessionState::ENABLE)
		{
			conn->perform_read();
		}
	};

	while(session->getState() == SessionState::ENABLE)
	{
		printf("data was received from %d\n",conn->get_fd());
		try
		{
			while(true)
			{
				DivisionID did;
				vec2 dpos;
				vec2 ddir;
				double dist;
				int width;
				conn->queue_read(did);
				flush();
				if(did == 0)
					break;
				conn->queue_read(dpos);
				conn->queue_read(ddir);
				conn->queue_read(dist);
				conn->queue_read(width);
				flush();
				Division *d = storage->getDivision(did);
				if(d == nullptr)
				{
					d = new Division(did);
					storage->addDivision(d);
				}
				d->setPosition(dpos);
				d->setDirection(ddir);
				d->setDistance(dist);
				d->setWidth(width);
				while(true)
				{
					UnitID id;
					UnitType type;
					vec2 dir;
					vec2 dst;
					conn->queue_read(id);
					flush();
					if(id == 0)
						break;
					conn->queue_read(type);
					flush();
					Unit *u = storage->getUnit(id);
					if(u == nullptr)
					{
						u = new Unit(id,type);
						storage->addUnit(u);
						storage->addObject(u);
						d->addUnit(u);
					}
					conn->queue_read(dir);
					conn->queue_read(dst);
					flush();
					u->setDir(dir);
					u->setDst(dst);
				}
			}
			
			while(true)
			{
				ObjectID id;
				ObjectType type;
				double size;
				double inv_mass;
				vec2 pos;
				vec2 vel;
				conn->queue_read(id);
				flush();
				if(id == 0)
					break;
				conn->queue_read(type);
				flush();
				Object *o = storage->getObject(id);
				if(o == nullptr)
				{
					o = new Object(id,type);
					storage->addObject(o);
				}
				conn->queue_read(size);
				conn->queue_read(inv_mass);
				conn->queue_read(pos);
				conn->queue_read(vel);
				flush();
				o->setSize(size);
				o->setInvMass(inv_mass);
				o->setPos(pos);
				o->setVel(vel);
				o->setVelBuf(vel);
			}
		}
		catch(std::exception)
		{
			return;
		}
	}
}
