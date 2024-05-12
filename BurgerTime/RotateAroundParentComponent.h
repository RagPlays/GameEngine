#ifndef ROTATEAROUNDPARENTCOMPONENT_H
#define ROTATEAROUNDPARENTCOMPONENT_H

#include "Component.h"

class RotateAroundParentComponent final : public MoE::Component
{
public:

	explicit RotateAroundParentComponent(MoE::GameObject* const owner, float rotationSpeed = 1.57f);
	virtual ~RotateAroundParentComponent() = default;

	RotateAroundParentComponent(const RotateAroundParentComponent& other) = delete;
	RotateAroundParentComponent(RotateAroundParentComponent&& other) noexcept = delete;
	RotateAroundParentComponent& operator=(const RotateAroundParentComponent& other) = delete;
	RotateAroundParentComponent& operator=(RotateAroundParentComponent&& other) noexcept = delete;

	virtual void Update() override;

private:

	float m_RotationSpeed;
	float m_CurrentAngle;

};

#endif // !ROTATEAROUNDPARENTCOMPONENT_H