#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Component.h"
#include "Transform.h"

class GameObject final
{
public:

	explicit GameObject(const std::string& tag = "Empty");
	~GameObject() = default;
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) noexcept = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) noexcept  = delete;

	// functions
	void FixedUpdate();
	void Update();
	void LateUpdate();
	void Render() const;
	void OnDestroy();

	// Components
	template <typename ComponentType>
	void AddComponent(std::unique_ptr<Component> component)
	{
		if (!HasComponent<ComponentType>())
		{
			m_Components.emplace_back(std::move(component));
		}
	}
	template <typename ComponentType>
	void RemoveComponent()
	{
		ComponentType* component = GetComponent<ComponentType>();
		if (component)
		{
			m_Components.erase(std::remove_if(m_Components.begin(), m_Components.end(),[&](std::unique_ptr<Component> comp)
				{
					return comp.get() == component; 
				}
			), m_Components.end());
		}
	}
	template <typename ComponentType>
	ComponentType* GetComponent() const
	{
		for (auto& component : m_Components)
		{
			ComponentType* castedComponent{ dynamic_cast<ComponentType*>(component.get()) };
			if (castedComponent)
			{
				return castedComponent;
			}
		}
		return nullptr;
	}
	template <typename ComponentType>
	bool HasComponent() const
	{
		for (auto& component : m_Components)
		{
			if (dynamic_cast<ComponentType*>(component.get()))
			{
				return true;
			}
		}
		return false;
	}

	// Childeren/Parent
	bool IsChild(GameObject* gameObj) const;
	GameObject* GetParent() const;
	size_t GetChildCount() const;
	GameObject* GetChildAt(size_t idx) const;
	const std::vector<std::unique_ptr<GameObject>>& GetChilderen() const;
	void SetParent(GameObject* parent, bool keepWorldPos = false);

	// Get/Set Transforms
	const glm::vec3& GetLocalPosition() const;
	void SetLocalPosition(const glm::vec3& pos);
	const glm::vec3& GetWorldPosition();
	void SetWorldPosition(const glm::vec3& pos);
	void SetPositionDirty();

	// Translate
	void Translate(const glm::vec3& translate);

	// Getters
	bool IsDestroyed() const;
	const std::string& GetTag() const;

	// Setters
	void SetTag(const std::string& tag);

	// Other
	bool CompareTag(const std::string& tag);
	void Destroy();

private:

	bool m_PositionIsDirty;
	bool m_IsDestroyed;
	std::string m_Tag;
	Transform m_LocalTransform;
	Transform m_WorldTransform;
	std::vector<std::unique_ptr<Component>> m_Components;
	std::vector<std::unique_ptr<GameObject>> m_Children;
	GameObject* m_Parent;

	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	void UpdateWorldPosition();
};

#endif // !GAMEOBJECT_H