#ifndef KNIGHT_ENTITY_H
#define KNIGHT_ENTITY_H

#include "Hero.hpp"

namespace HJ { namespace Entities {

	class Knight final : public Hero
	{

		public:
			Knight(const std::string& t_sprite, const std::string& t_animator);
			virtual ~Knight() = default;

			virtual void Init(const sf::Texture& t_texture, sf::IntRect t_texRect);

			virtual void Update(float t_deltaTime);
			virtual void Render();

			virtual void Attack(std::shared_ptr<Entity> t_entity) ;
			virtual void Skill(const std::function<void(std::shared_ptr<Entity> t_entity)>& t_func);
			virtual void Defend();
	};

} }

#endif // !KNIGHT_ENTITY_H
