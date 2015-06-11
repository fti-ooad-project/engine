#pragma once

#include "objectspectatorimpl.hpp"
#include "../storage.hpp"
#include <engine/spectator.hpp>
#include <engine/playerspectator.hpp>

class SpectatorImpl : public Spectator
{
private:
	Storage *storage;
	PlayerSpectator **players;
	int players_count;
	
public:
	SpectatorImpl(Storage *s, PlayerSpectator **ps, int pc);
	virtual ~SpectatorImpl();
	
	virtual void forEachObjectSpectator(std::function<void(ObjectSpectator*)>) override;
	virtual bool forObjectSpectatorID(ObjectID id, std::function<void(ObjectSpectator*)> func) override;
	
	virtual PlayerSpectator *getPlayerSpectator(int num) override;
	virtual int getPlayersCount() const override;
	
	virtual void setCallbackOnObjectCreate(std::function<void(ObjectSpectator*)>) override;
	virtual void setCallbackOnObjectRemove(std::function<void(ObjectSpectator*)>) override;
};
