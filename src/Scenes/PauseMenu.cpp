#include "PauseMenu.hpp"
#include "Splash.hpp"

#include <sstream>
#include <iostream>

#include <Engine/ECM/Components/TextComponent.hpp>
#include <Engine/ECM/Components/SpriteComponent.hpp>

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;

	PauseMenuScene::PauseMenuScene(GameDataRef t_data)
		: m_data(t_data)
	{
		// Won't use for more initialization, hence I will use the Init() func
	}

	void PauseMenuScene::Init()
	{
		// Restore entity manager to non-visible ents
		for (auto ent : m_data->ents.GetEntsDictionary()) ent.second->SetVisible(false);
		
		// load & set title font type
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
		

		// Create entities ...
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

		ents.insert_or_assign("E_aPauseMenuBG", bg);
		ents.insert_or_assign("E_aPauseMenuTitle", title);

		// :if entity is not in the entity manager, then it will be added:
		m_data->ents.PopulateEntsDictionary(ents);
	}

	void PauseMenuScene::HandleInput()
	{
		sf::Event event;
		while (System::Renderer::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				System::Renderer::GetWin().close();

			// Resume to the last Game Screen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			{
				// Restore entity manager to non-visible ents
				m_data->machine.RemoveState();
			}
		}
	}

	void PauseMenuScene::Update(float t_delatTime)
	{
		m_data->ents.Update(t_delatTime);
	}

	void PauseMenuScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();
	}

}