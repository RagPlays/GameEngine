#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <glm/glm.hpp>
#include <string>
#include <vector>
#include <memory>
#include "Component.h"
#include "Transform.h"

class GameObject final
{
public:

	explicit GameObject(bool isStatic = false, const std::string& tag = "Empty");
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

	// Components
	template <typename ComponentType>
	void AddComponent(std::shared_ptr<Component> component)
	{
		if (!HasComponent<ComponentType>())
		{
			m_Components.emplace_back(std::move(component));
		}
	}
	template <typename ComponentType>
	void RemoveComponent()
	{
		std::shared_ptr<ComponentType>& component{ GetComponent<ComponentType>() };
		if (component.get())
		{
			m_Components.erase(std::remove(m_Components.begin(), m_Components.end(), GetComponent<ComponentType>()), m_Components.end());
		}
	}
	template <typename ComponentType>
	std::shared_ptr<ComponentType> GetComponent() const
	{
		for (auto& component : m_Components)
		{
			std::shared_ptr<ComponentType> castedComponent{ std::dynamic_pointer_cast<ComponentType>(component) };
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
			if (std::dynamic_pointer_cast<ComponentType>(component))
			{
				return true;
			}
		}
		return false;
	}

	// Childeren/Parent
	bool IsChild(GameObject* gameObj) const;
	GameObject* GetParent() const;
	int GetChildCount() const;
	GameObject* GetChildAt(size_t idx) const;
	GameObject* GetChildAt(int idx) const;
	const std::vector<std::unique_ptr<GameObject>>& GetChilderen() const;
	void SetParent(GameObject* parent, bool keepWorldPos = false);

	// Get/Set Transforms
	const glm::vec3& GetLocalPosition() const;
	void SetLocalPosition(const glm::vec3& pos);
	const glm::vec3& GetWorldPosition();

	// Getters
	bool IsDestroyed() const;
	const std::string& GetTag() const;

	// Setters
	void SetTag(const std::string& tag);

	// Other
	bool CompareTag(const std::string& tag);
	void Destroy();

private:

	bool m_IsStatic;
	bool m_PositionIsDirty;
	bool m_IsDestroyed;
	std::string m_Tag;
	Transform m_LocalTransform;
	Transform m_WorldTransform;
	std::vector<std::shared_ptr<Component>> m_Components;

	std::vector<std::unique_ptr<GameObject>> m_Children;
	GameObject* m_Parent;

	void AddChild(GameObject* child);
	void RemoveChild(GameObject* child);
	void UpdateWorldPosition();
};

#endif // !GAMEOBJECT_H