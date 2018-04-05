#include "EvilAI.hpp"

namespace HJ { namespace Entities {

	EvilAI::EvilAI(const std::string& t_sprite) :
		m_spriteComp(AddComponent<Engine::Components::SpriteComponent>(t_sprite))
	{ }

	EvilAI* EvilAI::GetType()
	{
		return this;
	}

	void EvilAI::Init()
	{
		m_spriteComp->GetSprite().scale(sf::Vector2f(5.0f, 5.0f));
		m_spriteComp->GetSprite().setColor(sf::Color(255, 255, 255, 255));

		SetVisible(true);
		SetAlive(true);
	}

	void EvilAI::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);

		//check if hero dies
		if (m_health <= 0)
		{
			m_spriteComp->GetSprite().setColor(sf::Color(
				m_spriteComp->GetSprite().getColor().r - t_deltaTime,
				m_spriteComp->GetSprite().getColor().g - t_deltaTime,
				m_spriteComp->GetSprite().getColor().b - t_deltaTime,
				m_spriteComp->GetSprite().getColor().a - t_deltaTime
			));

			// reset to zero
			m_health = 0;
		}
	}

	void EvilAI::Render()
	{
		Entity::Render();
	}

	void EvilAI::SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect)
	{
		m_spriteComp->GetSprite().setTexture(t_texture);
		m_spriteComp->GetSprite().setTextureRect(t_texRect);
	}

	void EvilAI::TakeDamage(unsigned int t_dmg)
	{
		// check for dodge chance
		m_health -= t_dmg;
	}

	std::shared_ptr<Engine::Components::SpriteComponent> EvilAI::GetSpriteComponent()
	{
		return m_spriteComp;
	}

	std::shared_ptr<Engine::Components::AnimatorComponent> EvilAI::GetAnimatorComponent()
	{
		return m_animatorComp;
	}

} }