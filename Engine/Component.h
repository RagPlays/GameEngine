#ifndef COMPONENT_H
#define COMPONENT_H

#include <glm.hpp>

class GameObject;

class Component
{
public:

	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) noexcept = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) noexcept = delete;

	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render() const;

protected:
	explicit Component(GameObject* const owner);

	// Gets
	GameObject* const GetOwner() const;
	GameObject* GetParent() const;
	const glm::vec3& GetLocalPosition() const;
	const glm::vec3& GetWorldPosition() const;

	// Sets
	void SetLocalPosition(const glm::vec3& pos);

private:
	GameObject* const m_pOwner;
};

#endif // !COMPONENT_H