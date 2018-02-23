#ifndef LIBRARY_BUILDING_H
#define LIBRARY_BUILDING_H

#include "Building.hpp"

namespace HJ {
	namespace Entities {

		class Library final : public Building
		{
		public:
			Library(const std::string& t_sprite);
			~Library() = default;

			Library* GetType() override;

			void Init(const sf::Texture& t_texture) override;

			void Update(float t_deltaTime) override;
			void Render() override;

			void Upgrade();


		};

	}
}

#endif // !LIBRARY_BUILDING_H