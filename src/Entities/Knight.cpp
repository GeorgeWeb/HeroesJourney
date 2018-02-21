#include "Knight.hpp"

namespace HJ { namespace Entities {

	Knight::Knight(const std::string & t_sprite, const std::string & t_animator) :
		Hero(t_sprite, t_animator)
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

	void Knight::Init(const sf::Texture& t_texture, sf::IntRect t_texRect)
	{
		Hero::Init(t_texture, t_texRect);
	}

	void Knight::Update(float t_deltaTime)
	{
		Hero::Update(t_deltaTime);
	}

	void Knight::Render()
	{
		Hero::Render();
	}

	void Knight::Attack(std::shared_ptr<Entity> t_entity)
	{
		// implement
	}

	void Knight::Skill(const std::function<void(std::shared_ptr<Entity>t_entity)>& t_func)
	{
		Hero::Skill(t_func);
	}

	void Knight::Defend()
	{
		// implement
	}

	void Knight::HeroSlash()
	{
		// todo
	}

	void Knight::ShoulderBash()
	{
		// todo
	}

} }