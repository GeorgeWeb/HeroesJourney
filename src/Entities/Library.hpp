#ifndef LIBRARY_BUILDING_H
#define LIBRARY_BUILDING_H

#include "Building.hpp"

namespace HJ { namespace Entities {

	class Library final : public Building
	{
		public:
			Library(const std::string& t_sprite);
			~Library() = default;

			Library* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;

			void Upgrade() override final;
			void ApplyBonus(std::vector<std::shared_ptr <Hero>> t_heroes) override final;

	};
} }

#endif // !LIBRARY_BUILDING_H