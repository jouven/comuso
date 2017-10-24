#ifndef COMUSO_CXXTOOLSERIALIZATION_H_
#define COMUSO_CXXTOOLSERIALIZATION_H_

#include <cxxtools/json.h>
#include <cxxtools/utf8codec.h>

#include <type_traits>
#include <sstream>
#include <string>
#include <utility>

namespace eines
{
namespace serialization
{

template<typename T>
std::string serializeJSON_f(const T& obj_par_con)
{
	if (not obj_par_con.empty())
	{
		std::ostringstream tmp;
		tmp << cxxtools::Json(obj_par_con);
		return tmp.str();
	}
	else
	{
		return std::string();
	}
}

template<typename T>
std::string serializeJSON_f(
	typename std::enable_if<std::is_integral<T>::value, const T>::type obj_par_con
)
{
	std::ostringstream tmp;
	tmp << cxxtools::Json(obj_par_con);
	return tmp.str();
}

template<typename T>
std::pair<T, std::string> deserializeJSON_f(
	const std::string& JSONStr_par_con
)
{
	T tmpObj;
	std::string errorStr;
	if (not JSONStr_par_con.empty())
	{
		std::istringstream tmp(JSONStr_par_con);
		try
		{
			tmp >> cxxtools::Json(tmpObj);
		}
		catch (const std::exception& e)
		{
			errorStr = e.what();
		}
	}
	return std::make_pair(tmpObj, errorStr);
}

inline std::vector<std::string> cxxStrVectorToStdStrVector(
	const std::vector<cxxtools::String>& cxxStrVector_par_con
)
{
	std::vector<std::string> stdStrVector;
	if (not cxxStrVector_par_con.empty())
	{
		stdStrVector.reserve(cxxStrVector_par_con.size());
		for (const auto& str_ite_con : cxxStrVector_par_con)
		{
			stdStrVector.emplace_back(
				cxxtools::Utf8Codec::encode(str_ite_con)
			);
		}
	}
	return stdStrVector;
}

inline std::vector<cxxtools::String> StdStrVectorToCxxStrVector(
	const std::vector<std::string>& stdStrVector_par_con
)
{
	std::vector<cxxtools::String> cxxStrVector;
	if (not stdStrVector_par_con.empty())
	{
		cxxStrVector.reserve(stdStrVector_par_con.size());
		for (const auto& str_ite_con : stdStrVector_par_con)
		{
			cxxStrVector.emplace_back(
				cxxtools::Utf8Codec::decode(str_ite_con)
			);
		}
	}
	return cxxStrVector;
}

}
}

#endif /* COMUSO_CXXTOOLSERIALIZATION_H_ */
