//workaround to have async input check, because std::cin blocks
//creates a cin.txt file where the user can write commands
#ifndef COMUSO_FILEINPUT_H_
#define COMUSO_FILEINPUT_H_

#ifdef DEBUGJOUVEN
#include "backwardSTso/backward.hpp"
#endif

#include "signalso/signal.hpp"

#include <boost/filesystem.hpp>

#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include <string>

namespace eines
{
namespace input
{
inline std::string getLineFile_f(const char separator = '\n')
{
	std::string strFilePath(FILENAME_MAX,'\0');
	//not portable
	readlink("/proc/self/exe", &strFilePath[0], FILENAME_MAX);
	const std::string fileFolder(strFilePath.substr(0, strFilePath.find_last_of('/')));
	const std::string cinFilePath(fileFolder + "/cin.txt");
	//if the cin file doesn't exist create it
	if (not boost::filesystem::exists(cinFilePath))
	{
		std::ofstream out(cinFilePath);
	}

	boost::filesystem::path BFSFile(cinFilePath);
	auto previousFileLastModification(boost::filesystem::last_write_time(
	                                      BFSFile));
	bool gotTextFromfile(false);
	std::string inputMsg;
	while (not gotTextFromfile and eines::signal::isRunning_f())
	{
		//if someone removes it create it again and update the variable values
		if (not boost::filesystem::exists(cinFilePath))
		{
			std::ofstream out(cinFilePath);
			out.close();
			BFSFile = boost::filesystem::path(cinFilePath);
			previousFileLastModification = boost::filesystem::last_write_time(BFSFile);
		}
		const auto fileLastModification(boost::filesystem::last_write_time(BFSFile));
		if (fileLastModification != previousFileLastModification)
		{
			std::getline(std::ifstream(cinFilePath), inputMsg, separator);
			if (not inputMsg.empty())
			{
				gotTextFromfile = true;
			}
			previousFileLastModification = fileLastModification;
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(501));
	}
	return inputMsg;
}

}
}

#endif /* COMUSO_FILEINPUT_H_ */
