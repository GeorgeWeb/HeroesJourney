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

			virtual const std::string className() const { return "Rogue"; }
			
			void Init() override final;

			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Attack(std::shared_ptr<EvilAI> t_enemy) override final;
			void Defend() override final;
			
			void UseSkill1(std::shared_ptr<EvilAI> t_enemy) override final;
			void UseSkill2(std::shared_ptr<EvilAI> t_enemy) override final;
	};

} }

#endif // !ROGUE_ENTITY_H
