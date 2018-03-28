#include "PauseMenu.hpp"
#include "Splash.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/Components/TextComponent.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>

namespace HJ {

	using namespace Engine;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;

	PauseMenuScene::PauseMenuScene(GameDataRef t_data)
		: m_data(t_data)
	{
		InitSceneView();
	}

	void PauseMenuScene::Init()
	{
		// Background
		auto bg = std::make_shared<Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_PauseBGSprite");
		// define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_SplashBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 155));
		// set properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);

		// Title
		auto title = std::make_shared<Entity>();
		auto titleComp = title->AddComponent<TextComponent>("C_PauseMenuText");
		titleComp->GetText().setFont(m_data->assets.GetFont("Font_Pixel"));
		titleComp->GetText().setCharacterSize(72);
		titleComp->GetText().setString("PAUSE MENU");
		title->SetPosition(sf::Vector2f(
			(SCREEN_WIDTH * .5f) - (titleComp->GetText().getGlobalBounds().width * .5f),
			100.0f));
		title->SetAlive(true);
		title->SetVisible(true);

		AddEntity("E_aPauseMenuBG", bg);
		AddEntity("E_aPauseMenuTitle", title);
	}

	void PauseMenuScene::HandleInput()
	{
		sf::Event event;
		while (Engine2D::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Engine2D::GetWin().close();

			if (event.type == sf::Event::Resized)
				ResizeSceneView();

			// Resume to the last Game Screen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				m_data->machine.RemoveState();
		}
	}

	void PauseMenuScene::Update(float t_delatTime)
	{
		// manage screen's scene view on fixed time
		ResizeSceneView();

		m_data->ents.Update(m_entities, t_delatTime);
	}

	void PauseMenuScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void PauseMenuScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}

}