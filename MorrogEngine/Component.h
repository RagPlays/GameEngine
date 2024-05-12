#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm.hpp>

namespace MoE
{
	class GameObject;

	class Component
	{
	public:

		virtual ~Component() = default;

		Component(const Component& other) = delete;
		Component(Component&& other) noexcept = delete;
		Component& operator=(const Component& other) = delete;
		Component& operator=(Component&& other) noexcept = delete;

		virtual void GameStart();
		virtual void FixedUpdate();
		virtual void Update();
		virtual void LateUpdate();
		virtual void Render() const;
		virtual void OnDestroy();

		GameObject* const GetOwner() const;
		GameObject* GetParent() const;

	protected:

		explicit Component(GameObject* const owner);

		// Gets
		const glm::vec2& GetLocalPosition() const;
		const glm::vec2& GetWorldPosition() const;

		// Sets
		void SetLocalPosition(const glm::vec2& pos);

	private:

		GameObject* const m_pOwner;

	};
}

#endif // !COMPONENT_H