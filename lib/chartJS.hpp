
#ifndef COMUSO_CHARTJS_H_
#define COMUSO_CHARTJS_H_

#include "practicalTemplates.hpp"
#include "serialization.hpp"

#include <boost/lexical_cast.hpp>

#ifdef DEBUGJOUVEN
#include "loggingMacros.hpp"
#include "backwardSTso/backward.hpp"
#include <iostream>
#endif

#include <string>
#include <utility>
#include <map>
#include <vector>

namespace eines
{
namespace chartjs
{
//helper class to serialize/deserialize chart.js results
struct datesetExternal_s
{
		std::string caseLabel_pub;
		//data->a string is ued to store numbers,
		//but because there is no number for NaN, and it's relevant
		//when displaying a situation with no value
		std::vector<std::string> data_pub;
		datesetExternal_s() = default;
		datesetExternal_s(
			const std::string& caseLabel_par_con
			, const std::vector<std::string>& data_par_con
		)
			:
			caseLabel_pub(caseLabel_par_con)
			, data_pub(data_par_con)
		{}
		friend void operator<<=(
			cxxtools::SerializationInfo& si_par,
			const datesetExternal_s& obj_par_con
		)
		{
			si_par.addMember("label") <<= cxxtools::Utf8Codec::decode(obj_par_con.caseLabel_pub);
			//data it just numbers and NaN
			si_par.addMember("data") <<= obj_par_con.data_pub;
		}
		friend void operator>>=(const cxxtools::SerializationInfo& si_par_con,
							datesetExternal_s& obj_par)
		{
			cxxtools::String tmpUtf8;
			si_par_con.getMember("label", tmpUtf8);
			obj_par.caseLabel_pub = cxxtools::Utf8Codec::encode(tmpUtf8);
			si_par_con.getMember("data", obj_par.data_pub);
		}
};

class datasetInternal_c
{
		//the key of the outer container identifies a specific configuration/case
		//the key of the subcontainer is X axis value, a label, a variation common to all cases
		//the value of the subcontainer is the proper value (Y axis value)
		std::map<std::string, std::map<std::string, int_fast64_t>> values_pri;

		//labels / Xvalues custom ordered, the order is relevant when deserializing into JSON.
		//It governs the labels, if values_pri has other labels, they will be ignored
		//when doing class operations
		std::vector<std::string> labels_pri;
		bool conflict_pri = false;

		void modifyValueSpecial(
			const std::string& case_par_con
			, const std::string& label_par_con
			, const int_fast64_t YValue_par_con
		)
		{
			values_pri[case_par_con][label_par_con] = YValue_par_con;
		}
	public:
		datasetInternal_c() = default;
		datasetInternal_c(
			const std::map<std::string, std::map<std::string, int_fast64_t>>& values_par_con
			, const std::vector<std::string>& labels_par_con
		)
			: values_pri(values_par_con)
			, labels_pri(labels_par_con)
		{
			//simplement mirar si labels te duplicats
			std::vector<std::string> labelsTmp(labels_pri);
			removeDuplicates_ft(labelsTmp);
			if (labels_pri.size() != labelsTmp.size())
			{
				conflict_pri = true;
			}
			if (conflict_pri)
			{
				values_pri.clear();
				labels_pri.clear();
				conflict_pri = true;
			}
		}
		bool empty() const
		{
			return values_pri.empty() or labels_pri.empty();
		}
		bool getConflict() const
		{
			return conflict_pri;
		}
		std::vector<std::string> getLabels() const
		{
			return labels_pri;
		}
		int_fast64_t getLabelPosition(const std::string& label_par_con) const
		{
			return getValuePosition_ft(labels_pri, label_par_con);
		}
		//removes a case
		int_fast32_t removeCase(const std::string& case_par_con)
		{
			return values_pri.erase(case_par_con);
		}
		//tries to get an existing value
		std::pair<int_fast64_t, bool> getValue(
			const std::string& case_par_con
			, const std::string& label_par_con
		)
		{
			int_fast64_t value;
			bool found(false);
			if (values_pri.find(case_par_con) != values_pri.end()
				and values_pri[case_par_con].find(label_par_con) != values_pri[case_par_con].end())
			{
				value = values_pri[case_par_con][label_par_con];
				found = true;
			}
			return std::make_pair(value, found);
		}
		//tries to modify an existing value
		bool modifyValue(
			const std::string& case_par_con
			, const std::string& label_par_con
			, const int_fast64_t YValue_par_con
		)
		{
			bool modified(false);
			if (values_pri.find(case_par_con) != values_pri.end()
				and values_pri[case_par_con].find(label_par_con) != values_pri[case_par_con].end())
			{
				values_pri[case_par_con][label_par_con] = YValue_par_con;
				modified = true;
			}
			return modified;
		}
		//if the label exists, add/update the case with the value
		bool addValue(
			const std::string& case_par_con
			, const std::string& label_par_con
			, const int_fast64_t YValue_par_con
		)
		{
			bool added(false);
			if (std::find(labels_pri.begin(), labels_pri.end(), label_par_con) != labels_pri.end())
			{
				values_pri[case_par_con][label_par_con] = YValue_par_con;
				added = true;
			}
			return added;
		}
		//same as addvalue but only replaces the value if its better
		bool upsertIfBetterValue(
			const std::string& case_par_con
			, const std::string& label_par_con
			, const int_fast64_t YValue_par_con
			//else greater is better
			, const bool smallerIsBetter_par_con
		)
		{
			bool upserted(false);
			auto resultTmp(getValue(case_par_con, label_par_con));
			if (not resultTmp.second)
			{
				upserted = addValue(case_par_con, label_par_con, YValue_par_con);
			}
			else
			{
				if ((smallerIsBetter_par_con and resultTmp.first > YValue_par_con)
					or (not smallerIsBetter_par_con and resultTmp.first < YValue_par_con))
				{
					modifyValueSpecial(case_par_con, label_par_con, YValue_par_con);
					upserted = true;
				}
			}
			return upserted;
		}


		bool hasLabel(const std::string& label_par_con) const
		{
			return (std::find(labels_pri.begin(), labels_pri.end(), label_par_con) != labels_pri.end());
		}
//		bool hasLabel(const std::pair<std::string, int_fast64_t>& label_par_con) const
//		{
//			return (std::find(labels_pri.begin(), labels_pri.end(), label_par_con.first) != labels_pri.end());
//		}
		//add case, optionally values for each label
		//this operation doesn't add or remove labels
		//so if the labels, in keyLabelValueYValue_par_con, don't exist it doesn't matter
		void addCase(
			const std::string& case_par_con
			, std::map<std::string, int_fast64_t> keyLabelValueYValue_par = std::map<std::string, int_fast64_t>()
		)
		{
			removeIfPredicateTrue_ft(
				keyLabelValueYValue_par,
				[&](const typename std::map<std::string, int_fast64_t>::const_iterator& tmp)
					{ return not hasLabel(tmp->first);}
			);
			values_pri.emplace(case_par_con, keyLabelValueYValue_par);
		}
		//in the umap it must have a new value for each case already in values_pri
		//the label/XValue is added at the end/back
		bool addNewLabel(
			const std::string& label_par_con,
			const std::map<std::string, int_fast64_t>& casePerYValue_par_con = std::map<std::string, int_fast64_t>()
		)
		{
			bool added(false);
			if (std::find(labels_pri.begin(), labels_pri.end(), label_par_con) == labels_pri.end())
			{
				labels_pri.emplace_back(label_par_con);
				for (const auto& casePair_ite_con : casePerYValue_par_con)
				{
					if (values_pri.find(casePair_ite_con.first) != values_pri.end())
					{
						values_pri[casePair_ite_con.first][label_par_con] = casePair_ite_con.second;
					}
				}
				added = true;
			}
			return added;
		}

		//removes the label, and the label values in each case that has this label
		int_fast32_t removeLabel(const std::string& label_par_con)
		{
			int_fast32_t erasedCounter(0);
			for (auto& pair_ite_con : values_pri)
			{
				erasedCounter += pair_ite_con.second.erase(label_par_con);
			}
			labels_pri.erase(std::find(labels_pri.begin(), labels_pri.end(), label_par_con));
			return erasedCounter;
		}
		//for one case remove its value (just remove the label key)
		bool removeCaseValue(
			const std::string& case_par_con
			, const std::string& label_par_con
		)
		{
			int_fast32_t erasedCounter(0);
			if (values_pri.find(case_par_con) != values_pri.end()
				and values_pri[case_par_con].find(label_par_con) != values_pri[case_par_con].end())
			{
				values_pri[case_par_con].erase(label_par_con);
			}
			return erasedCounter;
		}

		friend void operator<<=(cxxtools::SerializationInfo& si_par,
							const datasetInternal_c& obj_par_con)
		{
			std::vector<cxxtools::String> labels;
			labels.reserve(obj_par_con.labels_pri.size());
			for (const auto& label_ite_con : obj_par_con.labels_pri)
			{
				labels.emplace_back(cxxtools::Utf8Codec::decode(label_ite_con));
			}
			si_par.addMember("labels") <<= labels;


			std::map<std::string, std::vector<std::string>> valuesPerCase;
			//valuesPerCase.reserve(obj_par_con.values_pri.size());
			for (const auto& casePair_ite_con : obj_par_con.values_pri)
			{
				valuesPerCase.emplace(casePair_ite_con.first, std::vector<std::string>());
				valuesPerCase[casePair_ite_con.first].reserve(obj_par_con.labels_pri.size());
				for (const auto& label_ite_con : obj_par_con.labels_pri)
				{
					if (casePair_ite_con.second.find(label_ite_con) != casePair_ite_con.second.end())
					{
						std::string tmp;
						boost::conversion::try_lexical_convert(casePair_ite_con.second.at(label_ite_con), tmp);
						valuesPerCase[casePair_ite_con.first].emplace_back(tmp);
					}
					else
					{
						valuesPerCase[casePair_ite_con.first].emplace_back("NaN");
					}
				}
			}


			std::vector<datesetExternal_s> datasets;
			datasets.reserve(valuesPerCase.size());
			for (auto&& itemPair_ite_con : valuesPerCase)
			{
				datasets.emplace_back(itemPair_ite_con.first, itemPair_ite_con.second);
			}
			si_par.addMember("datasets") <<= datasets;
		}
		friend void operator>>=(const cxxtools::SerializationInfo& si_par_con,
							datasetInternal_c& obj_par)
		{
			std::vector<cxxtools::String> vector_tmpUtf8;
			si_par_con.getMember("labels", vector_tmpUtf8);
			if (not vector_tmpUtf8.empty())
			{
				obj_par.labels_pri.reserve(vector_tmpUtf8.size());
				for (const auto& labelTextId_ite_con : vector_tmpUtf8)
				{
					obj_par.labels_pri.emplace_back(
						cxxtools::Utf8Codec::encode(labelTextId_ite_con)
					);
				}
			}
			removeDuplicates_ft(obj_par.labels_pri);

			std::vector<datesetExternal_s> datasets;
			si_par_con.getMember("datasets", datasets);
			for (const auto& dataset_ite_con : datasets)
			{
				obj_par.addCase(dataset_ite_con.caseLabel_pub);
				int_fast32_t indexTmp(0);
				for (const auto& caseValue_ite_con : dataset_ite_con.data_pub)
				{
					int_fast64_t intTmp(0);
					if (caseValue_ite_con != "NaN" and boost::conversion::try_lexical_convert(caseValue_ite_con, intTmp))
					{
						obj_par.addValue(dataset_ite_con.caseLabel_pub, obj_par.labels_pri[indexTmp], intTmp);
					}
					indexTmp = indexTmp + 1;
				}
			}
		}
};

}
}
#endif /* COMUSO_CHARTJS_H_ */
