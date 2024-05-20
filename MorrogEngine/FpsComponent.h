#ifndef FPSCOMPONENT_H
#define FPSCOMPONENT_H

#include <string>

#include "Component.h"

namespace MoE
{
	class FpsComponent final : public Component
	{
	public:

		explicit FpsComponent(GameObject* const owner);
		virtual ~FpsComponent() = default;

		FpsComponent(const FpsComponent& other) = delete;
		FpsComponent(FpsComponent&& other) noexcept = delete;
		FpsComponent& operator=(const FpsComponent& other) = delete;
		FpsComponent& operator=(FpsComponent&& other) noexcept = delete;
		
		virtual void SceneStart() override;
		virtual void Update() override;

	private:

		int m_FrameCount;
		float m_TotalWaitTime;
		const float m_UpdateTickTime;

	};
}

#endif // !FPSCOMPONENT_H