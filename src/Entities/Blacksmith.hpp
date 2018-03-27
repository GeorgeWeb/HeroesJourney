#ifndef BLACKSMITH_BUILDING_H
#define BLACKSMITH_BUILDING_H

#include "Building.hpp"

namespace HJ { namespace Entities {

	class Blacksmith final : public Building
	{
		public:
			Blacksmith(const std::string& t_sprite);
			~Blacksmith() = default;

			Blacksmith* GetType() override final;
			
			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Upgrade() override final;
	};

} }

#endif // !BLACKSMITH_BUILDING_H