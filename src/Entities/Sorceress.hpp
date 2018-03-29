#ifndef  SORCERESS_ENTITY_H
#define  SORCERESS_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Sorceress final : public Hero
	{
		public:
			Sorceress(const std::string& t_sprite);
			Sorceress(const std::string& t_sprite, const std::string& t_animatior);
			~Sorceress() = default;

			Sorceress* GetType() override final;

			void Init() override final;

			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Attack() override final;
			void Skill(std::function<void()> t_func) override final;
			void Defend() override final;

		private:
			void StreamOfFire();
			void Ignite();
	};

} }
#endif // ! SORCERESS_ENTITY_H
