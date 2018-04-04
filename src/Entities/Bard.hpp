#ifndef  BARD_ENTITY_H
#define  BARD_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Bard final : public Hero
	{
		public:
			Bard(const std::string& t_sprite);
			Bard(const std::string& t_sprite, const std::string& t_animatior);
			~Bard() = default;

			Bard* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Attack(std::shared_ptr<EvilAI> t_enemy) override final;
			void Defend() override final;

			void UseSkill1(std::vector<std::shared_ptr<Hero>> t_heroes) override final;
			void UseSkill2(std::vector<std::shared_ptr<Hero>> t_heroes) override final;
	};

} }

#endif // ! BARD_ENTITY_H
