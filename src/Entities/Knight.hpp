#ifndef KNIGHT_ENTITY_H
#define KNIGHT_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Knight final : public Hero
	{
		public:
			Knight(bool t_populate = true);
			~Knight() = default;

			Knight* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;
	};

} }

#endif // !KNIGHT_ENTITY_H
