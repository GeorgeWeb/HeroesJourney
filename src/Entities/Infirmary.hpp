#ifndef INFIRMARY_BUILDING_H
#define INFIRMARY_BUILDING_H

#include "Building.hpp"

namespace HJ {
	namespace Entities {

		class Infirmary final : public Building
		{
		public:
			Infirmary(const std::string& t_sprite);
			~Infirmary() = default;

			Infirmary* GetType() override;

			void Init(const sf::Texture& t_texture) override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void Upgrade();

		
		};

	}
}

#endif // !INFIRMARY_BUILDING_H