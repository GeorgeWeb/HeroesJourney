#ifndef  BARD_ENTITY_H
#define  BARD_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Bard final : public Hero
	{
		public:
			Bard(const std::string& t_sprite, const std::string& t_animatior);
			~Bard() = default;

			Bard* GetType() override;

			void Init(const sf::Texture& t_texture, sf::IntRect t_texRect) override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void Attack() override;
			void Skill(std::function<void()> t_func) override;
			void Defend() override;

		private:
			void SoothingSong();
			void HymnOfCharge();
	};

} }

#endif // ! BARD_ENTITY_H
