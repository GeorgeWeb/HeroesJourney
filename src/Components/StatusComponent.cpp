#include "StatusComponent.hpp"

#include <Engine/System/Renderer.hpp>

namespace HJ { namespace Components {

	using namespace Engine;

	sf::Vector2f spriteLayerOffset = sf::Vector2f(0.0f, -20.0f);

	StatusComponent::StatusComponent(ECM::Entity* t_parent)
		: ECM::Component(t_parent)
	{
		// initialize effects map

		// Create an empty texture
		sf::Texture tex;
		tex.create(16, 16);
		// create the effects
		auto stun = std::make_shared<Effect>();
		stun->SetSprite(tex, sf::Color::Red);
		auto frostResist = std::make_shared<Effect>();
		frostResist->SetSprite(tex, sf::Color::Cyan);
		auto dodgeAura = std::make_shared<Effect>();
		dodgeAura->SetSprite(tex, sf::Color::Blue);
		auto damageAura = std::make_shared<Effect>();
		damageAura->SetSprite(tex, sf::Color::Magenta);
		auto dodgeSkill = std::make_shared<Effect>();
		dodgeSkill->SetSprite(tex, sf::Color::Green);
		// add effects to the map
		m_effects.insert({ EFFECT_TYPE::STUN, stun });
		m_effects.insert({ EFFECT_TYPE::FROST_RESISTANCE, frostResist });
		m_effects.insert({ EFFECT_TYPE::DODGE_AURA, dodgeAura });
		m_effects.insert({ EFFECT_TYPE::DAMAGE_AURA, damageAura });
		m_effects.insert({ EFFECT_TYPE::DODGE_SKILL, dodgeSkill });

		independent = true;
	}

	StatusComponent* HJ::Components::StatusComponent::GetType()
	{
		return this;
	}

	void StatusComponent::Update(float t_deltaTime)
	{
		// set pos to the parent's one for ONLY non-independent sprite components
		if (m_parent->IsAlive())
		{
			offset.x = 0.0f;
			for (auto effectPair : m_effects)
			{
				auto type = effectPair.first;
				auto effect = effectPair.second;
				// set dependent (to parent Entity) position
				if (!independent)
					effect->sprite.setPosition(m_parent->GetPosition());
				
				// postion effects
				// effect->sprite.setPosition(m_parent->GetPosition());
				effect->sprite.setPosition(m_parent->GetPosition() + spriteLayerOffset + offset);
				if (effect->active)
				{
					unsigned int padding = (type == EFFECT_TYPE::STUN) ? 25.0f : 5.0f;
					offset.x += effect->sprite.getGlobalBounds().width + padding;
				}

				// set smoothness to the textures applied to each sprite
				if (effect->sprite.getTexture() != nullptr && !effect->sprite.getTexture()->isSmooth())
					const_cast<sf::Texture*>(effect->sprite.getTexture())->setSmooth(true);
			}
		}
	}

	void StatusComponent::Render()
	{
		if (m_parent->IsVisible())
		{
			for (auto effectPair : m_effects)
			{
				auto effect = effectPair.second;
				if (effect->active)
					System::Renderer::Queue(&(effect->sprite));
			}
		}
	}

	void StatusComponent::SetEffect(EFFECT_TYPE t_type, bool t_active)
	{
		auto effect = m_effects.find(t_type)->second;
		effect->active = t_active;
	}


} }