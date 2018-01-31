#include "MainGameMap.hpp"
#include "../DEFINITIONS.hpp"

#include <sstream>
#include <iostream>

namespace HeroesJourney {

	using namespace Engine;

	MainGameMapScene::MainGameMapScene(GameDataRef t_data)
		: m_data(t_data)
	{
		// Won't use for more initialization, hence I will use the Init() func
	}

	void MainGameMapScene::Init()
	{
		// load & set background texture
		m_data->assets.LoadTexture("Main Game Background", MAIN_GAME_SCENE_BACKGROUND);
		m_background.setTexture(m_data->assets.GetTexture("Main Game Background"));
	}

	void MainGameMapScene::HandleInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				m_data->window.close();

			// Switch scenes (to Main Menu) on startBtn left mouse click
			if (m_data->input.isSpriteClicked(m_background, sf::Mouse::Left, m_data->window))
				std::cout << "Oh, hi Mark!\n";
		}
	}

	void MainGameMapScene::Update(float t_delatTime)
	{
		// Do sth (e.g. well... the game logic, bruh)
	}

	void MainGameMapScene::Draw(float t_deltaTime)
	{
		m_data->window.clear();

		m_data->window.draw(m_background);

		m_data->window.display();
	}

}