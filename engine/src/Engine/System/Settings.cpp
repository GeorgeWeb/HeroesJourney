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

	void Settings::SetVSyncOn(bool t_vsync)
	{
		m_hasVsync = t_vsync;
		#if NDEBUG
		std::cout << "V-Sync: " << m_hasVsync << std::endl;
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
			Engine2D::window->create(sf::VideoMode(1366, 768), Engine2D::title, 
				sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
			// Hide default cursor
			Engine2D::window->setMouseCursorVisible(false);
			// window size reset with the changed res
			// Engine2D::GetWin().setSize(sf::Vector2u(m_screenWidth, m_screenHeight));
			Renderer::Initialize(*Engine2D::window);
			Engine2D::window->setSize(sf::Vector2u(m_screenWidth, m_screenHeight));
			// init. game settigns
			SetResolution(m_screenWidth, m_screenHeight);
			// SetScreenMode(SCREEN_MODE::WINDOWED);
			// SetVSyncOn(m_hasVsync);
		}
		else if (m_screenMode == SCREEN_MODE::FULLSCREEN)
		{
			// reset game window
			Engine2D::window->create(sf::VideoMode(1366, 768), Engine2D::title, sf::Style::Fullscreen);
			// Hide default cursor
			Engine2D::window->setMouseCursorVisible(false);
			// window size reset with the changed res
			// init. renderer
			Renderer::Initialize(*Engine2D::window);
			// init. game settigns
			SetResolution(m_screenWidth, m_screenHeight);
			// SetScreenMode(SCREEN_MODE::WINDOWED);
			// SetVSyncOn(m_hasVsync);
		}

		// v-sync on?
		Engine2D::SetVsync(m_hasVsync);
	}

} }
