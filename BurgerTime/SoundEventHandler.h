#ifndef SOUNDEVENTHANDLER_H
#define SOUNDEVENTHANDLER_H

#include "EventHandler.h"

using EventID = int;

namespace MoE
{
	class MusicPlayer;
	class SoundEffect;
}

class SoundEventHandler final : public MoE::EventHandler
{
public:

	SoundEventHandler() = default;
	virtual ~SoundEventHandler() = default;

	SoundEventHandler(const SoundEventHandler& other) = delete;
	SoundEventHandler(SoundEventHandler&& other) noexcept = delete;
	SoundEventHandler& operator=(const SoundEventHandler& other) = delete;
	SoundEventHandler& operator=(SoundEventHandler&& other) noexcept = delete;

	virtual void HandleEvent(EventID eventID) const override;

};

#endif // !SOUNDEVENTHANDLER_H
