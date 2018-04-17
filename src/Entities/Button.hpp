#ifndef BUTTON_COMPONENT_H
#define BUTTON_COMPONENT_H


#include <Engine/ECM/Components/SpriteComponent.hpp>
#include <Engine/ECM/Components/TextComponent.hpp>
#include <Engine/ECM/Components/ClickableComponent.hpp>

namespace HJ { namespace Entities {

	class Button final : public Engine::ECM::Entity
	{
		private:
			std::shared_ptr<Engine::Components::SpriteComponent> m_sprite;
			std::shared_ptr<Engine::Components::TextComponent> m_text;
			std::shared_ptr<Engine::Components::ClickableComponent> m_click;
		public:
			Button();
			~Button() = default;

			Button* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;

			inline std::shared_ptr<Engine::Components::SpriteComponent> GetSpriteComponent() { return m_sprite; }
			inline std::shared_ptr<Engine::Components::TextComponent> GetTextComponent() { return m_text; }
			inline std::shared_ptr<Engine::Components::ClickableComponent> GetClickableComponent() { return m_click; }
	};

} }

#endif // !BUTTON_COMPONENT_H