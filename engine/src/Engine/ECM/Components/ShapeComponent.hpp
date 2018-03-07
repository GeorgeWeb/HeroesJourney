#ifndef SHAPE_COMPONENT_H
#define SHAPE_COMPONENT_H

#include "../ECM.hpp"

namespace Engine { namespace Components {

	class ShapeComponent final : public ECM::Component
	{
		protected:
			std::shared_ptr<sf::Shape> m_shape;
		
		public:
			ShapeComponent() = delete;
			explicit ShapeComponent(ECM::Entity* t_parent);

			ShapeComponent* GetType() override;

			void Update(float t_deltaTime) override;
			void Render() override;

			sf::Shape& GetShape();

			template<class T, class... Targs>
			void SetShape(Targs... t_params)
			{
				m_shape.reset(new T(t_params...));
			}
	};

} }

#endif // !SHAPE_COMPONENT_H
