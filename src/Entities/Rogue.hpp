#ifndef ROGUE_ENTITY_H
#define ROGUE_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Rogue final : public Hero
	{
		public:
			Rogue(const std::string& t_sprite, const std::string& t_animator);
			~Rogue() = default;

			Rogue* GetType() override final;
			
			void Init() override final;

			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Attack() override final;
			void Skill(std::function<void()> t_func) override final;
			void Defend() override final;

		private:
			void TrueMark();
			void StormOfDaggers();
	};

} }

#endif // !ROGUE_ENTITY_H
