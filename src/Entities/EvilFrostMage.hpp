#ifndef EVIL_FROST_MAGE_H
#define EVIL_FROST_MAGE_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/AnimatorComponent.hpp>

#include "EvilAI.hpp"

namespace HJ { namespace Entities {

		class EvilFrostMage final : public EvilAI
		{	
			public:
				EvilFrostMage();
				virtual ~EvilFrostMage() = default;

				EvilFrostMage* GetType() override final;

				void Init() override final;
				void Update(float t_deltaTime) override final;
				void Render() override final;
		};
	}
}

#endif // !EVIL_FROST_MAGE_H