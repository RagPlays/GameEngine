#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

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
	void AddComponent(std::shared_ptr<Component> component);
	void RemoveComponent(std::shared_ptr<Component> component);
	template <typename ComponentType>
	std::shared_ptr<ComponentType> GetComponent();
	template <typename ComponentType>
	bool HasComponent();

	// Getters
	bool IsStatic() const;
	const std::string& GetTag() const;
	const Transform& GetTransform() const;

	// Setters
	void SetTag(const std::string& tag);
	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3& pos);
	void SetPosition(float x, float y);
	void SetPosition(const glm::vec2& pos);

	// Other
	bool CompareTag(const std::string& tag);

private:

	const bool m_IsStatic;
	std::string m_Tag;
	Transform m_Transform;
	std::vector<std::shared_ptr<Component>> m_Components;
};

#endif // !GAMEOBJECT_H