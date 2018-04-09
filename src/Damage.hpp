#ifndef DAMAGE_H
#define DAMAGE_H

#include "SkillSet.hpp"
#include "Entities/Hero.hpp"

namespace HJ
{

	class Damage final
	{
		public:
			Damage(std::shared_ptr<Entities::Hero> t_initiator, std::shared_ptr<Skill> t_skill, int t_hitChance);
			
			std::string SendDamage(std::shared_ptr<Entities::Hero> t_receiver);

		private:
			void ApplyEffects(std::shared_ptr<Entities::Hero> t_receiver);

		private:
			int m_hitChance;
			unsigned int m_damage;
			SKILL_TARGET m_target;
			DAMAGE_BASE m_base;
			DAMAGE_TYPE m_type;
			std::vector<EFFECT_TYPE> m_applicableEffects = {};
	};

}



#endif // !DAMAGE_H

