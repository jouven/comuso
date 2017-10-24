#ifndef COMUSO_PAGING_H_
#define COMUSO_PAGING_H_

#include "boost/lexical_cast.hpp"

#include <string>
#include <cstdint>

#ifdef DEBUGJOUVEN
#include "backwardSTso/backward.hpp"
#include <iostream>
#endif

namespace eines
{
namespace paging
{

//template<typename T>
//class pagingResults_c
//{
//	protected:
//		T _resultsContainer;
//	public:
//		pagingResults_c() = default;
//		pagingResults_c(
//		    const T& resultsContainer) :
//				_resultsContainer(resultsContainer)
//		{}
//		bool empty() const
//		{
//			return _resultsContainer.empty();
//		}
//};
struct paging_s
{
		int_fast32_t start_pub = 0;
		int_fast32_t limit_pub = 0;
		paging_s() = default;
		paging_s(
			const int_fast32_t start_par_con,
			const int_fast32_t limit_par_con)
			:
			start_pub(start_par_con)
			, limit_pub(limit_par_con)
		{}
		//warning it adds the order by + orderByField
		std::string getQueryPaginationStr_f(
			const std::string orderByField_par_con) const
		{
			std::string limitStr;
			std::string offsetStr;
			std::string paginationQueryString;
			if (boost::conversion::try_lexical_convert(limit_pub, limitStr)
				and boost::conversion::try_lexical_convert(start_pub, offsetStr))
			{
				paginationQueryString.append(
					R"( order by )" + orderByField_par_con +
					R"( limit )" +
					limitStr +
					R"( offset )" +
					offsetStr
				);
			}
			else
			{
				paginationQueryString.append(
					 R"( order by )" + orderByField_par_con +
					 R"( limit 10)"
					 R"( offset 0)"
				);
			}
			return paginationQueryString;
		}
};

}
}
#endif /* COMUSO_PAGING_H_ */
