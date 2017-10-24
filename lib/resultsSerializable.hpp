//helper class that holds serveral ctos for the most used results on autocomplete results (JSON)
#ifndef COMUSO_SERIALIZEDRESULTSSERIALIZABLE_H_
#define COMUSO_SERIALIZEDRESULTSSERIALIZABLE_H_

#include "results.hpp"
#include "serialization.hpp"

#ifdef DEBUGJOUVEN
#include "backwardSTso/backward.hpp"
#include <iostream>
#endif

#include <vector>
#include <string>
#include <utility>

namespace eines
{
namespace resultsSerializable
{

struct autoCompleteResultSerializable_s : public results::autoCompleteResult_s
{
	//inherit ctors
	using autoCompleteResult_s::autoCompleteResult_s;
	autoCompleteResultSerializable_s(const results::autoCompleteResult_s& request_par_con)
	:
		results::autoCompleteResult_s(request_par_con)
	{}

	autoCompleteResultSerializable_s(const results::autoCompleteResult_s&& request_par_con)
	:
		results::autoCompleteResult_s(std::move(request_par_con))
	{}
	autoCompleteResultSerializable_s& operator=(results::autoCompleteResult_s&& srcMove_par_con)
	{
		 *this = std::move(srcMove_par_con);
		 return *this;
	}
	friend void operator<<=(cxxtools::SerializationInfo& si_par,
							const autoCompleteResultSerializable_s& obj_par_con)
	{
		if (obj_par_con.strKeySet_par_con)
		{
			si_par.addMember(obj_par_con.keyName_par_con) <<= cxxtools::Utf8Codec::decode(obj_par_con.strKey_par_con);
		}
		if (obj_par_con.intKeySet_par_con)
		{
			si_par.addMember(obj_par_con.keyName_par_con) <<= obj_par_con.intKey_par_con;
		}
		if(obj_par_con.strValueSet_par_con)
		{
			si_par.addMember(obj_par_con.valueName_par_con) <<= cxxtools::Utf8Codec::decode(obj_par_con.strValue_par_con);
		}
		if(obj_par_con.intValueSet_par_con)
		{
			si_par.addMember(obj_par_con.valueName_par_con) <<= obj_par_con.intValue_par_con;
		}
	}
};

template<typename T>
class dicResultSerializable_c : public results::dicResult_c<T>
{
	public:
		//inherit ctors
		//using dicResultSerializable_c::dicResult_c::dicResult_c;
		using results::dicResult_c<T>::dicResult_c;
		dicResultSerializable_c() = default;
		dicResultSerializable_c(const results::dicResult_c<T>& request_par_con)
		:  results::dicResult_c<T>(request_par_con)
		{}
		dicResultSerializable_c(const results::dicResult_c<T>&& request_par_con)
		:  results::dicResult_c<T>(std::move(request_par_con))
		{}
		dicResultSerializable_c& operator=(results::dicResult_c<T>&& srcMove_par_con)
		{
			 *this = std::move(srcMove_par_con);
			 return *this;
		}
//	    dicResultSerializable_c(results::dicResult_c<T>&& request_par_con)
//		:  results::dicResult_c<T>(request_par_con)
//		{}
		void addMembers_f(
		    cxxtools::SerializationInfo& si_par) const
		{
//#ifdef DEBUGJOUVEN
//			std::cout << DEBUGSOURCE << "(dicResultWeb_c) addMember other\n";
//#endif
			//for some reason it requires the this
			for (const auto& item_ite_con : this->vectorDic_pro)
			{
				if (not item_ite_con.first.empty())
				{
//#ifdef DEBUGJOUVEN
//			std::cout << DEBUGSOURCE << "(dicResultWeb_c) addMember other2\n";
//#endif
					si_par.addMember(item_ite_con.first) <<= item_ite_con.second;
				}
			}
		}

		friend void operator<<=(cxxtools::SerializationInfo& si_par,
		                        const dicResultSerializable_c& obj_par_con)
		{
			if (obj_par_con.id_pro > 0)
			{
				si_par.addMember("id") <<= obj_par_con.id_pro;
			}
			obj_par_con.addMembers_f(si_par);
		}
};

//string specialization for addMembers_f
template <> inline
void dicResultSerializable_c<std::string>::addMembers_f(
    cxxtools::SerializationInfo& si_par) const
{
//#ifdef DEBUGJOUVEN
//	std::cout << DEBUGSOURCE << "(dicResultWeb_c) addMember string\n";
//#endif
	for (const auto& item_ite_con : vectorDic_pro)
	{
		if (not item_ite_con.first.empty())
		{
			si_par.addMember(item_ite_con.first) <<= cxxtools::Utf8Codec::decode(item_ite_con.second);
		}
	}
}

}
}

#endif /* COMUSO_SERIALIZEDRESULTSSERIALIZABLE_H_ */
