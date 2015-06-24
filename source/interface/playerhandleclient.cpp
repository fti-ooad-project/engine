#include "playerhandleclient.hpp"

#include "divisionhandleclient.hpp"

#include <cmath>

static int division_id_counter = 0;

PlayerHandleClient::PlayerHandleClient(int _id, Storage *s, TCPConnection *c)
  : PlayerHandleBase(_id,s), conn(c)
{
	
}

PlayerHandleClient::~PlayerHandleClient()
{
	
}

// PlayerHandle methods
void PlayerHandleClient::forEachDivisionHandle(std::function<void(DivisionHandle *dh)> func)
{
	Storage *storage = getStorage();
	storage->forDivisions([func,this](Division *d)
	{
		DivisionHandleClient dh(d,conn);
		func(&dh);
	});
}

bool PlayerHandleClient::forDivisionHandleID(DivisionID id, std::function<void(DivisionHandle *dh)> func)
{
	Storage *storage = getStorage();
	bool done = false;
	storage->forDivisions([id,func,&done,this](Division *d)
	{
		if(id == d->getID())
		{
			DivisionHandleClient dh(d,conn);
			func(&dh);
			done = true;
		}
	});
	return done;
}

std::pair<DivisionID,DivisionID> PlayerHandleClient::splitDivision(DivisionID id, std::function<bool(UnitSpectator*)> ind)
{
	// ???
	return std::pair<DivisionID,DivisionID>(0,0);
}
DivisionID PlayerHandleClient::mergeDivisions(DivisionID one, DivisionID two)
{
	// ???
	return 0;
}
DivisionID PlayerHandleClient::purchaseDivision(DivisionID id, UnitType type, int unit_count)
{
	int command = 0x12; //purchase division code
	conn->queue_write(command);
	int did = 0;
	if(id > 0)
		did = id;
	else
		did = ++division_id_counter + 0x1000*getID();
	conn->queue_write(did);
	conn->queue_write(type);
	conn->queue_write(unit_count);
	try
	{
		while(conn->get_write_size() != 0)
		{
			conn->perform_write();
		}
	}
	catch(TCPException)
	{
		return 0;
	}
	return did;
}
bool PlayerHandleClient::removeDivision(DivisionID id)
{
	int command = 0x13; //remove division code
	conn->queue_write(command);
	conn->queue_write(id);
	try
	{
		while(conn->get_write_size() != 0)
		{
			conn->perform_write();
		}
	}
	catch(TCPException)
	{
		return false;
	}
	return true;
}

