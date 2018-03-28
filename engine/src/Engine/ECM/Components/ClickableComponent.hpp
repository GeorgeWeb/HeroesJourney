#ifndef CLICKABLE_COMPONENT_H
#define CLICKABLE_COMPONENT_H

#include "../ECM.hpp"
#include "SpriteComponent.hpp"

namespace Engine { namespace Components {

	// WORKS ONLY WITH SPRITES AT THIS POINT, since I am only using sprites in the game !!!

	class ClickableComponent final : public ECM::Component
	{
		protected:			
			std::shared_ptr<SpriteComponent> m_spriteComponent;
			bool m_isClicked;
			bool m_unClicked;
			bool m_canResolve;
			float m_timer;

		public:
			ClickableComponent() = delete;
			explicit ClickableComponent(ECM::Entity* t_parent);

			ClickableComponent* GetType() override;

			void SetSpriteTarget(SpriteComponent* t_sprite);

			void Update(float t_deltaTime) override;
			void Render() override {}

			inline void SetClicked(bool t_clicked) { m_isClicked = t_clicked; }
			inline bool IsClicked() { return m_isClicked; }

			void SetResolve(bool t_resolve);
			bool CanResolve();
	};

} }

#endif // !CLICKABLE_COMPONENT_H