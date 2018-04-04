#include "Sorceress.hpp"

namespace HJ {namespace Entities {

	HJ::Entities::Sorceress::Sorceress(const std::string& t_sprite) :
		Hero(t_sprite)
	{
		m_health = 75;
		m_maxHealth = 75;
		m_mana = 120;
		m_maxMana = 120;
		m_armour = 5;
		m_damage = 30;
		m_alive = true;
		m_dodgeChance = 1;
		m_critChance = 2;
		m_isFlaming = false;
		m_isStunned = false;
	}

	HJ::Entities::Sorceress::Sorceress(const std::string& t_sprite, const std::string& t_animatior):
		Hero(t_sprite, t_animatior)
	{
		m_health = 75;
		m_maxHealth = 75;
		m_mana = 120;
		m_maxMana = 120;
		m_armour = 5;
		m_damage = 30;
		m_alive = true;
		m_dodgeChance = 1;
		m_critChance = 2;
		m_isFlaming = false;
		m_isStunned = false;
	}

	Sorceress* Sorceress::GetType()
	{
		return this;
	}

	void Sorceress::Init()
	{
		Hero::Init();
	}

	void Sorceress::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Sorceress::Render()
	{
		Hero::Render();
	}

	void Sorceress::Attack(std::shared_ptr<EvilAI> t_enemy)
	{
		// implement
	}

	void Sorceress::Defend()
	{
		// implement
	}

	void Sorceress::UseSkill1(std::shared_ptr<EvilAI> t_enemy)
	{
		// implement
	}

	void Sorceress::UseSkill2(std::shared_ptr<EvilAI> t_enemy)
	{
		// implement
	}

} }