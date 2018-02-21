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

			void Init(const sf::Texture& t_texture, sf::IntRect t_texRect) override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void Attack(std::shared_ptr<Entity> t_entity) override;
			void Skill(const std::function<void(std::shared_ptr<Entity> t_entity)>& t_func) override;
			void Defend() override;

		private:
			void TrueMark();
			void StormOfDaggers();
		};

	}
}

#endif // !ROGUE_ENTITY_H
