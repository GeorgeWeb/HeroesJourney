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

	void Settings::SetVSync(bool t_vsync)
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
		std::cout << "Resolution: (" << m_screenWidth << ", " << m_screenHeight << ")" << std::endl;
		#endif
	}

	void Settings::SaveScreenOpts()
	{
		switch (m_screenMode)
		{
			default:
			case SCREEN_MODE::WINDOWED:
				Engine2D::GetWin().setSize(sf::Vector2u(m_screenWidth, m_screenHeight));
				Engine2D::SetVsync(m_hasVsync);
				break;

			case SCREEN_MODE::FULLSCREEN:
				Engine2D::GetWin().setSize(sf::Vector2u(m_screenWidth, m_screenHeight));
				Engine2D::SetVsync(m_hasVsync);
				break;
		}
	}

} }
