#include "Building.hpp"

namespace HJ {	namespace Entities {

	Building::Building(const std::string& t_sprite) :
		m_spriteComp(AddComponent<Engine::Components::SpriteComponent>(t_sprite))
	{ }

	Building* Building::GetType()
	{
		return this;
	}

	void Building::Init()
	{
		m_spriteComp->GetSprite().scale(sf::Vector2f(1.0f, 1.0f));
		m_spriteComp->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		m_time = 0.1f;

		SetVisible(true);
		SetAlive(true);
	}

	void Building::Update(float t_deltaTime)
	{
		Entity::Update(t_deltaTime);
		
		// check if the building's sprite is clicked and react
		// ...
	}

	void Building::Render()
	{
		Entity::Render();
	}

	void Building::SetSprite(const sf::Texture& t_texture)
	{
		m_spriteComp->GetSprite().setTexture(t_texture);
	}

	void Building::Upgrade()
	{
		// TODO: upgrade change texture and bonus if upgraded
	}

} }