#ifndef BLACKSMITH_BUILDING_H
#define BLACKSMITH_BUILDING_H

#include "Building.hpp"

namespace HJ { namespace Entities {

	class Blacksmith final : public Building
	{
		public:
			Blacksmith(bool t_populate = true);
			~Blacksmith() = default;

			Blacksmith* GetType() override final;
			
			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Upgrade() override final;
			void ApplyBonus(std::vector<std::shared_ptr <Hero>> t_heroes) override final;

	};

} }

#endif // !BLACKSMITH_BUILDING_H