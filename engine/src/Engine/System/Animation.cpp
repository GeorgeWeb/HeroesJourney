#include "Animation.hpp"

namespace Engine { namespace System {

	Animation::Animation(sf::Texture* t_texture, sf::Vector2u t_imgCount, float t_switchTime) :
		m_imageCount(t_imgCount),
		m_switchTime(t_switchTime),
		m_totalTime(0.0f)
	{
		m_currentImage.x = 0;
		uvRect.width  = t_texture->getSize().x / static_cast<float>(m_imageCount.x);
		uvRect.height = t_texture->getSize().y / static_cast<float>(m_imageCount.y);
	}

	void Animation::Update(float t_deltaTime)
	{
		SetRow(); // sets m_row , default is 1
		m_currentImage.y = m_row;
		m_totalTime += t_deltaTime;

		if (m_totalTime >= m_switchTime)
		{
			m_totalTime -= m_switchTime;
			m_currentImage.x++;
			
			// clamping
			if (m_currentImage.x >= m_imageCount.x)
			{
				m_currentImage.x = 0;
			}
		}

		uvRect.left = m_currentImage.x * uvRect.width;
		uvRect.top = m_currentImage.y * uvRect.height;
	}

} }