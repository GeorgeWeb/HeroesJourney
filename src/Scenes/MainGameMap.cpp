#include "MainGameMap.hpp"
#include "PauseMenu.hpp"

#include <sstream>
#include <iostream>

namespace HJ {

	using namespace Engine;
	using namespace System;
	
	MainGameMapScene::MainGameMapScene(GameDataRef t_data)
		: m_data(t_data)
	{
		// Won't use for more initialization, hence I will use the Init() func
	}

	void MainGameMapScene::Init()
	{
		// load & set background texture
		m_data->assets.LoadTexture("MainGameBG", MAIN_GAME_SCENE_BACKGROUND);
		m_background.setTexture(m_data->assets.GetTexture("MainGameBG"));
	}

	void MainGameMapScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Renderer::GetWin().close();

			// Switch scenes (to Main Menu) on startBtn left mouse click
			//if (m_data->input.isClicked(m_background, sf::Mouse::Left, m_data->window))
				//std::cout << "Oh, hi Mark!\n";

			// Pause this screen and show Pause Screen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
			{
				m_background.setTexture(m_data->assets.GetTexture("MainMenuBG"));
				
				auto pauseMenuState = std::make_unique<PauseMenuScene>(PauseMenuScene(m_data));
				m_data->machine.AddState(std::move(pauseMenuState), false);
			}
		}
	}

	void MainGameMapScene::Update(float t_delatTime)
	{
		// Do sth (e.g. well... the game logic, bruh)
		Entity::EntityManager::getInstance().Update(t_delatTime);
	}

	void MainGameMapScene::Draw(float t_deltaTime)
	{
		Renderer::Queue(&m_background);
		Renderer::Queue(&GetEntity("StartBtn")->GetShape());
	}

}