#include "Hero.hpp"
#include "../DEFINITIONS.hpp"

using namespace Engine::ECM;
using namespace Engine::Components;

namespace HJ { namespace Entities {

	Hero::Hero() :
		m_spriteComp(AddComponent<Engine::Components::SpriteComponent>("C_HeroSprite")),
		m_animatorComp(AddComponent<Engine::Components::AnimatorComponent>("C_HeroAnimator"))
	{ }

	std::shared_ptr<Engine::Components::SpriteComponent> Hero::GetSpriteComponent()
	{
		return m_spriteComp;
	}

	std::shared_ptr<Engine::Components::AnimatorComponent> Hero::GetAnimatorComponent()
	{
		return m_animatorComp;
	}

	void Hero::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);
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

	void Hero::Animate()
	{
		for (auto anim : m_animatorComp->GetAnims())
			m_spriteComp->GetSprite().setTextureRect(m_animatorComp->GetAnimation(anim.first).uvRect);
	}

} }