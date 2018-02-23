#ifndef IENCOUNTER_H
#define IENCOUNTER_H

#include <Engine/Engine.hpp>
#include "../../Game.hpp"

#include "../../Entities/Hero.hpp"

namespace HJ { namespace Encounters{

	using namespace Engine;

	class IEncounter : public SM::State
	{
		protected:
			GameDataRef m_data;

		public:
			IEncounter(GameDataRef t_data);

			void Init() override final;

			void HandleInput() override final;
			void Update(float t_delatTime) override final;
			void Draw(float t_deltaTime) override final;
	};

} }

#endif IENCOUNTER_H