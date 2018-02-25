#include "MainMenu.hpp"
#include "MapScene.hpp"
#include "../DEFINITIONS.hpp"

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

		// Restore entity manager to non-visible ents
		for (auto ent : m_data->ents.GetEntsDictionary()) ent.second->SetVisible(false);

		// Declare local entities map container
		std::map<std::string, std::shared_ptr<Entity>> ents;

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
		mbtn->SetPosition(sf::Vector2f(0.0f, 0.0f));
		mbtn->SetVisible(true);
		mbtn->SetAlive(true);

		//add to local ents map
		ents.insert_or_assign("E_MainBG", bg);
		ents.insert_or_assign("E_MBtn", mbtn);
		
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

			auto btn = m_data->ents.Find<Entity>("E_MBtn")->GetComponent<SpriteComponent>("C_BtnSprite");
			if (m_data->input.isClicked(btn->GetSprite(), sf::Mouse::Left, Renderer::GetWin()))
			{
				//switch to map
				auto mapState = std::make_unique<MapScene>(MapScene(m_data));
				m_data->machine.AddState(std::move(mapState));
			}
		}

		// Resume to the last Game Screen
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
			this->m_data->machine.RemoveState();
	}

	void MainMenuScene::Update(float t_delatTime)
	{
		m_data->ents.Update(t_delatTime);
	}

	void MainMenuScene::Draw(float t_deltaTime)
	{
		m_data->ents.Render();
	}
}