//Inherited class used to deal/save the request part
//so it can be checked at any moment for data
#ifndef COMUSO_BASECLASS_H_
#define COMUSO_BASECLASS_H_

#ifdef DEBUGJOUVEN
#include "loggingMacros.hpp"
#ifndef __ANDROID__
#include "backwardSTso/backward.hpp"
#endif
#include <iostream>
#endif

#include <string>
#include <utility>
#include <mutex>
#include <unordered_map>

namespace eines
{
namespace baseClass
{

class baseClass_c
{
		std::string errorStr_pri;
	public:
		std::string getError_f()
		{
			return std::exchange(errorStr_pri, {});
		}
		void setError_f(const std::string& error_par_con)
		{
			errorStr_pri = error_par_con;
		}
		static void appendError_f(
			std::string& str_par,
			const std::string& error_par_con
			, const std::string& separator_par_con = "\n")
		{
			if (str_par.empty())
			{
				str_par
				.append(error_par_con);
			}
			else
			{
				str_par
				.append(separator_par_con)
				.append(error_par_con);
			}
		}
		void appendError_f(
			const std::string& error_par_con
			, const std::string& separator_par_con = "\n")
		{
			if (errorStr_pri.empty())
			{
				errorStr_pri
				.append(error_par_con);
			}
			else
			{
				errorStr_pri
				.append(separator_par_con)
				.append(error_par_con);
			}
		}
		bool anyError_f() const
		{
			return not errorStr_pri.empty();
		}
};

class uniqueErrorsClassMutex_c
{
		std::unordered_map<std::string, int_fast32_t> errorsUMap_pri;
		std::mutex mutex_pri;
	public:
		uniqueErrorsClassMutex_c() = default;
		std::unordered_map<std::string, int_fast32_t> getErrors_f()
		{
			std::lock_guard<std::mutex> lock(mutex_pri);
			//std::unordered_map<std::string, int_fast32_t> tmp = std::move(errorsStr_pri);
			//errorsStr_pri = std::unordered_map<std::string, int_fast32_t>();
			return std::exchange(errorsUMap_pri, std::unordered_map<std::string, int_fast32_t>());
		}
		void appendError_f(
			const std::string& error_par_con)
		{
			std::lock_guard<std::mutex> lock(mutex_pri);
			auto findResult(errorsUMap_pri.find(error_par_con));
			if (findResult == errorsUMap_pri.end())
			{
				errorsUMap_pri.emplace(error_par_con, 1);
			}
			else
			{
				findResult->second = findResult->second + 1;
			}
		}
		bool anyError_f() const
		{
			return not errorsUMap_pri.empty();
		}
};

}
}
#endif /* COMUSO_BASECLASS_H_ */
