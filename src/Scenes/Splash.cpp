#include "Splash.hpp"
#include "MainMenu.hpp"

#include "../DEFINITIONS.hpp"

#include <sstream>
#include <iostream>

namespace HeroesJourney {

	using namespace Engine;

	SplashScene::SplashScene(GameDataRef t_data)
		: m_data(t_data)
	{
		// Won't use for more initialization, hence I will use the Init() func
	}

	void SplashScene::Init()
	{
		m_data->assets.LoadTexture("Splash Background", SPLASH_SCENE_BACKGROUND);
		m_background.setTexture(m_data->assets.GetTexture("Splash Background"));
	}

	void SplashScene::HandleInput()
	{
		sf::Event event;
		while (m_data->window.pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				m_data->window.close();
		}
	}

	void SplashScene::Update(float t_delatTime)
	{
		if (m_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
		{
			// Switch scenes (to Main Menu)
			auto mainMenuState = std::make_unique<MainMenuScene>(MainMenuScene(m_data));
			m_data->machine.AddState(std::move(mainMenuState));
		}
	}

	void SplashScene::Draw(float t_deltaTime)
	{
		m_data->window.clear(sf::Color::Black);

		m_data->window.draw(m_background);

		m_data->window.display();
	}

}