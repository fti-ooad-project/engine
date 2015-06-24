#pragma once

#include <string>
#include <thread>

#include "session.hpp"

#ifndef ProcessorWrapper
#define ProcessorWrapper void
#endif

#ifndef StorageWrapper
#define StorageWrapper void
#endif

#ifndef TCPConnectionWrapper
#define TCPConnectionWrapper void
#endif

class RemoteSession : public Session
{
private:
	ProcessorWrapper *processor;
	StorageWrapper *storage;
	TCPConnectionWrapper *connection;
	std::thread *thread;
	
	PlayerHandle **players = nullptr;
	Spectator *spectator = nullptr;
	int players_count;
	
	SessionState state = SessionState::DISABLE;
	
public:
	RemoteSession(const std::string &host, int port);
	virtual ~RemoteSession();
	
	void process(double dt);
	
	virtual PlayerHandle *getPlayerHandle(int num) override;
	virtual int getPlayersCount() const override;
	
	virtual Spectator *getSpectator() override;
	virtual SessionState getState() const override;
};
