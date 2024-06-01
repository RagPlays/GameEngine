#ifndef ANIMATION_H
#define	ANIMATION_H

#include <SDL.h>
#include <cstdint>
#include <vector>

namespace MoE
{
	class TextureRenderer;

	struct Recti;
}

class Animation final
{
public:

	explicit Animation(MoE::TextureRenderer* renderComponent, uint8_t nrOfFrames, uint8_t fps);
	~Animation() = default;

	Animation(const Animation& other) = delete;
	Animation(Animation&& other) noexcept = delete;
	Animation& operator=(const Animation& other) = delete;
	Animation& operator=(Animation&& other) noexcept = delete;

	void AddFrame(const SDL_Rect& srcRect);

	void Play();
	bool Update();
	void Stop(bool reset = true);

private:

	bool m_IsPlaying;
	uint8_t m_CurrentFrame;
	uint8_t m_NrOfFrames;
	uint8_t m_FPS;
	float m_LastFrameTime;
	MoE::TextureRenderer* m_pRenderComponent;
	std::vector<SDL_Rect> m_SrcRects;

};

#endif // !ANIMATION_H