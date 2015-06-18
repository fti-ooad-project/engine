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
			int size = 0;
			conn->queue_read(size);
			flush();
			for(int i = 0; i < size; ++i)
			{
				ObjectID id;
				ObjectType type;
				double size;
				double inv_mass;
				vec2 pos;
				vec2 vel;
				conn->queue_read(id);
				conn->queue_read(type);
				conn->queue_read(size);
				conn->queue_read(inv_mass);
				conn->queue_read(pos);
				conn->queue_read(vel);
				flush();
				Object *o = storage->getObject(id);
				if(o == nullptr)
				{
					o = new Object(id,type);
					storage->addObject(o);
				}
				o->setSize(size);
				o->setInvMass(inv_mass);
				o->setPos(pos);
				o->setVel(vel);
			}
		}
		catch(std::exception)
		{
			return;
		}
	}
}
