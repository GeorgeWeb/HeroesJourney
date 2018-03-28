#include "Game.hpp"
#include "Scenes/Splash.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;

	Game::Game(unsigned int t_width, unsigned int t_height, const std::string& t_title) : 
		m_data(std::make_shared<GameData>()),
		m_deltaTime(1.0f / 60.0f)
	{	
		// create the game window
		sf::RenderWindow win(sf::VideoMode(t_width, t_height), t_title,
			sf::Style::Close | sf::Style::Resize | sf::Style::Titlebar);

		// set game title
		Engine2D::title = t_title;

		// set game window
		Engine2D::window = &win;

		// init. renderer
		Renderer::Initialize(win);

		// add first state/screen
		auto initState = std::make_unique<SplashScene>(SplashScene(m_data));
		m_data->machine.AddState(std::move(initState));

		GameLoop();
	}

	void Game::GameLoop()
	{
		float newTime, frameTime, interpolation;
		float currentTime = m_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (Engine2D::GetWin().isOpen())
		{
			m_data->machine.ProcessStateChanges();

			newTime = m_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
				frameTime = 0.25f;

			currentTime = newTime;
			accumulator += frameTime;

			// Integration -> movement and physics here:
			while (accumulator >= m_deltaTime)
			{
				// Calc. FPS & append it to the game title
				Engine2D::DisplayFPS();
				
				// handle input & Update scene
				m_data->machine.GetActiveState()->HandleInput();
				m_data->machine.GetActiveState()->Update(m_deltaTime);
				accumulator -= m_deltaTime;
			}

			// clear buffers (color)
			Engine2D::GetWin().clear(sf::Color::Black);

			// interpolate time for drawing
			interpolation = accumulator / m_deltaTime;
			
			// flush screen
			Engine2D::Render();

			// DO THE RENDERING FOR THE ACTIVE SCENE!
			m_data->machine.GetActiveState()->Draw(interpolation);	
		
			// display the window
			Engine2D::GetWin().display();
		}

		// empty the Renderer queue
		Renderer::Shutdown();
	}

}