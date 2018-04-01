#include "Game.hpp"
#include "Scenes/Splash.hpp"

namespace HJ {

	using namespace Engine;
	using namespace System;

	Game::Game(unsigned int t_width, unsigned int t_height, const std::string& t_title, bool t_vsync) : 
		m_data(std::make_shared<GameData>()),
		m_deltaTime(1.0f / 60.0f)
	{	
		// create the game window
		sf::RenderWindow win(sf::VideoMode(t_width, t_height), t_title, 
			sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
		
		/* Change cursor (abstract in Engine2D class) */

		// Hide default cursor
		win.setMouseCursorVisible(false);

		// Load new cursor's texture and add to cursor sprite
		m_data->assets.LoadTexture("Tex_Cursor", CUSTOM_CURSOR_IMG);
		Engine2D::cursor.setTexture(m_data->assets.GetTexture("Tex_Cursor"));

		// set game title
		Engine2D::title = t_title;
		// set game window
		Engine2D::window = &win;
		// set window v-sync default(OFF)
		Engine2D::SetVsync(t_vsync);

		// init. renderer
		Renderer::Initialize(win);

		// init. game settigns
		m_data->settings.SetResolution(t_width, t_height);
		m_data->settings.SetScreenMode(SCREEN_MODE::WINDOWED);
		m_data->settings.SetVSyncOn(t_vsync);

		// save the initialized game settings
		m_data->settings.Save();

		// add first state/screen
		auto initState = std::make_unique<SplashScene>(SplashScene(m_data));
		m_data->machine.AddState(std::move(initState));
		
		// start the game loop
		GameLoop();
	}

	void Game::GameLoop()
	{
		float newTime, frameTime, interpolation;
		float currentTime = m_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (Engine2D::GetWin().isOpen())
		{
			// sate machine processes changes such as initializing/changing/removing state (Scene)
			m_data->machine.ProcessStateChanges();

			// Calculate accumulator
			newTime = m_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
				frameTime = 0.25f;

			currentTime = newTime;
			accumulator += frameTime;

			/* Frame rate independent Game Update */

			// Integration (euler semi-implicit)
			while (accumulator >= m_deltaTime)
			{
				// Calc. FPS & append it to the game title
				Engine2D::DisplayFPS();
				
				// handle input & Update scene
				m_data->machine.GetActiveState()->HandleInput();
				m_data->machine.GetActiveState()->Update(m_deltaTime);
				
				// Update cursor
				Engine2D::cursor.setPosition(m_data->input.GetMousePositionToWorld(Engine2D::GetWin()));

				accumulator -= m_deltaTime;
			}

			// calculate interpolation time based on the accumulator and delta time
			// for better frame rate independent draw
			interpolation = accumulator / m_deltaTime;

			/* Draw game assets */

			// clear buffers (color)
			Engine2D::GetWin().clear(sf::Color::Black);
			
			// flush screen
			Engine2D::Render();

			// DO THE RENDERING FOR THE ACTIVE SCENE!
			m_data->machine.GetActiveState()->Draw(interpolation);	
			
			// Draw cursor
			Engine2D::GetWin().draw(Engine2D::cursor);

			// display the window
			Engine2D::GetWin().display();
		}

		// empty the Renderer queue
		Renderer::Shutdown();
	}

}