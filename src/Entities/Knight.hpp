#ifndef KNIGHT_ENTITY_H
#define KNIGHT_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Knight final : public Hero
	{
		public:
			Knight(const std::string& t_sprite, const std::string& t_animator);
			~Knight() = default;

			Knight* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Attack() override final;
			void Skill(std::function<void()> t_func) override final;
			void Defend() override final;

		private:
			void HeroSlash();
			void ShoulderBash();
	};

} }

#endif // !KNIGHT_ENTITY_H
