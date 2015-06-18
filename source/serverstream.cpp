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
			conn->queue_write(int(storage->getObjectCount()));
			flush();
			storage->forObjectsConst([conn,flush](const Object *o)
			{
				conn->queue_write(ObjectID(o->getID()));
				conn->queue_write(ObjectType(o->getType()));
				conn->queue_write(double(o->getSize()));
				conn->queue_write(double(o->getInvMass()));
				conn->queue_write(vec2(o->getPos()));
				conn->queue_write(vec2(o->getVel()));
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
