#include "HealthComponent.h"

using namespace MoE;

HealthComponent::HealthComponent(GameObject* const owner, float maxHealth)
	: Component{ owner }
	, m_CurrentHealth{ maxHealth }
	, m_MaxHealth{ maxHealth }
	, m_IsDead{ false }
{
}

void HealthComponent::Damage(float damageValue)
{
	if (m_IsDead) return;

	m_CurrentHealth -= damageValue;
	if (m_CurrentHealth <= 0.f)
	{
		m_IsDead = true;
		m_CurrentHealth = 0.f;
	}
}

void HealthComponent::Heal(float healValue)
{
	if (m_IsDead) return;

	m_CurrentHealth += healValue;
	if (m_CurrentHealth > m_MaxHealth)
	{
		m_CurrentHealth = m_MaxHealth;
	}
}

void HealthComponent::SetHealth(float health)
{
	m_CurrentHealth = health;
}

float HealthComponent::GetHealth() const
{
	return m_CurrentHealth;
}

void HealthComponent::SetMaxHealth(float maxHealth)
{
	m_MaxHealth = maxHealth;
	if (m_CurrentHealth > maxHealth)
	{
		m_CurrentHealth = maxHealth;
	}
}

float HealthComponent::GetMaxHealth() const
{
	return m_MaxHealth;
}

void HealthComponent::Revive(float health)
{
	m_IsDead = false;
	if (health > 0.f)
	{
		m_CurrentHealth = health;
	}
	else
	{
		m_CurrentHealth = m_MaxHealth;
	}
}

void HealthComponent::Kill()
{
	m_IsDead = true;
	m_CurrentHealth = 0.f;
}