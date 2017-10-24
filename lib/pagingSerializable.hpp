#ifndef COMUSO_PAGINGSERIALIZABLE_H_
#define COMUSO_PAGINGSERIALIZABLE_H_

//#include "paging.hpp"

#include "boost/lexical_cast.hpp"

#include <string>
#include <cxxtools/json.h>
#include <cstdint>

#ifdef DEBUGJOUVEN
#include "backwardSTso/backward.hpp"
#include <iostream>
#endif

#define MACRO_paginationDeserializationBlock \
	si_par_con.getMember("start", obj_par.start_pub); \
	if (obj_par.start_pub < 0) obj_par.start_pub = 0; \
	si_par_con.getMember("limit", obj_par.limit_pub); \
	if (obj_par.limit_pub > 200 or obj_par.limit_pub < 1) obj_par.limit_pub = 10; \
	si_par_con.getMember("draw", obj_par.draw_pub);

namespace eines
{
namespace pagingSerializable
{

template <typename T>
class pagingResultsSerializable_c //: public paging::pagingResults_c<T>
{
	private:
		const T resultsContainer_pri_con;
		const int_fast32_t draw_pri_con = 0;
	public:
		pagingResultsSerializable_c() = default;
		pagingResultsSerializable_c(
		    const T& resultsContainer_par_con,
			const int_fast32_t draw_par_con) :
				resultsContainer_pri_con(resultsContainer_par_con)
				,draw_pri_con(draw_par_con)
		{}
		bool empty() const
		{
			return resultsContainer_pri_con.empty();
		}
		friend void operator<<=(cxxtools::SerializationInfo& si_par,
		                        const pagingResultsSerializable_c& obj_par_con)
		{
			if (obj_par_con.draw_pri_con > 0)
			{
				si_par.addMember("draw") <<= (obj_par_con.draw_pri_con+1);
			}
			si_par.addMember("results") <<= obj_par_con.resultsContainer_pri_con;
		}
};

//use with MACRO_paginationDeserializationBlock
//this is alone here, because paging normally wouldn't require this but datatables does
struct dataTablesSerializable_s
{
		int_fast32_t draw_pub = 0;
//		pagingSerializable_s() = default;
//		pagingSerializable_s(
//			const int_fast32_t start,
//			const int_fast32_t limit)
//			: paging::paging_s(start ,limit)
//		{}
};

}
}
#endif /* COMUSO_PAGINGSERIALIZABLE_H_ */
