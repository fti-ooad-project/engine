#pragma once

#include <engine/session.hpp>
#include "storage.hpp"

#include "tcp/connection.hpp"

class ServerStream
{
private:
	Session *session;
	Storage *storage;
	
public:
	ServerStream(Session *s, Storage *st);
	virtual ~ServerStream();
	
	void operator()(TCPConnection *c);
};
