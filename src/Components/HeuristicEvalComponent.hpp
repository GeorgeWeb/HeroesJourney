#ifndef HEURISTIC_EVAL_COMPONENT_H
#define HEURISTIC_EVAL_COMPONENT_H

#include "../Entities/Hero.hpp"
#include "../SkillSet.hpp"

namespace HJ { namespace Components {

	using namespace Engine;

	class HeuristicEvalComponent : public ECM::Component
	{
		public:
			HeuristicEvalComponent() = delete;
			explicit HeuristicEvalComponent(ECM::Entity* t_parent);

			void Initialize(std::shared_ptr<Entities::Hero> t_initiator,
				std::vector<std::shared_ptr<Entities::Hero>> t_targets,
				std::shared_ptr<Skill> t_usedSkill);

			HeuristicEvalComponent* GetType() override { return this; }

			void Update(float t_deltaTime) override {}
			void Render() override {}

			void Evaluate();

			bool IsComplete() const;
			void SetComplete(bool t_complete);

			inline std::vector<std::shared_ptr<Entities::Hero>> GetTargets() { return m_targets; }
			inline std::shared_ptr<Entities::Hero> GetInitiator() { return m_initiator; }
			inline std::shared_ptr<Skill> GetUsedSkill() { return m_usedSkill; }

		private:
			std::shared_ptr<Entities::Hero> m_initiator;
			std::vector<std::shared_ptr<Entities::Hero>> m_targets;
			std::shared_ptr<Skill> m_usedSkill;

			bool m_complete;

		// Evaluation helper
		private:
			// generic hero evaluation
			void HeroEval();

			// boss evaluations
			void FrostGolemEval();
	};

} }

#endif // !HEURISTIC_EVAL_COMPONENT_H