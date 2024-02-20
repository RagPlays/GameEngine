#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

#include <memory>
#include "Transform.h"

class Texture2D;

// todo: this should become final.
class GameObject
{
public:
	virtual void FixedUpdate(float elapsedSec);
	virtual void Update(float elapsedSec);
	virtual void LateUpdate(float elapsedSec);
	virtual void Render() const;

	void SetTexture(const std::string& filename);
	void SetPosition(float x, float y);

	GameObject() = default;
	virtual ~GameObject();
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	GameObject& operator=(const GameObject& other) = delete;
	GameObject& operator=(GameObject&& other) = delete;

private:
	Transform m_Transform{};
	// todo: mmm, every gameobject has a texture? Is that correct?
	std::shared_ptr<Texture2D> m_Texture{};
};

#endif // !GAMEOBJECT_H