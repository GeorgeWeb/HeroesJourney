#ifndef EVIL_FROST_MAGE_H
#define EVIL_FROST_MAGE_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>

#include "EvilAI.hpp"

#include <functional>

namespace HJ { namespace Entities {

		enum EvilMageBehaviour
		{
			// derived
			ATTACK = AIBehaviour::BASE_ATTACK,
			DEFEND = AIBehaviour::BASE_DEFEND,
			DIE = AIBehaviour::BASE_DIE,
			// new
			FROST_STORM,
			ICY_BURST
		};

		class EvilFrostMage : public EvilAI
		{	
			public:
				// EvilFrostMage();
				EvilFrostMage(const std::string& t_sprite, const std::string& t_animator);
				virtual ~EvilFrostMage() = default;

				void Init(const sf::Texture& t_texture, sf::IntRect t_texRect) override;

				void Update(float t_deltaTime) override;
				void Render() override;

				void Attack() override;
				void Skill(std::function<void()> t_func) override;
				void Defend() override;
		};
	}
}

#endif // !EVIL_FROST_MAGE_H