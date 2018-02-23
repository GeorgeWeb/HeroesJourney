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
		float m_time = 0.1f;

		std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;
		

	public:
		Building() = delete;
		Building(const std::string& t_sprite);
		virtual ~Building() = default;

		Building* GetType() override;

		virtual void Init(const sf::Texture& t_texture);

		virtual void Update(float t_deltaTime);
		virtual void Render();
		void Upgrade();

		void SetSprite(const sf::Texture& t_texture);

		bool isClicked;
		bool unClick;



	};


} }
#endif // ! BUILDING_ENTITY_H
