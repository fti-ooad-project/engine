#include "divisionhandleclient.hpp"

#include "unitspectatorimpl.hpp"

DivisionHandleClient::DivisionHandleClient(Division *d, TCPConnection *c)
  : DivisionHandleBase(d), conn(c)
{
	
}

DivisionHandleClient::~DivisionHandleClient()
{
	
}

// DivisionHandle methods

static int flush(TCPConnection *c)
{
	try
	{
		while(c->write_size() > 0)
		{
			c->perform_write();
		}
	}
	catch(TCPConnection)
	{
		return -1;
	}
	return 0;
}

void DivisionHandleClient::setPosition(const vec2 &pos)
{
	int command = 0x101;
	DivisionID id = getDivision()->getID();
	conn->queue_write(command);
	conn->queue_write(id);
	conn->queue_write(pos);
	flush(conn);
}

void DivisionHandleClient::setDirection(const vec2 &dir)
{
	int command = 0x102;
	DivisionID id = getDivision()->getID();
	conn->queue_write(command);
	conn->queue_write(id);
	conn->queue_write(dir);
	flush(conn);
}

void DivisionHandleClient::setDestination(const vec2 &dst)
{
	int command = 0x103;
	DivisionID id = getDivision()->getID();
	conn->queue_write(command);
	conn->queue_write(id);
	conn->queue_write(dst);
	flush(conn);
}

void DivisionHandleClient::setDistance(double dist)
{
	int command = 0x104;
	DivisionID id = getDivision()->getID();
	conn->queue_write(command);
	conn->queue_write(id);
	conn->queue_write(dist);
	flush(conn);
}

void DivisionHandleClient::setWidth(int width)
{
	int command = 0x105;
	DivisionID id = getDivision()->getID();
	conn->queue_write(command);
	conn->queue_write(id);
	conn->queue_write(width);
	flush(conn);
}

void DivisionHandleClient::setMode(DivisionMode m)
{
	int command = 0x106;
	DivisionID id = getDivision()->getID();
	conn->queue_write(command);
	conn->queue_write(id);
	conn->queue_write(m);
	flush(conn);
}

