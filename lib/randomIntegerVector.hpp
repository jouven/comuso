#ifndef COMUSO_RANDOMINTEGERVECTOR_H_
#define COMUSO_RANDOMINTEGERVECTOR_H_

#include <chrono>
#include <random>
#include <cstdint>
#include <vector>

namespace eines
{
struct randomIntegerVector_s
{
	template<typename T>
	std::vector<T> operator()(
		const int_fast64_t vectorLength
		, const T min_par_con
		, const T max_par_con) const
	{
		static std::mt19937 rg(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<T> pick(min_par_con, max_par_con);

		std::vector<T> vector;
		vector.resize(vectorLength);
		for (auto i = 0; i < vectorLength; ++i)
		{
			vector[i] = pick(rg);
		}

		return vector;
	}
};
}

#endif /* COMUSO_RANDOMINTEGERVECTOR_H_ */
