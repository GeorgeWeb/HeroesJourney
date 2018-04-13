#ifndef GENERALSTORE_BUILDING_H
#define GENERALSTORE_BUILDING_H

#include "Building.hpp"

namespace HJ { namespace Entities {

	class GeneralStore final : public Building
	{
		public:
			GeneralStore(bool t_populate = true);
			~GeneralStore() = default;

			GeneralStore* GetType() override final;

			void Init() override final;
			void Update(float t_deltaTime) override final;
			void Render() override final;
	};

} }

#endif // !GENERALSTORE_BUILDING_H