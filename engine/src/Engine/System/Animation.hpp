#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

namespace Engine { namespace System {

	class Animation
	{
		private:
			sf::Vector2u m_imageCount; ///> x and y OR rows and cols :)
			sf::Vector2u m_currentImage;

			float m_totalTime;
			float m_switchTime;
			
			unsigned int m_row;
			bool m_faceRight;
			bool m_play;
			bool m_loop;
			bool m_incrementRows = true;

		public:
			explicit Animation(sf::Texture* t_texture, sf::Vector2u t_imgCount, float t_switchTime, bool t_right, bool t_loop = false);
			Animation(const Animation&) = default;
			Animation() = default;
			
			~Animation() = default;

			void Update(float t_deltaTime);

			inline void ExitLoop() { m_loop = (m_loop) ? false : m_loop; }

			inline unsigned int GetRow() const { return m_row; }
			inline void SetRow(unsigned int t_row = 0) { m_row = t_row; m_play = true; }
			inline void SetFaceRight(bool t_faceRight = false) { m_faceRight = t_faceRight; }

		public:
			sf::IntRect uvRect;
	};

} }

#endif // !ANIMATION_H
