#include "Damage.hpp"
#include <string>

namespace HJ
{
	Damage::Damage(std::shared_ptr<Entities::Hero> t_initiator, std::shared_ptr<Skill> t_skill, int t_hitChance)
	{
		m_hitChance = t_hitChance;
		m_target = t_skill->target;
		m_base = t_skill->dmgBase;
		m_type = t_skill->dmgType;
		m_applicableEffects = t_skill->applicableEffects;
		if (m_base == DAMAGE_BASE::DEFENCE)
		{
			m_damage = 0;
		}
		else
		{
			m_damage = t_initiator->GetDmg();
			m_damage *= t_skill->damageMod;
			m_damage /= 100;

			// IN PERCENTAGES

			if (t_initiator->GetStatusComponent()->GetEffect(EFFECT_TYPE::DAMAGE_AURA)->active)
			{
				m_damage *= 25;
				m_damage /= 100;
			}

			if (t_initiator->GetStatusComponent()->GetEffect(EFFECT_TYPE::ENRAGE)->active)
			{
				m_damage *= 200;
				m_damage /= 100;
			}
		}
	}

	std::string Damage::SendDamage(std::shared_ptr<Entities::Hero> t_receiver)
	{
		if (m_target == SKILL_TARGET::ALLY)
		{
			// Apply effect
			ApplyEffects(t_receiver);
			return "BUFFED!";
		}

		unsigned int dodge = t_receiver->GetDodge();
		if (t_receiver->GetStatusComponent()->GetEffect(EFFECT_TYPE::DEFEND)->active)
		{
			dodge *= 2;
		}

		if (dodge > m_hitChance)
		{
			return "DODGED!";
		}

		if (t_receiver->GetStatusComponent()->GetEffect(EFFECT_TYPE::FLY)->active && m_base == DAMAGE_BASE::MELEE)
		{
			m_damage = 0;
		}

		if (t_receiver->GetStatusComponent()->GetEffect(EFFECT_TYPE::MAGIC_IMUNITY)->active && m_type != DAMAGE_TYPE::BASIC)
		{
			m_damage *= 20;
			m_damage /= 100;
		}

		if (t_receiver->GetStatusComponent()->GetEffect(EFFECT_TYPE::FROST_ARMOR)->active && m_type != DAMAGE_TYPE::FIRE)
		{
			m_damage *= 20;
			m_damage /= 100;
		}
		
		if (t_receiver->GetStatusComponent()->GetEffect(EFFECT_TYPE::FROST_AURA)->active && m_type != DAMAGE_TYPE::FROST)
		{
			m_damage *= 80;
			m_damage /= 100;
		}

		if (t_receiver->GetStatusComponent()->GetEffect(EFFECT_TYPE::ARMOUR_AURA)->active && m_type != DAMAGE_TYPE::BASIC)
		{
			m_damage *= 80;
			m_damage /= 100;
		}

		if (m_type == DAMAGE_TYPE::BASIC)
		{
			m_damage *= 100 - t_receiver->GetArmour();
			m_damage /= 100;
		}

		t_receiver->ReceiveDamage(m_damage / 10);
		ApplyEffects(t_receiver);

		return std::to_string(m_damage);
	}

	void Damage::ApplyEffects(std::shared_ptr<Entities::Hero> t_receiver)
	{
		for (auto effect : m_applicableEffects)
		{
			if (!(effect == EFFECT_TYPE::STUN && t_receiver->GetStatusComponent()->GetEffect(EFFECT_TYPE::ENRAGE)->active))
				t_receiver->GetStatusComponent()->GetEffect(effect)->active = true;
		}
	}
}