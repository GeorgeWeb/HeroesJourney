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

		class EvilFrostMage final : public EvilAI
		{	
			public:
				EvilFrostMage(const std::string& t_sprite);
				EvilFrostMage(const std::string& t_sprite, const std::string& t_animator);
				virtual ~EvilFrostMage() = default;

				EvilFrostMage* GetType() override final;

				void Init() override final;
				void Update(float t_deltaTime) override final;
				void Render() override final;

				void Attack() override final;
				void Skill(std::function<void()> t_func) override final;
				void Defend() override final;
		};
	}
}

#endif // !EVIL_FROST_MAGE_H