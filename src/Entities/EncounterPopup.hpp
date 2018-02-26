#ifndef ENCOUNTER_POPUP_H
#define ENCOUNTER_POPUP_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/TextComponent.hpp>
#include <Engine/Input/InputManager.hpp>

#include <functional>

namespace HJ { namespace Entities {

	class EncounterPopup final : public Engine::ECM::Entity
	{
		private:
			std::shared_ptr<Engine::Components::SpriteComponent> m_bgSprite;
			std::shared_ptr<Engine::Components::SpriteComponent> m_closeBtnSprite;
			std::shared_ptr<Engine::Components::SpriteComponent> m_playBtnSprite;
			std::shared_ptr<Engine::Components::SpriteComponent> m_opponentSprite;
			std::shared_ptr<Engine::Components::SpriteComponent> m_storySprite;
			std::shared_ptr<Engine::Components::TextComponent> m_titleText;

			Engine::Input::InputManager m_encInput;

		public:
			EncounterPopup();
			~EncounterPopup() = default;

			EncounterPopup* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;

			void ToggleCloseBtnBehaviour();

			void SetBackgroundImage(const sf::Texture& t_texture);
			void SetCloseButtonImage(const sf::Texture& t_texture);
			void SetPlayButtonImage(const sf::Texture& t_texture);
			void SetOpponentImage(const sf::Texture& t_texture);
			void SetStoryImage(const sf::Texture& t_texture);
			void SetTitleText(const std::string& t_text, const sf::Font& t_font);
			
			// put together and position the whole panel
			void Assemble(sf::Vector2f t_position);

			// custom behaviour on creation
			void OnDisplay(std::function<void()> t_func);
			// custom behaviour on closing
			std::function<void()> OnClose;
	};

} }

#endif // !ENCOUNTER_POPUP_H
