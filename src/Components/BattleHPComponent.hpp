#ifndef BATTLE_HP_COMPONENT_H
#define BATTLE_HP_COMPONENT_H

#include <Engine/ECM/ECM.hpp>

#include "../Entities/Hero.hpp"
#include "../Entities/EvilAI.hpp"

namespace HJ { namespace Components {

	using namespace Engine;

	class BattleHPComponent final : public ECM::Component
	{
		public:
			BattleHPComponent() = delete;
			explicit BattleHPComponent(ECM::Entity* t_parent);

			void Update(float t_deltaTime) override;
			void Render() override;
	};

} }

#endif // !BATTLE_HP_COMPONENT_H
