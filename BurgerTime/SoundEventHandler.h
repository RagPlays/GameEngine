#ifndef SOUNDEVENTHANDLER_H
#define SOUNDEVENTHANDLER_H

#include <memory>
#include "EventHandler.h"

class MusicPlayer;
class SoundEffect;

class SoundEventHandler final : public EventHandler
{
public:

	SoundEventHandler() = default;
	virtual ~SoundEventHandler() = default;

	SoundEventHandler(const SoundEventHandler& other) = delete;
	SoundEventHandler(SoundEventHandler&& other) noexcept = delete;
	SoundEventHandler& operator=(const SoundEventHandler& other) = delete;
	SoundEventHandler& operator=(SoundEventHandler&& other) noexcept = delete;

	virtual void HandleEvent(GameEvent gameEvent) override;

private:
};

#endif // !SOUNDEVENTHANDLER_H
