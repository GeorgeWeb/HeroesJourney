#ifndef DIALOG_H
#define DIALOG_H

#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/TextComponent.hpp>
#include <vector>

namespace HJ {
	
	enum class DIALOG_TURN : int
	{
		LEFT = 0,
		RIGHT = 1
	};

	namespace Entities {

	class Dialog final : public Engine::ECM::Entity
	{
		private:
			std::vector<std::shared_ptr<Engine::Components::TextComponent>> m_conversation;
			std::shared_ptr<Engine::Components::SpriteComponent> m_lCharacter;
			std::shared_ptr<Engine::Components::SpriteComponent> m_rCharacter;		
			std::vector<std::string> m_texts;
		public:
			Dialog();
			~Dialog() = default;
			Dialog* GetType() override;
			
			void Init() override;
			void Update(float t_deltaTime) override;
			void Render() override;

			void SetLeftCharacterImage(const sf::Texture& t_texture);
			void SetRightCharacterImage(const sf::Texture& t_texture);

			void AddConversation(std::vector<std::string> t_texts);
			std::vector<std::shared_ptr<Engine::Components::TextComponent>>& GetConversation();
			std::vector<std::string> GetTexts() { return m_texts; }

			void DisplayConvo(int t_start, int t_end, const sf::Font& t_font);
	};

} }

#endif // !DIALOG_H
