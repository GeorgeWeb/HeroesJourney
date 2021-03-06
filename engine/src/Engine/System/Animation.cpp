#include "Animation.hpp"

namespace Engine { namespace System {

	Animation::Animation(sf::Texture* t_texture, sf::Vector2u t_imgCount, float t_switchTime, bool t_right, bool t_loop) :
		m_imageCount(t_imgCount),
		m_switchTime(t_switchTime),
		m_totalTime(0.0f),
		m_faceRight(t_right),
		m_play(true),
		m_loop(t_loop)
	{
		m_currentImage.x = 0;
		uvRect.width  = t_texture->getSize().x / m_imageCount.x;
		uvRect.height = t_texture->getSize().y / m_imageCount.y;
	}

	void Animation::Update(float t_deltaTime)
	{
		m_currentImage.y = m_row;
		m_incrementRows = m_loop;
		m_totalTime += t_deltaTime;

		if (m_totalTime >= m_switchTime)
		{
			m_totalTime -= m_switchTime;
			m_currentImage.x++;

			// clamping
			if (m_currentImage.x >= m_imageCount.x)
			{
				m_currentImage.x = 0;
				if (m_imageCount.y > 0)
				{
					if (m_currentImage.y >= m_imageCount.y - 1)
					{
						if (m_loop)
						{
							m_currentImage.x = 0;
							m_currentImage.y = m_row = 0;
						}
						else
						{
							m_currentImage.x = m_imageCount.x;
							m_currentImage.y = m_imageCount.y;
						}
						
						m_play = m_loop;
					}
					else
					{
						m_row = (m_incrementRows) ? m_row + 1 : m_imageCount.y - 1;
					}
				}
			}
		}

		// texture direction facing
		if (m_play)
		{
			uvRect.top = m_currentImage.y * uvRect.height;

			if (m_faceRight)
			{
				uvRect.left = m_currentImage.x * uvRect.width;
				uvRect.width = abs(uvRect.width);
			}
			else
			{
				uvRect.left = (m_currentImage.x + 1) * abs(uvRect.width);
				uvRect.width = -abs(uvRect.width);
			}
		}
	}

} }