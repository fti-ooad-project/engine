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
	auto wflush = [this,conn]()
	{
		while(conn->write_size() && session->getState() == SessionState::ENABLE)
		{
			conn->perform_write();
		}
	};
	
	auto rflush = [this,conn]()
	{
		while(conn->read_size() && session->getState() == SessionState::ENABLE)
		{
			conn->perform_read();
		}
	};
	
	int command;
	while(session->getState() == SessionState::ENABLE)
	{
		try
		{
			if(conn->read_size() == 0)
			{
				conn->queue_read(command);
			}
			conn->perform_read();
			if(conn->read_size() == 0)
			{
				DivisionID did = 0;
				switch(command)
				{
				case 0x12: // purchaseDivision(DivisionID,UnitType,int)
				{
					UnitType ut = 0;
					int uc = 0;
					conn->queue_read(did);
					conn->queue_read(ut);
					conn->queue_read(uc);
					rflush();
					session->getPlayerHandle(0)->purchaseDivision(did,ut,uc);
				}
					break;
				case 0x13: // removeDivision(DivisionID)
				{
					conn->queue_read(did);
					rflush();
					session->getPlayerHandle(0)->removeDivision(did);
				}
					break;
				case 0x101: // setPosition(vec2)
				{
					vec2 pos;
					conn->queue_read(did);
					conn->queue_read(pos);
					rflush();
					session->getPlayerHandle(0)->forDivisionHandleID(did,[pos](DivisionHandle *dh)
					{
						dh->setPosition(pos);
					});
				}
					break;
				case 0x102: // setDirection(vec2)
				{
					vec2 dir;
					conn->queue_read(did);
					conn->queue_read(dir);
					rflush();
					session->getPlayerHandle(0)->forDivisionHandleID(did,[dir](DivisionHandle *dh)
					{
						dh->setDirection(dir);
					});
				}
					break;
				case 0x103: // setDestination(vec2)
				{
					vec2 dst;
					conn->queue_read(did);
					conn->queue_read(dst);
					rflush();
					session->getPlayerHandle(0)->forDivisionHandleID(did,[dst](DivisionHandle *dh)
					{
						dh->setDestination(dst);
					});
				}
					break;
				case 0x104: // setDistance(double)
				{
					double dist;
					conn->queue_read(did);
					conn->queue_read(dist);
					rflush();
					session->getPlayerHandle(0)->forDivisionHandleID(did,[dist](DivisionHandle *dh)
					{
						dh->setDistance(dist);
					});
				}
					break;
				case 0x105: // setWidth(int)
				{
					int width;
					conn->queue_read(did);
					conn->queue_read(width);
					rflush();
					session->getPlayerHandle(0)->forDivisionHandleID(did,[width](DivisionHandle *dh)
					{
						dh->setWidth(width);
					});
				}
					break;
				case 0x106: // setMode(DivisionMode)
				{
					DivisionMode mode;
					conn->queue_read(did);
					conn->queue_read(mode);
					rflush();
					session->getPlayerHandle(0)->forDivisionHandleID(did,[mode](DivisionHandle *dh)
					{
						dh->setMode(mode);
					});
				}
					break;
				}
			}
			
			printf("data was received from %d\n",conn->get_fd());
			
			storage->forDivisionsConst([conn,wflush](const Division *d)
			{
				DivisionID did = d->getID();
				vec2 dpos = d->getPosition();
				vec2 ddir = d->getDirection();
				double dist = d->getDistance();
				int width = d->getWidth();
				conn->queue_write(did);
				conn->queue_write(dpos);
				conn->queue_write(ddir);
				conn->queue_write(dist);
				conn->queue_write(width);
				wflush();
				for(const Unit *u : *d)
				{
					UnitID id = u->getID();
					UnitType type = u->getType();
					vec2 dir = u->getDir();
					vec2 dst = u->getDst();
					conn->queue_write(id);
					conn->queue_write(type);
					conn->queue_write(dir);
					conn->queue_write(dst);
					wflush();
				}
				conn->queue_write(UnitID(0));
				wflush();
			});
			conn->queue_write(DivisionID(0));
			wflush();
			
			storage->forObjectsConst([conn,wflush](const Object *o)
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
				wflush();
			});
			conn->queue_write(ObjectID(0));
			wflush();
			
			printf("data was sent to %d\n",conn->get_fd());
		}
		catch(std::exception)
		{
			return;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(500));
	}
}
