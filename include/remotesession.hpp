#pragma once

#include <string>
#include <thread>

#include "session.hpp"

#ifndef StorageWrapper
#define StorageWrapper void
#endif

#ifndef TCPConnectionWrapper
#define TCPConnectionWrapper void
#endif

class RemoteSession : public Session
{
private:
	StorageWrapper *storage;
	TCPConnectionWrapper *connection;
	std::thread *thread;
	
	Spectator *spectator = nullptr;
	const int players_count;
	
	SessionState state = SessionState::DISABLE;
	
public:
	RemoteSession(const std::string &host, int port);
	virtual ~RemoteSession();
	
	virtual PlayerHandle *getPlayerHandle(int num) override;
	virtual int getPlayersCount() const override;
	
	virtual Spectator *getSpectator() override;
	virtual SessionState getState() const override;
};
