#ifndef BLACKSMITH_BUILDING_H
#define BLACKSMITH_BUILDING_H

#include "Building.hpp"

namespace HJ {
	namespace Entities {

		class Blacksmith final : public Building
		{
		public:
			Blacksmith(const std::string& t_sprite);
			~Blacksmith() = default;

			Blacksmith* GetType() override;

			void Init(const sf::Texture& t_texture) override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void Upgrade();


		};

	}
}

#endif // !BLACKSMITH_BUILDING_H