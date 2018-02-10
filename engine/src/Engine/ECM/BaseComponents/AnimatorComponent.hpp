#ifndef ANIMATOR_COMPONENT_H
#define ANIMATOR_COMPONENT_H

#include "../ECM.hpp"
#include "../../System/Animation.hpp"

namespace Engine { namespace Components {

	class AnimatorComponent final : public ECM::Component
	{
		protected:
			std::shared_ptr<System::Animation> m_animation;
			
		public:
			AnimatorComponent() = delete;
			explicit AnimatorComponent(ECM::Entity* t_parent);

			void Update(float t_deltaTime) override;
			void Render() override;

			void SetAnimation(sf::Texture* t_texture, sf::Vector2u t_imgCount, float t_switchTime);

			System::Animation& GetAnimation() override;
	};

} }

#endif !ANIMATOR_COMPONENT_H