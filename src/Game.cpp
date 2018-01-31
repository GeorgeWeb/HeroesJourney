#include "Game.hpp"
#include "Scenes/Splash.hpp"

namespace HeroesJourney {

	Game::Game(unsigned int t_width, unsigned int t_height, const std::string& t_title)
	{
		// init/create the game window
		m_data->window.create(sf::VideoMode(t_width, t_height), t_title, sf::Style::Close | sf::Style::Titlebar);

		// add first state/screen
		auto initState = std::make_unique<SplashScene>(SplashScene(m_data));
		m_data->machine.AddState(std::move(initState));

		// fire up the game !!! (#lit)
		Run();
	}

	void Game::Run()
	{
		float newTime, frameTime, interpolation;
		float currentTime = m_clock.getElapsedTime().asSeconds();
		float accumulator = 0.0f;

		while (m_data->window.isOpen())
		{
			m_data->machine.ProcessStateChanges();

			newTime = m_clock.getElapsedTime().asSeconds();
			frameTime = newTime - currentTime;

			if (frameTime > 0.25f)
				frameTime = 0.25f;

			currentTime = newTime;
			accumulator += frameTime;

			while (accumulator >= m_deltaTime)
			{
				m_data->machine.GetActiveState()->HandleInput();
				m_data->machine.GetActiveState()->Update(m_deltaTime);
				accumulator -= m_deltaTime;
			}

			interpolation = accumulator / m_deltaTime;
			m_data->machine.GetActiveState()->Draw(interpolation);
		}
	}

}