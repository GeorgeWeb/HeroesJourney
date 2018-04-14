#include "StatusComponent.hpp"
#include <Engine/Engine.hpp>
#include "../DEFINITIONS.hpp"

namespace HJ { namespace Components {

	using namespace Engine;

	sf::Vector2f spriteLayerOffset = sf::Vector2f(0.0f, -30.0f);
	sf::Texture StatusComponent::stunTex;
	sf::Texture StatusComponent::defendTex;
	sf::Texture StatusComponent::dmgAuraTex;
	sf::Texture StatusComponent::armAuraTex;
	sf::Texture StatusComponent::frostAuraTex;
	sf::Texture StatusComponent::frostArmTex;
	sf::Texture StatusComponent::enrageTex;
	sf::Texture StatusComponent::flyTex;
	sf::Texture StatusComponent::magicImuneTex;
	sf::Texture StatusComponent::multiTargetTex;

	StatusComponent::StatusComponent(ECM::Entity* t_parent)
		: ECM::Component(t_parent)
	{
		// -- Initialize effects map -- //
		stunTex.loadFromFile(STUN_EFFECT);
		defendTex.loadFromFile(DEFEND_EFFECT);
		dmgAuraTex.loadFromFile(DAMAGE_AURA_EFFECT);
		armAuraTex.loadFromFile(ARMOUR_AURA_EFFECT);
		frostAuraTex.loadFromFile(FROST_AURA_EFFECT);
		frostArmTex.loadFromFile(FROST_ARMOUR_EFFECT);
		enrageTex.loadFromFile(ENRAGE_EFFECT);
		flyTex.loadFromFile(FLYING_EFFECT);
		magicImuneTex.loadFromFile(MAGIC_IMUNITY_EFFECT);
		multiTargetTex.loadFromFile(MULTI_TARGET_EFFECT);
		// create the effects using the texture paths
		m_effects[EFFECT_TYPE::STUN] = std::make_shared<Effect>(stunTex);
		m_effects[EFFECT_TYPE::FROST_ARMOR] = std::make_shared<Effect>(frostArmTex);
		m_effects[EFFECT_TYPE::ARMOUR_AURA] = std::make_shared<Effect>(armAuraTex);
		m_effects[EFFECT_TYPE::DAMAGE_AURA] = std::make_shared<Effect>(dmgAuraTex);
		m_effects[EFFECT_TYPE::FROST_AURA] = std::make_shared<Effect>(frostAuraTex);
		m_effects[EFFECT_TYPE::DEFEND] = std::make_shared<Effect>(defendTex);
		m_effects[EFFECT_TYPE::ENRAGE] = std::make_shared<Effect>(enrageTex);
		m_effects[EFFECT_TYPE::FLY] = std::make_shared<Effect>(flyTex);
		m_effects[EFFECT_TYPE::MAGIC_IMUNITY] = std::make_shared<Effect>(magicImuneTex);
		m_effects[EFFECT_TYPE::MULTIPLE_TARGET] = std::make_shared<Effect>(multiTargetTex);
		// set the component to be indepent (position wise) from its parent
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
					effect->sprite->setPosition(m_parent->GetPosition());
				
				// postion effects
				effect->sprite->setPosition(m_parent->GetPosition() + spriteLayerOffset + offset);
				if (effect->active)
				{
					unsigned int padding = (type == EFFECT_TYPE::STUN) ? 25.0f : 5.0f;
					offset.x += effect->sprite->getGlobalBounds().width + padding;
				}

				// set smoothness to the textures applied to each sprite
				if (effect->sprite->getTexture() != nullptr && !effect->sprite->getTexture()->isSmooth())
					const_cast<sf::Texture*>(effect->sprite->getTexture())->setSmooth(true);
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
					System::Renderer::Queue(&(*effect->sprite));
					// Engine2D::GetWin().draw(*effect->sprite);
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
			return effect->second;
		else
			return nullptr;
	}


} }