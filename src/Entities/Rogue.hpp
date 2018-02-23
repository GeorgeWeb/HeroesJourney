#ifndef ROGUE_ENTITY_H
#define ROGUE_ENTITY_H

#include "Hero.hpp"

namespace HJ {
	namespace Entities {

		class Rogue final : public Hero
		{
			public:
				Rogue(const std::string& t_sprite, const std::string& t_animator);
				~Rogue() = default;

				Rogue* GetType() override;
			
				void Init(const sf::Texture& t_texture, sf::IntRect t_texRect) override;

				void Update(float t_deltaTime) override;
				void Render() override;

				void Attack() override;
				void Skill(std::function<void()> t_func) override;
				void Defend() override;

			private:
				void TrueMark();
				void StormOfDaggers();
		};

	}
}

#endif // !ROGUE_ENTITY_H
