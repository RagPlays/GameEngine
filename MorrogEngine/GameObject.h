#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <type_traits>
#include <concepts>

#include "Transform.h"

namespace MoE
{
	class Component;

	template<class ComponentType>
	concept IsComponent = std::is_base_of_v<Component, ComponentType>;

	class GameObject final
	{
	public:

		GameObject();
		~GameObject();

		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) noexcept = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) noexcept = delete;

		// functions
		void SceneStart();
		void FixedUpdate();
		void Update();
		void LateUpdate();
		void Render() const;
		void OnDestroy();
		void SceneEnd();

		// Components
		template <IsComponent ComponentType>
		void AddComponent(std::unique_ptr<ComponentType>&& component)
		{
			if (!HasComponent<ComponentType>())
			{
				m_Components[typeid(ComponentType)] = std::move(component);
			}
		}

		template <IsComponent ComponentType>
		void RemoveComponent()
		{
			m_Components.erase(typeid(ComponentType));
		}

		template <IsComponent ComponentType>
		ComponentType* GetComponent() const
		{
			auto it{ m_Components.find(typeid(ComponentType)) };
			if (it != m_Components.end())
			{
				return static_cast<ComponentType*>(it->second.get());
			}
			return nullptr;
		}

		template <IsComponent ComponentType>
		bool HasComponent() const
		{
			return m_Components.find(typeid(ComponentType)) != m_Components.end();
		}

		// Childeren/Parent
		bool IsChild(GameObject* gameObj) const;
		GameObject* GetParent() const;
		size_t GetChildCount() const;
		GameObject* GetChildAt(size_t idx) const;
		const std::vector<std::unique_ptr<GameObject>>& GetChilderen() const;
		void AddChild(std::unique_ptr<GameObject>&& child, bool keepWorldPos = false);

		// Get/Set Transforms
		const glm::vec2& GetLocalPosition() const;
		void SetLocalPosition(const glm::vec2& pos);
		const glm::vec2& GetWorldPosition();
		void SetWorldPosition(const glm::vec2& pos);
		void SetPositionDirty();

		// Translate
		void Translate(const glm::vec2& translate);

		// Deleting / Destroying
		bool IsDestroyed() const;
		void DeleteDestroyed();

		// Other
		void Destroy();
		static void Destroy(GameObject* gameObj);

	private:

		void RemoveChild(GameObject* child);
		bool IsAncestor(GameObject* gameObj);

		void UpdateWorldPosition();

	private:

		Transform m_LocalTransform;
		Transform m_WorldTransform;
		std::unordered_map<std::type_index, std::unique_ptr<Component>> m_Components;
		std::vector<std::unique_ptr<GameObject>> m_Children;
		GameObject* m_Parent;
		bool m_PositionIsDirty;
		bool m_IsDestroyed;

	};
}

#endif // !GAMEOBJECT_H