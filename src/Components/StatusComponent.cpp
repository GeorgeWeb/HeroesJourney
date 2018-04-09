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
		stun->SetSprite(tex, sf::Color::White);
		auto frostArmour = std::make_shared<Effect>();
		frostArmour->SetSprite(tex, sf::Color::Cyan);
		auto armourAura = std::make_shared<Effect>();
		armourAura->SetSprite(tex, sf::Color::Yellow);
		auto damageAura = std::make_shared<Effect>();
		damageAura->SetSprite(tex, sf::Color::Magenta);
		auto frostAura = std::make_shared<Effect>();
		frostAura->SetSprite(tex, sf::Color::Blue);
		auto dodge = std::make_shared<Effect>();
		dodge->SetSprite(tex, sf::Color::Green);
		auto enrage = std::make_shared<Effect>();
		enrage->SetSprite(tex, sf::Color::Red);
		auto fly = std::make_shared<Effect>();
		fly->SetSprite(tex, sf::Color::Red);
		auto magicImune = std::make_shared<Effect>();
		magicImune->SetSprite(tex, sf::Color::Red);
		auto multiTarget = std::make_shared<Effect>();
		multiTarget->SetSprite(tex, sf::Color::Red);
		// add effects to the map
		m_effects[EFFECT_TYPE::STUN] = stun;
		m_effects[EFFECT_TYPE::FROST_ARMOR] = frostArmour;
		m_effects[EFFECT_TYPE::ARMOUR_AURA] = armourAura;
		m_effects[EFFECT_TYPE::DAMAGE_AURA] = damageAura;
		m_effects[EFFECT_TYPE::FROST_AURA] = frostAura;
		m_effects[EFFECT_TYPE::DODGE] = dodge;
		m_effects[EFFECT_TYPE::ENRAGE] = enrage;
		m_effects[EFFECT_TYPE::FLY] = fly;
		m_effects[EFFECT_TYPE::MAGIC_IMUNITY] = magicImune;
		m_effects[EFFECT_TYPE::MULTIPLE_TARGET] = multiTarget;

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

	std::shared_ptr<Effect> StatusComponent::GetEffect(EFFECT_TYPE t_type)
	{
		auto effect = m_effects.find(t_type);
		if (effect != m_effects.end())
		{
			std::cout << "FOUND!" << std::endl;
			return effect->second;
		}
		else
		{
			std::cout << "CAN'T FIND!" << std::endl;
			return nullptr;
		}
	}


} }