#ifndef RANDOM_H
#define RANDOM_H

#include <random>
#include <time.h>

namespace Engine { namespace Utils {

	// TODO: C++11-ize
	class Random
	{
		public:
			Random()
			{
				srand(time(0));
			}

			int NextInt(int high, int low)
			{
				return (rand() % (high - low)) + low;
			}
	};

} }

#endif // !RANDOM_H
