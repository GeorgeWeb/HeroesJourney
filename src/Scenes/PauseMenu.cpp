#include "PauseMenu.hpp"
#include "MainGameMap.hpp"

#include <sstream>
#include <iostream>

namespace HJ {

	using namespace Engine;
	using namespace System;

	PauseMenuScene::PauseMenuScene(GameDataRef t_data)
		: m_data(t_data)
	{
		// Won't use for more initialization, hence I will use the Init() func
	}

	void PauseMenuScene::Init()
	{
		// load & set title font type
		m_data->assets.LoadFont("Main Menu Title Font", MAINMENU_TITLE_FONT);
		m_titleText.setFont(m_data->assets.GetFont("Main Menu Title Font"));
		m_titleText.setCharacterSize(72);
		m_titleText.setString("Heroes Journey");
		m_titleText.setPosition((SCREEN_WIDTH * .5f) - (m_titleText.getGlobalBounds().width * .5f), 100.0f);
	}

	void PauseMenuScene::HandleInput()
	{
		sf::Event event;
		while (Renderer::GetWin().pollEvent(event))
		{
			if (sf::Event::Closed == event.type)
				Renderer::GetWin().close();

			// Resume to the last Game Screen
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
				this->m_data->machine.RemoveState();
		}
	}

	void PauseMenuScene::Update(float t_delatTime)
	{
		// Do sth (e.g. animations)
	}

	void PauseMenuScene::Draw(float t_deltaTime)
	{
		Renderer::Queue(&m_titleText);
	}

}