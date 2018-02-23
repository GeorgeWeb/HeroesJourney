
#ifndef INN_BUILDING_H
#define INN_BUILDING_H

#include "Building.hpp"

namespace HJ {
	namespace Entities {

		class Inn final : public Building
		{
		public:
			Inn(const std::string& t_sprite);
			~Inn() = default;

			Inn* GetType() override;

			void Init(const sf::Texture& t_texture) override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void Upgrade();


		};

	}
}

#endif // !INN_BUILDING_H