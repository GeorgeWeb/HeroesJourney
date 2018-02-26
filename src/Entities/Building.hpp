#ifndef  BUILDING_ENTITY_H
#define BUILDING_ENTITY_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include "../Game.hpp"

namespace HJ {	namespace Entities {

	class Building : public Engine::ECM::Entity 
	{
		protected:
			int m_bonus;
			int m_level;
			sf::Clock m_clock;
			float m_time;

			std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;

		public:
			Building() = delete;
			Building(const std::string& t_sprite);
			virtual ~Building() = default;

			virtual Building* GetType() override;

			virtual void Init() override;
			virtual void Update(float t_deltaTime) override;
			virtual void Render() override;

			virtual void Upgrade();
			
			void SetSprite(const sf::Texture& t_texture);

		public:
			bool isClicked;
			bool unClick;
	};

} }
#endif // !BUILDING_ENTITY_H
