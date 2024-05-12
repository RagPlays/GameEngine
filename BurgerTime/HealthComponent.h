#ifndef HEALTHCOMPONENT_H
#define HEALTHCOMPONENT_H

#include "Component.h"

class HealthComponent final : public MoE::Component
{
public:

	explicit HealthComponent(MoE::GameObject* const owner, float maxHealth);
	virtual ~HealthComponent() = default;

	HealthComponent(const HealthComponent& other) = delete;
	HealthComponent(HealthComponent&& other) noexcept = delete;
	HealthComponent& operator=(const HealthComponent& other) = delete;
	HealthComponent& operator=(HealthComponent&& other) noexcept = delete;

	void Damage(float damageValue);
	void Heal(float healValue);
	
	void SetHealth(float health);
	float GetHealth() const;

	void SetMaxHealth(float maxHealth);
	float GetMaxHealth() const;

	void Revive(float health = -1.f);
	void Kill();

private:

	bool m_IsDead;
	float m_CurrentHealth;
	float m_MaxHealth;

};

#endif // !HEALTHCOMPONENT_H
