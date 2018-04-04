#include "Hero.hpp"

namespace HJ { namespace Entities {

	Hero::Hero(const std::string& t_sprite) :
		m_spriteComp(AddComponent<Engine::Components::SpriteComponent>(t_sprite))
	{ }

	Hero::Hero(const std::string& t_sprite, const std::string& t_animator) :
		m_spriteComp(AddComponent<Engine::Components::SpriteComponent>(t_sprite)),
		m_animatorComp(AddComponent<Engine::Components::AnimatorComponent>(t_animator))
	{ }

	Hero* Hero::GetType()
	{
		return this;
	}

	void Hero::Init()
	{
		m_spriteComp->GetSprite().scale(sf::Vector2f(5.0f, 5.0f));
		m_spriteComp->GetSprite().setColor(sf::Color(255, 255, 255, 255));

		SetVisible(true);
		SetAlive(true);
	}

	void Hero::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);

		//check if hero dies
		if (m_health <= 0) 
		{
			// animate death
		}
	}

	void Hero::Render()
	{
		Entity::Render();
	}

	void Hero::SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect)
	{
		m_spriteComp->GetSprite().setTexture(t_texture);
		m_spriteComp->GetSprite().setTextureRect(t_texRect);
	}

	void Hero::Animate(const std::string& t_animationName)
	{
		m_spriteComp->GetSprite().setTextureRect(m_animatorComp->GetAnimation(t_animationName).uvRect);
	}

	std::shared_ptr<Engine::Components::SpriteComponent> Hero::GetSpriteComponent()
	{
		return m_spriteComp;
	}

	std::shared_ptr<Engine::Components::AnimatorComponent> Hero::GetAnimatorComponent()
	{
		return m_animatorComp;
	}

} }