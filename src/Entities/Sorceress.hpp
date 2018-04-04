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

			void Attack(std::shared_ptr<EvilAI> t_enemy) override final;
			void Defend() override final;

			void UseSkill1(std::shared_ptr<EvilAI> t_enemy) override final;
			void UseSkill2(std::shared_ptr<EvilAI> t_enemy) override final;
	};

} }
#endif // ! SORCERESS_ENTITY_H
