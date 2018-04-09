#ifndef ROGUE_ENTITY_H
#define ROGUE_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Rogue final : public Hero
	{
		public:
			Rogue();
			~Rogue() = default;

			Rogue* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;
	};

} }

#endif // !ROGUE_ENTITY_H
