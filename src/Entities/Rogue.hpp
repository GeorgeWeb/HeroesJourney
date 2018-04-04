#ifndef ROGUE_ENTITY_H
#define ROGUE_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Rogue final : public Hero
	{
		public:
			Rogue(const std::string& t_sprite);
			Rogue(const std::string& t_sprite, const std::string& t_animator);
			~Rogue() = default;

			Rogue* GetType() override final;
			
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
