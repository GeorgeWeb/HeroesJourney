#include "Bard.h"

namespace HJ { namespace Entities {

	Bard::Bard(const std::string & t_sprite, const std::string & t_animatior) :
		Hero(t_sprite, t_animatior)
	{
		m_health = 100;
		m_mana = 80;
		m_armour = 10;
		m_damage = 30;
		m_alive = true;
		m_dodgeChance = 3;
		m_critChance = 2;
		m_isFlaming = false;
		m_isStunned = false;

	}

	void Bard::Init(const sf::Texture & t_texture, sf::IntRect t_texRect)
	{
		Hero::Init(t_texture, t_texRect);
	}

	void Bard::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Bard::Render()
	{
		Hero::Render();
	}

	void Bard::Attack(std::shared_ptr<Entity> t_entity)
	{
		// todo
	}

	void Bard::Skill(const std::function<void(std::shared_ptr<Entity>t_entity)>& t_func)
	{
		Hero::Skill(t_func);
	}

	void Bard::Defend()
	{
		// todo
	}

	void Bard::SoothingSong()
	{
		// todo
	}

	void Bard::HymnOfCharge()
	{
		// todo
	}

} }