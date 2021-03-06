#ifndef BUILDING_ENTITY_H
#define BUILDING_ENTITY_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/ClickableComponent.hpp>
#include "Hero.hpp"

namespace HJ {	namespace Entities {

	class Building : public Engine::ECM::Entity 
	{
		protected:
			int m_bonus = 0;
			int m_level = 1;
			sf::Clock m_clock;
			float m_time;

			std::shared_ptr<Engine::Components::SpriteComponent> m_spriteComp;
			std::shared_ptr<Engine::Components::ClickableComponent> m_clickComp;

		public:
			std::shared_ptr<Engine::Components::SpriteComponent> GetSpriteComponent();
			std::shared_ptr<Engine::Components::ClickableComponent> GetClickableComponent();
		public:
			Building(bool t_populate = true);
			virtual ~Building() = default;

			virtual Building* GetType() override;
			
			inline int GetLevel() const { return m_level; }
			inline void SetLevel(int t_level) { m_level = t_level; }

			inline int GetBonus() const { return m_bonus; }

			virtual void Init() override;
			virtual void Update(float t_deltaTime) override;
			virtual void Render() override;

			virtual void Upgrade();
			virtual void ApplyBonus(std::vector<std::shared_ptr <Hero>> t_heroes);
			
			void SetSprite(const sf::Texture& t_texture);

		
	};

} }
#endif // !BUILDING_ENTITY_H
