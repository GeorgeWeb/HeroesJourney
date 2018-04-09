#include "Hero.hpp"
#include "../DEFINITIONS.hpp"

namespace HJ { namespace Entities {

	Hero::Hero() :
		m_spriteComp(AddComponent<Engine::Components::SpriteComponent>("C_bHeroSprite")),
		m_animatorComp(AddComponent<Engine::Components::AnimatorComponent>("C_HeroAnimator")),
		m_statusComp(AddComponent<Components::StatusComponent>("C_aHeroStatus")),
		m_skillComp(AddComponent<Components::SkillComponent>("C_HeroSkills"))
	{ }

	Hero::Hero(const std::string & t_name, HERO_TYPE t_type, unsigned int t_health, unsigned int t_damage, unsigned int t_armour) :
		m_spriteComp(AddComponent<Engine::Components::SpriteComponent>("C_bHeroSprite")),
		m_animatorComp(AddComponent<Engine::Components::AnimatorComponent>("C_HeroAnimator")),
		m_statusComp(AddComponent<Components::StatusComponent>("C_aHeroStatus")),
		m_skillComp(AddComponent<Components::SkillComponent>("C_HeroSkills"))
	{
		m_name = t_name;
		m_type = t_type;
		m_health = m_maxHealth = t_health;
		m_damage = t_damage;
		m_armour = t_armour;
	}

	Hero* Hero::GetType()
	{
		return this;
	}

	void Hero::ReceiveDamage(unsigned int t_damage)
	{
		m_health -= t_damage;
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

	std::shared_ptr<Components::StatusComponent> Hero::GetStatusComponent()
	{
		return m_statusComp;
	}

	std::shared_ptr<Components::SkillComponent> Hero::GetSkillComponent()
	{
		return m_skillComp;
	}

} }