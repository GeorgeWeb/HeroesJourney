#include "Building.hpp"

namespace HJ {	namespace Entities {
	
	Building::Building(bool t_populate) :
		m_spriteComp(AddComponent<Engine::Components::SpriteComponent>("C_BuildingSprite")),
		m_clickComp(AddComponent<Engine::Components::ClickableComponent>("C_BuildingClick"))
	{
		m_clickComp->SetSpriteTarget(m_spriteComp.get());
	}

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

	void Building::ApplyBonus(std::vector<std::shared_ptr<Hero>> t_heroes)
	{
		//
	}

	std::shared_ptr<Engine::Components::SpriteComponent>Building::GetSpriteComponent()
	{
		return m_spriteComp;
	}

	std::shared_ptr<Engine::Components::ClickableComponent>Building::GetClickableComponent()
	{
		return m_clickComp;
	}

} }