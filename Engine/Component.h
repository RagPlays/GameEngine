#ifndef COMPONENT_H
#define COMPONENT_H

class GameObject;

class Component
{
public:

	explicit Component(GameObject* const owner);
	virtual ~Component() = default;
	Component(const Component& other) = delete;
	Component(Component&& other) noexcept = delete;
	Component& operator=(const Component& other) = delete;
	Component& operator=(Component&& other) noexcept = delete;

	virtual void FixedUpdate();
	virtual void Update();
	virtual void LateUpdate();
	virtual void Render() const;

	GameObject* const GetOwner() const;

protected:
	GameObject* const m_Owner;

private:
};

#endif // !COMPONENT_H