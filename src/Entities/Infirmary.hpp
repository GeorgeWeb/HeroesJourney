#ifndef INFIRMARY_BUILDING_H
#define INFIRMARY_BUILDING_H

#include "Building.hpp"

namespace HJ { namespace Entities {

	class Infirmary final : public Building
	{
		public:
			Infirmary(bool t_populate = true);
			~Infirmary() = default;

			Infirmary* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Upgrade() override final;
			virtual void ApplyBonus(std::vector<std::shared_ptr <Hero>> t_heroes) override final;
	};

} }

#endif // !INFIRMARY_BUILDING_H