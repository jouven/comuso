#ifndef COMUSO_PROCESSFILENAME_H_
#define COMUSO_PROCESSFILENAME_H_

#ifdef DEBUGJOUVEN
#include "backwardSTso/backward.hpp"
#endif

#ifdef __MINGW32__
#define UNICODE
#include <windows.h>
#include <utf8.h>
#endif

#include <string>
#include <unistd.h>
#include <cstdio>

namespace eines
{
namespace process
{
	class processFile_c
	{
			private:
				std::string processFileFullPath_pri = std::string(FILENAME_MAX,'\0');
				std::string processFolderFullPath_pri;
			public:
			processFile_c()
			{

				#ifdef __MINGW32__
				processFileFullPath_pri.clear();
				std::wstring tempStr(FILENAME_MAX,'\0');
				GetModuleFileNameW( NULL, &tempStr[0], FILENAME_MAX);
				utf8::utf16to8(tempStr.begin(), tempStr.end(), back_inserter(processFileFullPath_pri));
				//std::cout << "\nprocessFileFullPath_pri" << processFileFullPath_pri << '\n';
				processFolderFullPath_pri = processFileFullPath_pri.substr(0, processFileFullPath_pri.find_last_of("\\"));
				#else
				readlink("/proc/self/exe", &processFileFullPath_pri[0], FILENAME_MAX);
				processFolderFullPath_pri = processFileFullPath_pri.substr(0, processFileFullPath_pri.find_last_of("/"));
				#endif
			}

			std::string processFileFullPath_f() const
			{
				return processFileFullPath_pri;
			}
			//DOES NOT contain the last /
			std::string processFolderFullPath_f() const
			{
				return processFolderFullPath_pri;
			}
	};

	const static processFile_c processFileInfo_glo_sta_con;
}
}

#endif /* COMUSO_PROCESSFILENAME_H_ */
