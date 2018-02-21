#ifndef KNIGHT_ENTITY_H
#define KNIGHT_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Knight final : public Hero
	{

		public:
			Knight(const std::string& t_sprite, const std::string& t_animator);
			~Knight() = default;

			void Init(const sf::Texture& t_texture, sf::IntRect t_texRect) override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void Attack() override;
			void Skill(std::function<void()> t_func) override;
			void Defend() override;

		private:
			void HeroSlash();
			void ShoulderBash();
	};

} }

#endif // !KNIGHT_ENTITY_H
