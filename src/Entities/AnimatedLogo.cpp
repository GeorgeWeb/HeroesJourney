#include "AnimatedLogo.hpp"
#include "../DEFINITIONS.hpp"

using namespace Engine::ECM;
using namespace Engine::Components;

namespace HJ { namespace Entities {

		AnimatedLogo::AnimatedLogo() :
			m_spriteComp(AddComponent<Engine::Components::SpriteComponent>("C_AnimLogoSprite")),
			m_animatorComp(AddComponent<Engine::Components::AnimatorComponent>("C_AnimLogoAnimator"))
		{ }

		std::shared_ptr<Engine::Components::SpriteComponent> AnimatedLogo::GetSpriteComponent()
		{
			return m_spriteComp;
		}

		std::shared_ptr<Engine::Components::AnimatorComponent> AnimatedLogo::GetAnimatorComponent()
		{
			return m_animatorComp;
		}

		void AnimatedLogo::Update(float t_deltaTime)
		{
			Entity::Update(t_deltaTime);
		}

		void AnimatedLogo::Render()
		{
			Entity::Render();
		}

		void AnimatedLogo::SetSprite(const sf::Texture& t_texture, sf::IntRect t_texRect)
		{
			m_spriteComp->GetSprite().setTexture(t_texture);
			m_spriteComp->GetSprite().setTextureRect(t_texRect);
		}

		void AnimatedLogo::Animate()
		{
			for (auto anim : m_animatorComp->GetAnims())
				m_spriteComp->GetSprite().setTextureRect(m_animatorComp->GetAnimation(anim.first).uvRect);
		}

} }