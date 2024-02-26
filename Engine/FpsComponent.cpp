#include <stdexcept>
#include "FpsComponent.h"
#include "GameObject.h"
#include "Renderer.h"
#include "Font.h"
#include "Timer.h"
#include "Texture2D.h"

FpsComponent::FpsComponent(GameObject* const owner, std::shared_ptr<Font> font, SDL_Color textColor)
	: Component{ owner }
	, m_Font{ font }
	, m_TextTexture{ nullptr }
	, m_TextColor{ textColor }
	, m_NeedsUpdate{ true }
	, m_TotalWaitTime{ }
	, m_UpdateTickTime{ 0.5f }
{
}

void FpsComponent::Update()
{
	if (m_NeedsUpdate)
	{
		std::stringstream ss;
		ss << std::fixed << std::setprecision(2) << Timer::GetInstance().GetPreciseFPS() << " FPS";
		const std::string text{ ss.str() };

		SDL_Surface* surface{ TTF_RenderText_Blended(m_Font->GetFont(), text.c_str(), m_TextColor) };
		if (!surface) throw std::runtime_error(std::string("Render text failed: ") + SDL_GetError());

		SDL_Texture* texture{ SDL_CreateTextureFromSurface(Renderer::GetInstance().GetSDLRenderer(), surface) };
		if (!texture) throw std::runtime_error(std::string("Create text texture from surface failed: ") + SDL_GetError());

		SDL_FreeSurface(surface);
		m_TextTexture = std::make_shared<Texture2D>(texture);

		m_NeedsUpdate = false;
	}
	else
	{
		m_TotalWaitTime += Timer::GetInstance().GetElapsedSec();

		if (m_TotalWaitTime > m_UpdateTickTime)
		{
			m_TotalWaitTime -= m_UpdateTickTime;
			m_NeedsUpdate = true;
		}
	}
}

void FpsComponent::Render() const
{
	if (m_TextTexture.get())
	{
		const glm::vec3& renderPos{ m_Owner->GetTransform().GetPosition() };
		Renderer::GetInstance().RenderTexture(*m_TextTexture, renderPos.x, renderPos.y);
	}
}