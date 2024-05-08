#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>

class Transform final
{
public:

	Transform();
	~Transform() = default;

	Transform(const Transform& other) = default;
	Transform(Transform&& other) noexcept = default;
	Transform& operator=(const Transform& other) = default;
	Transform& operator=(Transform&& other) noexcept = default;

	// Position
	const glm::vec2& GetPosition() const;
	void SetPosition(float x, float y);
	void SetPosition(const glm::vec2& position);

	//// Rotation
	//const glm::vec2& GetRotation() const;
	//void SetRotation(float x, float y);
	//void SetRotation(const glm::vec2& rotation);

	//// Scale
	//const glm::vec2& GetScale() const;
	//void SetScale(float x, float y);
	//void SetScale(const glm::vec2& scale);

private:

	glm::vec2 m_Position;
	//glm::vec2 m_Rotation; // in radians
	//glm::vec2 m_Scale;

};

#endif // !TRANSFORM_H