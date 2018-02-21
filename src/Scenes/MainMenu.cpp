#include "MainMenu.hpp"
#include "../DEFINITIONS.hpp"
#include "MapScene.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	using namespace Engine::Components;
	


	MainMenuScene::MainMenuScene(GameDataRef t_data)
		:m_data(t_data)
	{
		// Will not be used for more initialization
	}

	void MainMenuScene::Init()
	{
		m_data->assets.LoadTexture("Tex_MainBG", MAINMENU_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_Start", MAINMENU_STARTGAME_BUTTON);
		m_data->assets.LoadFont("Font_MainMenu", GAME_TITLE_FONT);

		//Entity manager to non-visible ents
		for (auto ent : m_data->ents.GetEntsDictionary()) ent.second->SetVisible(false);

		//Local entities map container
		std::map<std::string, std::shared_ptr<ECM::Entity>> ents;

		//Background
		auto bg = std::make_shared<ECM::Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_MainBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_MainBG"));
		bgSprite->GetSprite().setColor(sf::Color(128, 128, 128, 200));
		//properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		
		//Start button
		auto start_btn = std::make_shared<ECM::Entity>();
		auto startSprite = start_btn->AddComponent<SpriteComponent>("C_StartSprite");
		//define start button sprite
		startSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_Start"));
		startSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		start_btn->SetPosition(sf::Vector2f((SCREEN_WIDTH - startSprite->GetSprite().getGlobalBounds().width) * 0.5f, (SCREEN_HEIGHT - startSprite->GetSprite().getGlobalBounds().height) * 0.7f));

		start_btn->SetVisible(true);
		start_btn->SetAlive(true);

		//add to local ents map
		ents.insert_or_assign("E_Start", start_btn);
		ents.insert_or_assign("E_MainBG", bg);
		

		//:if entity is not in the entity manager, then add
		m_data->ents.PopulateEntsDictionary(ents);
	}

	void MainMenuScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Renderer::GetWin().close();

			auto startComp = m_data->ents.Find("E_Start")->GetComponent("C_StartSprite");

			if (m_data->input.isClicked(startComp->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				m_shouldFade = true;
				//make the button look clicked
				startComp->GetSprite().setColor(sf::Color(startComp->GetSprite().getColor().r,
					startComp->GetSprite().getColor().g,
					startComp->GetSprite().getColor().b,
					startComp->GetSprite().getColor().a - 50));
			}
		}
	}

	void MainMenuScene::Update(float t_delatTime)
	{
		auto bgSpriteComp = m_data->ents.Find("E_MainBG")->GetComponent("C_MainBGSprite");
		if (m_shouldFade)
		{
			auto fadedColor = sf::Color(bgSpriteComp->GetSprite().getColor().r,
				bgSpriteComp->GetSprite().getColor().g,
				bgSpriteComp->GetSprite().getColor().b,
				bgSpriteComp->GetSprite().getColor().a - t_delatTime*100.0f);
			
			bgSpriteComp->GetSprite().setColor(fadedColor);
			if (bgSpriteComp->GetSprite().getColor().a == 0)
			{
				m_shouldFade = false;

				//switch to map
				auto mapState = std::make_unique<MapScene>(MapScene(m_data));
				m_data->machine.AddState(std::move(mapState));
			}
		}
		m_data->ents.Update(t_delatTime);
	}

	void MainMenuScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();
	}
}