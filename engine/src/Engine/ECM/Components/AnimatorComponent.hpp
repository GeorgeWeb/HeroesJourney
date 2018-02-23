#ifndef ANIMATOR_COMPONENT_H
#define ANIMATOR_COMPONENT_H

#include "../ECM.hpp"
#include "../../System/Animation.hpp"

namespace Engine { namespace Components {

	class AnimatorComponent final : public ECM::Component
	{
		protected:
			std::map<std::string, std::shared_ptr<System::Animation>> m_animations;
			
		public:
			AnimatorComponent() = delete;
			explicit AnimatorComponent(ECM::Entity* t_parent);

			AnimatorComponent* GetType() override;

			void Update(float t_deltaTime) override;
			void Render() override;

			std::shared_ptr<System::Animation> AddAnimation(const std::string& t_name, System::Animation t_animation);

			sf::IntRect GetAnimUVRect(const std::string& t_name);

			std::map<std::string, std::shared_ptr<System::Animation>> GetAnims();
			
			System::Animation& GetAnimation(const std::string& t_name);
	};

} }

#endif !ANIMATOR_COMPONENT_H