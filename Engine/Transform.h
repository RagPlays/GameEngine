#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm/glm.hpp>

class Transform final
{
public:

	// Position
	const glm::vec3& GetPosition() const;
	void SetPosition(float x, float y, float z);

	// Rotation

	// Scale
	const glm::vec3& GetScale() const;
	void SetScale(float x, float y, float z);

private:

	glm::vec3 m_position;
	// m_Rotation
	glm::vec3 m_Scale;

};

#endif // !TRANSFORM_H