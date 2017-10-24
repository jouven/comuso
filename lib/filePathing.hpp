#ifndef COMUSO_FILEPATHING_H_
#define COMUSO_FILEPATHING_H_

#ifdef DEBUGJOUVEN
#include "backwardSTso/backward.hpp"
#endif

#include <boost/filesystem.hpp>

namespace eines
{
namespace filePathing
{
//returns a boost::filesystem::path with the relative path between two boost::filesystem::path variables
//from should be the parent,
//i.e from is "/home/jouven" and to is "/home/jouven/eclipseprojects/test"
//returns "eclipseprojects/test"
inline boost::filesystem::path relativeTo_f(
	const boost::filesystem::path& from_par_con,
    const boost::filesystem::path& to_par_con)
{
	//warning! --> assuming that "from" path is parent of "to" path
	// Start at the root path and while they are the same then do nothing then when they first
	// diverge take the remainder of the two path and replace the entire from path with ".."
	// segments.
	boost::filesystem::path::const_iterator fromIter = from_par_con.begin();
	boost::filesystem::path::const_iterator toIter = to_par_con.begin();

	// Loop through both
	while (fromIter !=
	       from_par_con.end()) // && toIter != to.end() && (*toIter) == (*fromIter))
	{
		++toIter;
		++fromIter;
		//std::cout << "toIter: " << toIter->c_str() << '\n' ;
		//std::cout << "fromIter: " << fromIter->c_str() << '\n' ;
	}

	boost::filesystem::path finalPath;
	//   while (fromIter != from.end())
	//   {
	//      finalPath /= "..";
	//      ++fromIter;
	//   }

	while (toIter != to_par_con.end())
	{
		finalPath /= *toIter;
		++toIter;
	}

	return finalPath;
}

//returns a vector of boost::filesystem::path with all the files of the path, it does
//recurse folders
inline std::vector<boost::filesystem::path> getAllFileInPath_f(
    const boost::filesystem::path& basePath_par_con
    , const bool getFoldersToo_par_con = false)
{
	std::vector<boost::filesystem::path> vfiles;
	boost::filesystem::recursive_directory_iterator it(basePath_par_con);
	const boost::filesystem::recursive_directory_iterator endit;
	while (it != endit)
	{
		if (exists(*it) and (is_regular_file(*it) or (getFoldersToo_par_con and is_directory(*it))))
		{
			vfiles.emplace_back(it->path());
		}
		it = std::next(it);
	}
	return vfiles;
}

}
}

#endif /* COMUSO_FILEPATHING_H_ */
