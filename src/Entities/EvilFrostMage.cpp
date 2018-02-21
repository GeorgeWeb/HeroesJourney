#include "EvilFrostMage.hpp"

namespace HJ { namespace Entities {

	EvilFrostMage::EvilFrostMage(const std::string & t_sprite, const std::string & t_animator) :
		EvilAI(t_sprite, t_animator)
	{
		m_health = 150;
		m_mana = 75;
		m_armour = 20;
		m_damage = 50;
		m_alive = true;
		m_dodgeChance = 2;
		m_critChance = 3;
		m_isFlaming = false;
		m_isStunned = false;
	}

	void EvilFrostMage::Init(const sf::Texture& t_texture, sf::IntRect t_texRect)
	{
		EvilAI::Init(t_texture, t_texRect);
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