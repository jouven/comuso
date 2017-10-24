//helper class that holds serveral ctos for the most used results on autocomplete results
#ifndef COMUSO_RESULTS_H_
#define COMUSO_RESULTS_H_

#ifdef DEBUGJOUVEN
#include "backwardSTso/backward.hpp"
#include <iostream>
#endif

#include <vector>
#include <string>
#include <utility>
#include <cstdint>

namespace eines
{
namespace results
{

struct autoCompleteResult_s
{
	std::string strKey_par_con;
	bool strKeySet_par_con = false;
	int_fast32_t intKey_par_con = INT_FAST32_MIN;
	bool intKeySet_par_con = false;
	int_fast32_t intValue_par_con = INT_FAST32_MIN;
	bool intValueSet_par_con = false;
	std::string strValue_par_con;
	bool strValueSet_par_con = false;

	std::string keyName_par_con = "id";
	std::string valueName_par_con = "text";

	autoCompleteResult_s() = default;

	autoCompleteResult_s(
		const std::string& key_par_con,
		const std::string& value_par_con) :
			strKey_par_con(key_par_con),
			strKeySet_par_con(true),
			strValue_par_con(value_par_con),
			strValueSet_par_con(true)
	{};
	autoCompleteResult_s(
		const std::string& key_par_con,
		const int_fast32_t value_par_con) :
			strKey_par_con(key_par_con),
			strKeySet_par_con(true),
			intValue_par_con(value_par_con),
			intValueSet_par_con(true)
	{};
	autoCompleteResult_s(
		const int_fast32_t key_par_con,
		const std::string& value_par_con) :
			intKey_par_con(key_par_con),
			intKeySet_par_con(true),
			strValue_par_con(value_par_con),
			strValueSet_par_con(true)
	{};
	autoCompleteResult_s(
		const int_fast32_t key_par_con,
		const int_fast32_t value_par_con) :
			intKey_par_con(key_par_con),
			intKeySet_par_con(true),
			intValue_par_con(value_par_con),
			intValueSet_par_con(true)
	{};

	autoCompleteResult_s(const autoCompleteResult_s& srcMove_par_con)
	:
		strKey_par_con(srcMove_par_con.strKey_par_con)
		, strKeySet_par_con(srcMove_par_con.strKeySet_par_con)
		, intKey_par_con(srcMove_par_con.intKey_par_con)
		, intKeySet_par_con(srcMove_par_con.intKeySet_par_con)
		, intValue_par_con(srcMove_par_con.intValue_par_con)
		, intValueSet_par_con(srcMove_par_con.intValueSet_par_con)
		, strValue_par_con(srcMove_par_con.strValue_par_con)
		, strValueSet_par_con(srcMove_par_con.strValueSet_par_con)
		, keyName_par_con(srcMove_par_con.keyName_par_con)
		, valueName_par_con(srcMove_par_con.valueName_par_con)
	{}

	autoCompleteResult_s(const autoCompleteResult_s&& srcMove_par_con)
	:
		strKey_par_con(std::move(srcMove_par_con.strKey_par_con))
		, strKeySet_par_con(std::move(srcMove_par_con.strKeySet_par_con))
		, intKey_par_con(std::move(srcMove_par_con.intKey_par_con))
		, intKeySet_par_con(std::move(srcMove_par_con.intKeySet_par_con))
		, intValue_par_con(std::move(srcMove_par_con.intValue_par_con))
		, intValueSet_par_con(std::move(srcMove_par_con.intValueSet_par_con))
		, strValue_par_con(std::move(srcMove_par_con.strValue_par_con))
		, strValueSet_par_con(std::move(srcMove_par_con.strValueSet_par_con))
		, keyName_par_con(std::move(srcMove_par_con.keyName_par_con))
		, valueName_par_con(std::move(srcMove_par_con.valueName_par_con))
	{}
	autoCompleteResult_s& operator=(autoCompleteResult_s&& srcMove_par_con)
	{
		strKey_par_con = std::move(srcMove_par_con.strKey_par_con);
		strKeySet_par_con = std::move(srcMove_par_con.strKeySet_par_con);
		intKey_par_con = std::move(srcMove_par_con.intKey_par_con);
		intKeySet_par_con = std::move(srcMove_par_con.intKeySet_par_con);
		intValue_par_con = std::move(srcMove_par_con.intValue_par_con);
		intValueSet_par_con = std::move(srcMove_par_con.intValueSet_par_con);
		strValue_par_con = std::move(srcMove_par_con.strValue_par_con);
		strValueSet_par_con = std::move(srcMove_par_con.strValueSet_par_con);
		keyName_par_con = std::move(srcMove_par_con.keyName_par_con);
		valueName_par_con = std::move(srcMove_par_con.valueName_par_con);
		return *this;
	}
};

//mainly used to return results, like X updates, Y deletions... etc
template<typename T>
class dicResult_c
{
	protected:
		int_fast32_t id_pro = 0;
		bool idSet_pro = false;
		std::vector<std::pair<std::string, T>> vectorDic_pro;
	public:
		dicResult_c() = default;
		dicResult_c(
		    const std::vector<std::pair<std::string, T>>& vectorDic_par_con) :
			vectorDic_pro(vectorDic_par_con)
		{};
		dicResult_c(
			const int_fast32_t id_par_con,
		    const std::vector<std::pair<std::string, T>>& vectorDic_par_con) :
		    id_pro(id_par_con)
		    , idSet_pro(id_par_con > 0)
			, vectorDic_pro(vectorDic_par_con)
		{};
		dicResult_c(const dicResult_c<T>& src_par_con)
		:
			id_pro(src_par_con.id_pro)
			, idSet_pro(src_par_con.id_pro > 0)
			, vectorDic_pro(src_par_con.vectorDic_pro)
		{}

		dicResult_c(const dicResult_c<T>&& srcMove_par_con)
		:
			id_pro(std::move(srcMove_par_con.id_pro))
			, idSet_pro(srcMove_par_con.id_pro > 0)
			, vectorDic_pro(std::move(srcMove_par_con.vectorDic_pro))
		{}
		dicResult_c& operator=(dicResult_c&& src_par_con)
		{
			 id_pro = std::move(src_par_con.id_pro);
			 vectorDic_pro = std::move(src_par_con.vectorDic_pro);
			 return *this;
		}
		void setId_f(const int_fast32_t id_par_con)
		{
			id_pro = id_par_con;
		    idSet_pro = id_par_con > 0;
		}
		bool empty() const
		{
			return vectorDic_pro.empty() and id_pro == -1;
		}

		int_fast32_t getId_f() const
		{
			return id_pro;
		}
		std::vector<std::pair<std::string, T>> getDic_f() const
		{
			return vectorDic_pro;
		}
		void insertPair_f(const std::string& first_par_con, const T& second_par_con)
		{
			vectorDic_pro.emplace_back(first_par_con, second_par_con);
		}
		void insert_f(const std::pair<std::string, T>& item_par_con)
		{
			vectorDic_pro.emplace_back(item_par_con);
		}
		void insert_f(const std::pair<std::string, T>&& item_par_con)
		{
			vectorDic_pro.emplace_back(std::move(item_par_con));
		}
		//tries to add up the value if an item with the same "key" is found
		//else inserts it
		void addUpPairValue_f(
			const std::string& first_par_con,
			const T& second_par_con
		)
		{
			for (auto& i_ite : vectorDic_pro)
			{
				if (i_ite.first == first_par_con)
				{
					i_ite.second = i_ite.second + second_par_con;
					return;
				}
			}
			vectorDic_pro.emplace_back(first_par_con, second_par_con);
		}
		//tries to add up the value if an item with the same "key" is found
		//else inserts it
		void addUpValue_f(const std::pair<std::string, T>& item_par_con)
		{
			for (auto& i_ite : vectorDic_pro)
			{
				if (i_ite.first == item_par_con.first)
				{
					i_ite.second = i_ite.second + item_par_con.second;
					return;
				}
			}
			vectorDic_pro.emplace_back(item_par_con);
		}
		void addUpValue_f(const std::pair<std::string, T>&& item_par_con)
		{
			for (auto& i_ite : vectorDic_pro)
			{
				if (i_ite.first == item_par_con.first)
				{
					i_ite.second = i_ite.second + item_par_con.second;
					return;
				}
			}
			vectorDic_pro.emplace_back(std::move(item_par_con));
		}
		void addDic_f(const std::vector<std::pair<std::string, T>>& vectorDic_par_con)
		{
			for (const auto& item_ite_con : vectorDic_par_con)
			{
				addUpValue_f(item_ite_con);
			}
		}
		void addDic_f(const std::vector<std::pair<std::string, T>>&& vectorDic_par_con)
		{
			for (const auto& item_ite_con : vectorDic_par_con)
			{
				addUpValue_f(std::move(item_ite_con));
			}
		}
		void addDic_f(const dicResult_c<T>& dic_par_con)
		{
			for (const auto& item_ite_con : dic_par_con.getDic_f())
			{
				addUpValue_f(item_ite_con);
			}
		}
		void addDic_f(const dicResult_c<T>&& dic_par_con)
		{
			for (const auto& item_ite_con : dic_par_con.getDic_f())
			{
				addUpValue_f(std::move(item_ite_con));
			}
		}
};

}
}

#endif /* COMUSO_RESULTS_H_ */
