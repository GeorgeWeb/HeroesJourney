#ifndef INN_BUILDING_H
#define INN_BUILDING_H

#include "Building.hpp"

namespace HJ { namespace Entities {

	class Inn final : public Building
	{
		public:
			Inn(const std::string& t_sprite);
			~Inn() = default;

			Inn* GetType() override final;

			void Init() override final;

			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Upgrade() override final;
			void ApplyBonus(std::vector<std::shared_ptr <Hero>> t_heroes) override final;

	};

} }

#endif // !INN_BUILDING_H