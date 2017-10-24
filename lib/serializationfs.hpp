#ifndef COMUSO_CXXTOOLSERIALIZATIONFS_H_
#define COMUSO_CXXTOOLSERIALIZATIONFS_H_

#include "serialization.hpp"

#include <fstream>

namespace eines
{
namespace serialization
{

template<typename T>
void saveObjectToFile_f(
	const std::string& filename_par_con
	, const T& obj_par_con
)
{
	auto strTmp(serializeJSON_f<T>(obj_par_con));
	std::ofstream outFile(filename_par_con);
	outFile << strTmp;
}

template<typename T>
std::pair<T, std::string> getObjectFromFile_f(
	const std::string& filename_par_con
)
{
	std::pair<T, std::string> tmpObj;
	if (not filename_par_con.empty())
	{
		std::ifstream inFile(filename_par_con);
		if (inFile.is_open())
		{
			std::stringstream tmp;
			tmp << inFile.rdbuf();
			tmpObj = deserializeJSON_f<T>(tmp.str());
		}
		else
		{
			tmpObj.second = "Error opening file: " + filename_par_con;
		}
	}
	else
	{
		tmpObj.second = "Empty file name";
	}
	return tmpObj;
}

}
}

#endif /* COMUSO_CXXTOOLSERIALIZATIONFS_H_ */
