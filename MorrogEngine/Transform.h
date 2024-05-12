#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <glm.hpp>

namespace MoE
{
	class Transform final
	{
	public:

		Transform() = default;
		~Transform() = default;

		Transform(const Transform& other) = default;
		Transform(Transform&& other) noexcept = default;
		Transform& operator=(const Transform& other) = default;
		Transform& operator=(Transform&& other) noexcept = default;

		// Position
		const glm::vec2& GetPosition() const;
		void SetPosition(float x, float y);
		void SetPosition(const glm::vec2& position);

	private:

		glm::vec2 m_Position;
		float m_Rotation; // in radians

	};
}

#endif // !TRANSFORM_H