#ifndef  BARD_ENTITY_H
#define  BARD_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Bard final : public Hero
	{
		public:
			Bard();
			~Bard() = default;

			Bard* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;
	};

} }

#endif // ! BARD_ENTITY_H
