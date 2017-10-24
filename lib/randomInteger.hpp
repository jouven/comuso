#ifndef COMUSO_RANDOMINTEGER_H_
#define COMUSO_RANDOMINTEGER_H_

#include <chrono>
#include <random>
#include <cstdint>

namespace eines
{
struct randomInteger_s
{
	template <typename T>
	T operator()(
		const T min_par_con
		, const T max_par_con
	) const
	{
		//this means that the seed will be the same for the duration of the program
		static std::mt19937 rg(std::chrono::system_clock::now().time_since_epoch().count());
		//if we did the static with this one, the random range would be set once and that's it
		//SO NO STATIC HERE
		std::uniform_int_distribution<T> pick(min_par_con, max_par_con);

		return pick(rg);
	}
};
}

#endif /* COMUSO_RANDOMINTEGER_H_ */
