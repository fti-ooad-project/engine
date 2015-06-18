#pragma once

#include "tcp/connection.hpp"

#include <engine/session.hpp>
#include "storage.hpp"

class ClientStream
{
private:
	Session *session;
	Storage *storage;
	
public:
	ClientStream(Session *s, Storage *st);
	~ClientStream();
	
	void operator()(TCPConnection *conn);
};
