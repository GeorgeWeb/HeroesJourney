#ifndef DIALOG_H
#define DIALOG_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/TextComponent.hpp>
#include <vector>

namespace HJ { namespace Entities {

	class Dialog final : public Engine::ECM::Entity
	{
		private:
			std::vector<std::shared_ptr<Engine::Components::TextComponent>> m_conversation;
			std::shared_ptr<Engine::Components::SpriteComponent> m_background;
			std::shared_ptr<Engine::Components::SpriteComponent> m_lCharacter;
			std::shared_ptr<Engine::Components::SpriteComponent> m_rCharacter;
		
		public:
			Dialog();
			~Dialog() = default;
			Dialog* GetType() override;
			
			void Init() override;
			void Update(float t_deltaTime) override;
			void Render() override;

			void SetBackgroundImage(const sf::Texture& t_texture);
			void SetLeftCharacterImage(const sf::Texture& t_texture);
			void SetRightCharacterImage(const sf::Texture& t_texture);

			void AddConversation(unsigned int t_lines);
			std::vector<std::shared_ptr<Engine::Components::TextComponent>>& GetConversation();

		private:
			// Abstract these in a DialogSystem class
			// TODO: Add fade effects for the sprites as well (on sprite change)
			void FadeIn();
			void FadeOut();
	};

} }

#endif // !DIALOG_H
