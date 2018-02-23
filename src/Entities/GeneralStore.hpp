
#ifndef GENERALSTORE_BUILDING_H
#define GENERALSTORE_BUILDING_H

#include "Building.hpp"

namespace HJ { namespace Entities {

		class GeneralStore final : public Building
		{
		public:
			GeneralStore(const std::string& t_sprite);
			~GeneralStore() = default;

			GeneralStore* GetType() override;

			void Init(const sf::Texture& t_texture) override;

			void Update(float t_deltaTime) override;
			void Render() override;



		};

	} }

#endif // !GENERALSTORE_BUILDING_H