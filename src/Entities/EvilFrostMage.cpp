#include "EvilFrostMage.hpp"

namespace HJ { namespace Entities {

	EvilFrostMage::EvilFrostMage(const std::string& t_sprite) :
		EvilAI(t_sprite)
	{
		m_health = 150;
		m_maxHealth = 150;
		m_mana = 75;
		m_maxMana = 75;
		m_armour = 20;
		m_damage = 50;
		m_dodgeChance = 2;
		m_critChance = 3;
		m_isFlaming = false;
		m_isStunned = false;
	}

	EvilFrostMage::EvilFrostMage(const std::string & t_sprite, const std::string& t_animator) :
		EvilAI(t_sprite, t_animator)
	{
		m_health = 150;
		m_maxHealth = 150;
		m_mana = 75;
		m_maxMana = 75;
		m_armour = 20;
		m_damage = 50;
		m_dodgeChance = 2;
		m_critChance = 3;
		m_isFlaming = false;
		m_isStunned = false;
	}

	EvilFrostMage* EvilFrostMage::GetType()
	{
		return this;
	}

	void EvilFrostMage::Init()
	{
		EvilAI::Init();
	}

	void EvilFrostMage::Update(float t_deltaTime)
	{
		EvilAI::Update(t_deltaTime);
	}

	void EvilFrostMage::Render()
	{
		EvilAI::Render();
	}

	void EvilFrostMage::Attack()
	{
		// implement
	}

	void EvilFrostMage::Skill(std::function<void()> t_func)
	{
		EvilAI::Skill(t_func);
	}

	void EvilFrostMage::Defend()
	{
		// implement
	}

} }