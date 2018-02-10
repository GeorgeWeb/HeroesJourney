#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

namespace Engine { namespace System {

	class Animation
	{
		private:
			sf::Vector2u m_imageCount; // x and y OR rows and cols :)
			sf::Vector2u m_currentImage;

			float m_totalTime;
			float m_switchTime;
			
			int m_row;

		public:
			explicit Animation(sf::Texture* t_texture, sf::Vector2u t_imgCount, float t_switchTime);
			Animation() = default;
			~Animation() = default;

			void Update(float t_deltaTime);

			void SetRow(int t_row = 0) { m_row = t_row; }

		public:
			sf::IntRect uvRect;
	};

} }

#endif // !ANIMATION_H
