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
			if (m_initiator->className() == "Frost Golem")
			{
				FrostGolemEval();
				m_complete = true;
			}

			if (m_initiator->className() == "Troll")
			{
				TrollEval();
				m_complete = true;
			}

			if (m_initiator->className() == "Cyclop")
			{
				CyclopsEval();
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
			m_targets.clear();
			m_targets.push_back(m_initiator);
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
		if (m_initiator->GetHealth() <= m_initiator->GetMaxHealth() / 2 && !m_initiator->GetStatusComponent()->GetEffect(EFFECT_TYPE::ENRAGE)->active)
		{
			RageBehaviour();
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
	}

	void HeuristicEvalComponent::TrollEval()
	{
		// TODO
	}

	void HeuristicEvalComponent::CyclopsEval()
	{
		// TODO
	}

	void HeuristicEvalComponent::RageBehaviour()
	{
		m_initiator->GetStatusComponent()->GetEffect(EFFECT_TYPE::ENRAGE)->active = true;
		m_usedSkill = m_initiator->GetSkillComponent()->FindSkill(SKILL_NAME::RAGE);

		// CAN ADD ALL AS WELL

		if (m_usedSkill->target == SKILL_TARGET::SELF)
		{
			m_targets.clear();
			m_targets.push_back(m_initiator);
		}
		else if (m_usedSkill->target == SKILL_TARGET::ALLY)
		{
			std::vector<std::shared_ptr<Entities::Hero>> originalTargets;
			originalTargets.insert(originalTargets.begin(), m_targets.begin(), m_targets.end());
			m_targets.clear();
		
			for (auto target : originalTargets)
			{
				if (target->heroType() == m_initiator->heroType())
					m_targets.push_back(target);
			}
		}
		else if (m_usedSkill->target == SKILL_TARGET::ENEMY_TEAM)
		{
			std::vector<std::shared_ptr<Entities::Hero>> originalTargets;
			originalTargets.insert(originalTargets.begin(), m_targets.begin(), m_targets.end());
			m_targets.clear();
		
			for (auto target : originalTargets)
			{
				if (target->heroType() != m_initiator->heroType())
					m_targets.push_back(target);
			}
		}
		else // ENEMY
		{
			std::map<std::string, Entities::Hero> enemies;
			for (auto target : m_targets)
			{
				if (target->heroType() != m_initiator->heroType())
				{
					Entities::Hero enemy = *target;
					enemies[enemy.className()] = enemy;
				}
			}

			// copy initiator
			Entities::Hero initiatorCopy = *m_initiator;
			auto initiatorCopyPtr = std::make_shared<Entities::Hero>(); *initiatorCopyPtr = initiatorCopy;
			int healthDiff = 0;
			Entities::Hero highestDealer;

			Damage damage;
			for (auto enemy : enemies)
			{
				// SKILL 1
				// reset initiator copy
				*initiatorCopyPtr = *m_initiator;
				// copy enemy
				auto enemyCopyPtr = std::make_shared<Entities::Hero>(); *enemyCopyPtr = enemy.second;
				// create test damage from enemy copy
				damage = Damage(enemyCopyPtr, enemyCopyPtr->GetSkillComponent()->FindSkill(SKILL_NAME::SPECIAL_SKILL_1), m_random.NextInt(100, 1));
				// send damage to initiator copy
				damage.SendDamage(initiatorCopyPtr,false);
				// set highest dealer
				if (m_initiator->GetHealth() - initiatorCopyPtr->GetHealth() > healthDiff)
				{
					healthDiff = m_initiator->GetHealth() - initiatorCopyPtr->GetHealth();
					highestDealer = enemy.second;
				}
					
				// SKILL 2
				// reset initiator copy
				*initiatorCopyPtr = *m_initiator;
				// skill 2 simulate
				// create test damage from enemy copy
				damage = Damage(enemyCopyPtr, enemyCopyPtr->GetSkillComponent()->FindSkill(SKILL_NAME::SPECIAL_SKILL_2), m_random.NextInt(100, 1));
				// send damage to initiator copy
				damage.SendDamage(initiatorCopyPtr,false);
				// set highest dealer
				if (m_initiator->GetHealth() - initiatorCopyPtr->GetHealth() > healthDiff)
				{
					healthDiff = m_initiator->GetHealth() - initiatorCopyPtr->GetHealth();
					highestDealer = enemy.second;
				}
					
				// BASIC ATTACK
				// reset initiator copy
				*initiatorCopyPtr = *m_initiator;
				// basic attack simulate
				// create test damage from enemy copy
				damage = Damage(enemyCopyPtr, enemyCopyPtr->GetSkillComponent()->FindSkill(SKILL_NAME::BASIC_ATTACK), m_random.NextInt(100, 1));
				// send damage to initiator copy
				damage.SendDamage(initiatorCopyPtr,false);
				// set highest dealer
				if (m_initiator->GetHealth() - initiatorCopyPtr->GetHealth() > healthDiff)
				{
					healthDiff = m_initiator->GetHealth() - initiatorCopyPtr->GetHealth();
					highestDealer = enemy.second;
				}
			}

			// copy targets
			std::vector<std::shared_ptr<Entities::Hero>> originalTargets;
			originalTargets.insert(originalTargets.begin(), m_targets.begin(), m_targets.end());
			m_targets.clear();
			// push the highest dealer in the targets vector
			for (auto target : originalTargets)
			{
				if (target->className() == highestDealer.className())
					m_targets.push_back(target);
			}
		}
	}

} }