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

	explicit FpsComponent(GameObject* const owner, std::shared_ptr<Font> font, SDL_Color textColor = { 255, 255, 255 });
	~FpsComponent() = default;
	FpsComponent(const FpsComponent& other) = delete;
	FpsComponent(FpsComponent&& other) noexcept = delete;
	FpsComponent& operator=(const FpsComponent& other) = delete;
	FpsComponent& operator=(FpsComponent&& other) noexcept = delete;

	virtual void Update() override;
	virtual void Render() const override;

private:

	bool m_NeedsUpdate;
	float m_TotalWaitTime;
	const float m_UpdateTickTime;
	std::shared_ptr<Font> m_Font;
	std::shared_ptr<Texture2D> m_TextTexture;
	SDL_Color m_TextColor;
};

#endif // !FPSCOMPONENT_H