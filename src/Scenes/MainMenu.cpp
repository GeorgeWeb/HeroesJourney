#include "MainMenu.hpp"
#include "StoryIntro.hpp"
#include "../DEFINITIONS.hpp"
#include "MapScene.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;
	// engine/game component namespaces
	using namespace Engine::ECM;
	using namespace Engine::Components;
	using namespace HJ::Entities;
	
	MainMenuScene::MainMenuScene(GameDataRef t_data)
		: m_data(t_data)
	{
		// Will not be used for more initialization
	}

	void MainMenuScene::Init()
	{
		// Load resources
		m_data->assets.LoadTexture("Tex_MainBG", MAINMENU_SCENE_BACKGROUND);
		m_data->assets.LoadTexture("Tex_StartBtn", MAINMENU_STARTGAME_BUTTON);

		//Background
		auto bg = std::make_shared<Entity>();
		auto bgSprite = bg->AddComponent<SpriteComponent>("C_MainBGSprite");
		//define bg sprite
		bgSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_MainBG"));
		bgSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		bg->SetPosition(sf::Vector2f(0.0f, 0.0f));
		bg->SetVisible(true);
		bg->SetAlive(true);
		
		//Button
		auto mbtn = std::make_shared<ECM::Entity>();
		auto mbtnSprite = mbtn->AddComponent<SpriteComponent>("C_BtnSprite");
		//define bg sprite
		mbtnSprite->GetSprite().setTexture(m_data->assets.GetTexture("Tex_StartBtn"));
		mbtnSprite->GetSprite().setColor(sf::Color(255, 255, 255, 255));
		//properties
		mbtn->SetPosition(sf::Vector2f((SCREEN_WIDTH - mbtnSprite->GetSprite().getGlobalBounds().width) * 0.5f,
			(SCREEN_HEIGHT - mbtnSprite->GetSprite().getGlobalBounds().height) * 0.3f));
		mbtn->SetVisible(true);
		mbtn->SetAlive(true);

		//add to local ents map
		AddEntity("E_zMainBG", bg);
		AddEntity("E_xBtn", mbtn);
	}

	void MainMenuScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				Renderer::GetWin().close();

			auto btn = m_data->ents.Find<Entity>("E_xBtn")->GetComponent<SpriteComponent>("C_BtnSprite");
			if (m_data->input.isClicked(btn->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				////switch to story introduction
				//auto storyIntro = std::make_unique<StoryIntroScene>(StoryIntroScene(m_data));
				//m_data->machine.AddState(std::move(storyIntro));

				//switch to map
				auto mapState = std::make_unique<MapScene>(MapScene(m_data));
				m_data->machine.AddState(std::move(mapState));
			}
		}
	}

	void MainMenuScene::Update(float t_delatTime)
	{
		m_data->ents.Update(m_entities, t_delatTime);
	}

	void MainMenuScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render(m_entities);
	}

	void MainMenuScene::AddEntity(const std::string& t_name, std::shared_ptr<Entity> t_entity)
	{
		State::AddEntity(t_name, t_entity);
		// Add to global entities container
		m_data->ents.Save(t_name, t_entity);
	}
}