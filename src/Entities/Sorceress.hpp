#ifndef  SORCERESS_ENTITY_H
#define  SORCERESS_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Sorceress final : public Hero
	{
		public:
			Sorceress();
			~Sorceress() = default;

			Sorceress* GetType() override final;

			virtual const std::string className() const { return "Sorceress"; }

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;
	};

} }
#endif // ! SORCERESS_ENTITY_H
