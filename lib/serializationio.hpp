#ifndef COMUSO_CXXTOOLSERIALIZATIONIO_H_
#define COMUSO_CXXTOOLSERIALIZATIONIO_H_

#include "serializationfs.hpp"

#include "loggingMacros.hpp"

#include <iostream>

namespace eines
{
namespace serialization
{

template<typename T>
T getObjectFromFilePrintError_f(
	const std::string& filename_par_con
)
{
	auto tmp(getObjectFromFile_f<T>(
		filename_par_con
	));
	if (not tmp.second.empty())
	{
		std::cout << DEBUGDATETIME << DEBUGSOURCE << tmp.second;
	}
	return tmp.first;

}

}
}

#endif /* COMUSO_CXXTOOLSERIALIZATIONIO_H_ */
