#ifndef ENCOUNTER_POPUP_H
#define ENCOUNTER_POPUP_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/TextComponent.hpp>

#include <functional>

namespace HJ { namespace Entities {

	class EncounterPopup final : public Engine::ECM::Entity
	{
		private:
			std::shared_ptr<Engine::Components::SpriteComponent> m_bgSprite;
			std::shared_ptr<Engine::Components::SpriteComponent> m_btnSprite;
			std::shared_ptr<Engine::Components::SpriteComponent> m_opponentSprite;
			std::shared_ptr<Engine::Components::SpriteComponent> m_storySprite;
			std::shared_ptr<Engine::Components::TextComponent> m_titleText;

		public:
			EncounterPopup();
			~EncounterPopup() = default;

			void Update(float t_deltaTime) override;
			void Render() override;

			// setters
			void SetBackgroundImage(const sf::Texture& t_texture);
			void SetButtonImage(const sf::Texture& t_texture);
			void SetOpponentImage(const sf::Texture& t_texture);
			void SetStoryImage(const sf::Texture& t_texture);
			void SetTitleText(const std::string& t_text, const sf::Font t_font);
			
			// move the whole panel
			// void SetPosition(sf::Vector2f t_position);

			// custom behaviour on creation
			void OnCreate(std::function<void()> t_func);
			// custom behaviour on closing
			std::function<void()> OnClose;
	};

} }

#endif // !ENCOUNTER_POPUP_H
