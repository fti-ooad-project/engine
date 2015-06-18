#pragma once

#include "session.hpp"

#ifndef StorageWrapper
#define StorageWrapper void
#endif

#ifndef ProcessorWrapper
#define ProcessorWrapper void
#endif

#ifndef TCPServerWrapper
#define TCPServerWrapper void
#endif

class LocalSession : public Session
{
private:
	ProcessorWrapper *processor;
	StorageWrapper *storage;
	TCPServerWrapper *server;
	
	PlayerHandle **players = nullptr;
	Spectator *spectator = nullptr;
	const int players_count;
	
	SessionState state = SessionState::DISABLE;
	
public:
	LocalSession(int c_players_count, int port);
	virtual ~LocalSession();
	
	void loadMap();
	void process(double dt);
	
	virtual PlayerHandle *getPlayerHandle(int num) override;
	virtual int getPlayersCount() const override;
	
	virtual Spectator *getSpectator() override;
	virtual SessionState getState() const override;
};
