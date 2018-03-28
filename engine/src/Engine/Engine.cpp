#include "Engine.hpp"
#include <future>
#include <iostream>
#include <stdexcept>
#include <SFML/Graphics.hpp>

namespace Engine {

	using namespace System;

	std::string Engine2D::title;
	sf::RenderWindow* Engine2D::window;

	void Engine2D::Render()
	{
		Renderer::Render();
	}

	sf::Vector2u Engine2D::GetWinSize()
	{
		return window->getSize();
	}

	void Engine2D::SetVsync(bool t_vsync)
	{
		window->setVerticalSyncEnabled(t_vsync);
	}

	sf::RenderWindow& Engine2D::GetWin()
	{
		return *window;
	}
	
	float frametimes[256] = {};
	uint8_t ftc = 0;

	void Engine2D::DisplayFPS()
	{
		static sf::Clock clock;
		float dt = clock.restart().asSeconds();
		{
			frametimes[++ftc] = dt;
			static std::string avg = Engine2D::title + " #FPS: ";
			if (ftc % 60 == 0)
			{
				double davg = 0;
				for (const auto t : frametimes)
					davg += t;

				davg = 1.0 / (davg / 255.0);
				Engine2D::GetWin().setTitle(avg + toStrDecPt(2, davg));
			}
		}
	}

	namespace Timing {

		long long Now()
		{
			return std::chrono::high_resolution_clock::now()
				.time_since_epoch()
				.count();
		}

		long long Last()
		{
			auto n = Timing::Now();
			static auto then = Timing::Now();
			auto dt = n - then;
			then = n;
			return dt;
		}

	}

}