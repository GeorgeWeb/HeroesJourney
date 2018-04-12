#include "Settings.hpp"
#include "../Engine.hpp"
#include <iostream>

#define NDEBUG 1

namespace Engine { namespace System {

	void Settings::Save()
	{
		// IF screen changes && audio
		// Apply audio -> screen
		// ELSE IF screen changes && !audio changes
		// Apply screen only
		// ELSE IF !screen changes && audio changes
		// Apply audio only
		// ELSE (!screen && !audio)
		// Do Not do anything
		
		SaveScreenOpts();
	}

	void Settings::SetScreenMode(const SCREEN_MODE& t_mode)
	{
		m_screenMode = t_mode;
		#if NDEBUG
		std::cout << "Mode: " << m_screenMode << std::endl;
		#endif
	}

	void Settings::SetResolution(unsigned int t_width, unsigned int t_height)
	{
		m_screenWidth = t_width;
		m_screenHeight = t_height;
		#if NDEBUG
		std::cout << "Resolution from settings: (" << m_screenWidth << ", " << m_screenHeight << ")" << std::endl;
		#endif
	}

	void Settings::SaveScreenOpts()
	{
		// screen resolution
		if (m_screenMode == SCREEN_MODE::WINDOWED)
		{
			// reset game window
			Engine2D::window->create(sf::VideoMode(m_screenWidth, m_screenHeight), Engine2D::title,
				sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
			// Hide default cursor
			Engine2D::window->setMouseCursorVisible(false);
			// window size reset with the changed res
			// set ratios
			int newH = (1366 * m_screenHeight) / m_screenWidth;
			int displace = (newH - 768) / (-2);
			Engine2D::window->setView(sf::View(sf::FloatRect(0, displace, 1366, newH)));
			// init. renderer
			Renderer::Initialize(*Engine2D::window);

		}
		else if (m_screenMode == SCREEN_MODE::FULLSCREEN)
		{
			// reset game window
			Engine2D::window->create(sf::VideoMode(m_screenWidth, m_screenHeight), Engine2D::title, sf::Style::Fullscreen);
			// Hide default cursor
			Engine2D::window->setMouseCursorVisible(false);
			// window size reset with the changed res
			// set ratios
			int newH = (1366 * m_screenHeight) / m_screenWidth;
			int displace = (newH - 768) / (-2);
			Engine2D::window->setView(sf::View(sf::FloatRect(0, displace, 1366, newH)));
			// init. renderer
			Renderer::Initialize(*Engine2D::window);
		}
	}

} }
