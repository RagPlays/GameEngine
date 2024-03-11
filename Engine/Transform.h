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
	const glm::vec3& GetPosition() const;
	void SetPosition(float x, float y, float z);
	void SetPosition(const glm::vec3& position);

	// Rotation
	const glm::vec3& GetRotation() const;
	void SetRotation(float x, float y, float z);
	void SetRotation(const glm::vec3& rotation);

	// Scale
	const glm::vec3& GetScale() const;
	void SetScale(float x, float y, float z);
	void setScale(const glm::vec3& scale);

private:

	glm::vec3 m_Position;
	glm::vec3 m_Rotation; // in radians
	glm::vec3 m_Scale;

};

#endif // !TRANSFORM_H