#ifndef FPSCOMPONENT_H
#define FPSCOMPONENT_H

#include <string>
#include <memory>
#include <SDL_ttf.h>
#include "Component.h"

class Font;
class Texture2D;
class GameObject;

class FpsComponent final : public Component
{
public:

	explicit FpsComponent(GameObject* const owner);
	virtual ~FpsComponent() = default;
	FpsComponent(const FpsComponent& other) = delete;
	FpsComponent(FpsComponent&& other) noexcept = delete;
	FpsComponent& operator=(const FpsComponent& other) = delete;
	FpsComponent& operator=(FpsComponent&& other) noexcept = delete;

	virtual void Update() override;

private:

	bool m_NeedsUpdate;
	int m_FrameCount;
	float m_TotalWaitTime;
	const float m_UpdateTickTime;
};

#endif // !FPSCOMPONENT_H