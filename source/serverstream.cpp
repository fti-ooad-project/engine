#include "serverstream.hpp"

#include <thread>
#include <chrono>

#include <stdio.h>

ServerStream::ServerStream(Session *s, Storage *st)
  : session(s), storage(st)
{
	
}

ServerStream::~ServerStream()
{
	
}

void ServerStream::operator()(TCPConnection *conn)
{
	auto flush = [this,conn]()
	{
		while(conn->write_size() && session->getState() == SessionState::ENABLE)
		{
			conn->perform_write();
		}
	};
	
	while(session->getState() == SessionState::ENABLE)
	{
		printf("data was sent to %d\n",conn->get_fd());
		try
		{
			/*
			int unit_count = storage->getUnitCount();
			conn->queue_write(unit_count);
			flush();
			storage->forUnitsConst([conn,flush](const Unit *u)
			{
				u->getDir();
				u->getDst();
			});
			*/
			
			int object_count = storage->getObjectCount();
			conn->queue_write(object_count);
			flush();
			storage->forObjectsConst([conn,flush](const Object *o)
			{
				ObjectID id = o->getID();
				ObjectType type = o->getType();
				double size = o->getSize();
				double inv_mass = o->getInvMass();
				vec2 pos = o->getPos();
				vec2 vel = o->getVel();
				conn->queue_write(id);
				conn->queue_write(type);
				conn->queue_write(size);
				conn->queue_write(inv_mass);
				conn->queue_write(pos);
				conn->queue_write(vel);
				flush();
			});
		}
		catch(std::exception)
		{
			return;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
