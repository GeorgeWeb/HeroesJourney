#include "HeuristicEvalComponent.hpp"


namespace HJ { namespace Components {

	using namespace Engine;

	HeuristicEvalComponent::HeuristicEvalComponent(ECM::Entity* t_parent) 
		: ECM::Component(t_parent), m_complete(false)
	{ }

	void HeuristicEvalComponent::Initialize(std::shared_ptr<Entities::Hero> t_initiator,
		std::vector<std::shared_ptr<Entities::Hero>> t_targets,
		std::shared_ptr<Skill> t_usedSkill)
	{
		m_initiator = t_initiator;
		m_targets.clear();
		m_targets.insert(m_targets.begin(), t_targets.begin(), t_targets.end());
		m_usedSkill = t_usedSkill;
	}

	void HeuristicEvalComponent::Evaluate()
	{
		if (m_usedSkill != nullptr)
		{
			
			HeroEval();
			m_complete = true;
		}
		else
		{
			std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA NULL PTR AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!\n";
			if (m_initiator->className() == "Frost Golem")
			{

				FrostGolemEval();
				m_complete = true;
			}

			if (m_initiator->className() == "Troll")
			{
				FrostGolemEval();
				m_complete = true;
			}

			if (m_initiator->className() == "Cyclop")
			{
				FrostGolemEval();
				m_complete = true;
			}

			if (m_initiator->className() == "Harpy")
			{
				FrostGolemEval();
				m_complete = true;
			}

			if (m_initiator->className() == "Frost Mage")
			{
				FrostGolemEval();
				m_complete = true;
			}
		}
	}

	bool HeuristicEvalComponent::IsComplete() const
	{
		return m_complete;
	}

	void HeuristicEvalComponent::SetComplete(bool t_complete)
	{
		m_complete = t_complete;
	}

	void HeuristicEvalComponent::HeroEval()
	{	
		if (m_usedSkill->target == SKILL_TARGET::SELF)
		{
			std::cout << "Evaluating my-self!" << std::endl;
			std::cout << m_targets.size() << std::endl;
			m_targets.clear();
			m_targets.push_back(m_initiator);
			std::cout << m_targets.size() << std::endl;
		}
		else if (m_usedSkill->target == SKILL_TARGET::ALLY)
		{
			std::vector<std::shared_ptr<Entities::Hero>> originalTargets;
			originalTargets.insert(originalTargets.begin(), m_targets.begin(), m_targets.end());
			m_targets.clear();
			for (std::shared_ptr<Entities::Hero> target : originalTargets)
			{
				if (target->heroType() == m_initiator->heroType() && !target->IsDead())
				{
					m_targets.push_back(target);
				}
			}
		}
		else if (m_usedSkill->target == SKILL_TARGET::ENEMY)
		{
			std::vector<std::shared_ptr<Entities::Hero>> originalTargets;
			originalTargets.insert(originalTargets.begin(), m_targets.begin(), m_targets.end());
			m_targets.clear();
			for (std::shared_ptr<Entities::Hero> target : originalTargets)
			{
				if (target->heroType() != m_initiator->heroType() && !target->IsDead())
				{
					m_targets.push_back(target);
				}
			}
		}
	}

	void HeuristicEvalComponent::FrostGolemEval()
	{
		
		// RAGE
		if (m_initiator->GetHealth() < m_initiator->GetMaxHealth() / 2)
		{
			m_initiator->GetStatusComponent()->GetEffect(EFFECT_TYPE::ENRAGE)->active = true;
			m_usedSkill = m_initiator->GetSkillComponent()->FindSkill(SKILL_NAME::RAGE);
			if (m_usedSkill->target == SKILL_TARGET::ENEMY)
			{
				std::vector<std::shared_ptr<Entities::Hero>> originalTargets;
				originalTargets.insert(originalTargets.begin(), m_targets.begin(), m_targets.end());
				m_targets.clear();
				for (std::shared_ptr<Entities::Hero> target : originalTargets)
				{
					if (target->heroType() != m_initiator->heroType() && !target->IsDead() && m_targets.empty())
					{
						m_targets.push_back(target);
					}
				}
			}
			else
			{
				m_targets.clear();
				m_targets.push_back(m_initiator);
			}
		}
		else if (m_initiator->GetStatusComponent()->GetEffect(EFFECT_TYPE::MULTIPLE_TARGET)->active)
		{
			// use rand skill
			m_usedSkill = m_initiator->GetSkillComponent()->FindSkill(SKILL_NAME::SPECIAL_SKILL_1);
			
			// get multiple enemy targets
			std::vector<std::shared_ptr<Entities::Hero>> originalTargets;
			originalTargets.insert(originalTargets.begin(), m_targets.begin(), m_targets.end());
			m_targets.clear();
			for (std::shared_ptr<Entities::Hero> target : originalTargets)
			{
				if (target->heroType() != m_initiator->heroType() && !target->IsDead())
				{
					m_targets.push_back(target);
				}
			}
		}
		else
		{
		
			m_usedSkill = m_initiator->GetSkillComponent()->FindSkill(SKILL_NAME::SPECIAL_SKILL_2);
			
			// get single enemy target
			std::vector<std::shared_ptr<Entities::Hero>> originalTargets;
			originalTargets.insert(originalTargets.begin(), m_targets.begin(), m_targets.end());
			m_targets.clear();
			for (std::shared_ptr<Entities::Hero> target : originalTargets)
			{
				if (target->heroType() != m_initiator->heroType() && !target->IsDead() && m_targets.size()==0)
				{
					m_targets.push_back(target);
				}
			}
		}
		std::cout << "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA NULL PTR AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA!\n";
	}

} }