#include "EvilAI.hpp"

namespace HJ { namespace Entities {

	EvilAI::EvilAI(const std::string& t_sprite, const std::string& t_animator) :
		m_spriteComp(AddComponent<Engine::Components::SpriteComponent>(t_sprite)),
		m_animatorComp(AddComponent<Engine::Components::AnimatorComponent>(t_animator))
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
			//animate death
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

	void EvilAI::Animate(const std::string& t_animationName)
	{
		m_spriteComp->GetSprite().setTextureRect(m_animatorComp->GetAnimation(t_animationName).uvRect);
	}

	void EvilAI::Skill(std::function<void()> t_func)
	{
		std::invoke([&]() { t_func; });
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