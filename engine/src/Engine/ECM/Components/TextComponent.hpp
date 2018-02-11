#ifndef TEXT_COMPONENT_H
#define TEXT_COMPONENT_H

#include "../ECM.hpp"

namespace Engine { namespace Components {

	class TextComponent final : public ECM::Component
	{
		protected:
			std::shared_ptr<sf::Text> m_text;

		public:
			TextComponent() = delete;
			explicit TextComponent(ECM::Entity* t_parent);

			void Update(float t_deltaTime) override;
			void Render() override;

			sf::Text& GetText() override;

			void SetFont(const sf::Font& t_font)
			{
				m_text->setFont(t_font);
			}
	};

} }

#endif // !TEXT_COMPONENT_H