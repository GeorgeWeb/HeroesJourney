#ifndef DAMAGE_H
#define DAMAGE_H

namespace HJ
{

	enum class DAMAGE_BASE : int
	{
		MELEE   = 0,
		RANGED  = 1,
		DEFENCE = 2
	};

	enum class DAMAGE_TYPE : int
	{
		BASIC = 0,
		FROST = 1,
		FIRE  = 2,
		MAGIC = 3
	};

	class Damage final
	{
		public:
			Damage() = default;
	};

}



#endif // !DAMAGE_H

