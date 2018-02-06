#include "Splash.hpp"
#include "MainMenu.hpp"

#include <sstream>
#include <iostream>

namespace HJ {

	using namespace Engine;
	using namespace System;

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
		while (Renderer::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Renderer::GetWin().close();
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
		Renderer::Queue(&m_background);
	}

}