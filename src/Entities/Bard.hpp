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

			void Attack() override final;
			void Skill(std::function<void()> t_func) override final;
			void Defend() override final;

		private:
			void SoothingSong();
			void HymnOfCharge();
	};

} }

#endif // ! BARD_ENTITY_H
