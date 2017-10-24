#ifndef COMUSO_RANDOMSTRING_H_
#define COMUSO_RANDOMSTRING_H_

#include <chrono>
#include <random>
#include <string>

namespace eines
{
struct randomString_s
{
	std::string operator()(const int_fast32_t length_par_con) const
	{
		static const std::string alphanums(
        	"0123456789"
        	"abcdefghijklmnopqrstuvwxyz"
        	"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        );

		static std::mt19937 rg(std::chrono::system_clock::now().time_since_epoch().count());
		std::uniform_int_distribution<> pick(0, alphanums.size() - 1);

		std::string s(length_par_con,'\0');

		for (auto i = 0; i < length_par_con; ++i)
		{
			s[i] = alphanums[pick(rg)];
		}

		return s;
	}
};
}

#endif /* COMUSO_RANDOMSTRING_H_ */
