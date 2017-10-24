
#ifndef COMUSO_BENCHMARKTEMPLATES_H_
#define COMUSO_BENCHMARKTEMPLATES_H_

#include "chartJS.hpp"

#ifdef DEBUGJOUVEN
#include "backwardSTso/backward.hpp"
#include "comuso/loggingMacros.hpp"
#include <iostream>
#endif

#include <chrono>
#include <mutex>

namespace eines
{

class benchClass_c
{
		chartjs::datasetInternal_c obj_pri;
		const bool smallerIsBetter_pri_con = true;
		std::mutex updateLock_pri;
	public:
		benchClass_c() = default;
		benchClass_c(const bool smallerIsBetter_par_con)
		: smallerIsBetter_pri_con(smallerIsBetter_par_con)
		{}

		template<typename T>
		T benchFunction_f(
			const std::function<T()>& func_par_con
			, const std::string& case_par_con
			, const std::string& label_par_con
		)
		{
			auto start(std::chrono::steady_clock::now());

			T returnResult(func_par_con());

			auto end(std::chrono::steady_clock::now());

			auto elapsed(std::chrono::duration_cast<std::chrono::milliseconds>(
							   end - start));
			std::lock_guard<std::mutex> lock(updateLock_pri);
			obj_pri.upsertIfBetterValue(case_par_con, label_par_con, elapsed.count(), smallerIsBetter_pri_con);

			return returnResult;
		}
		void benchFunction_f(
			const std::function<void()>& func_par_con
			, const std::string& case_par_con
			, const std::string& label_par_con
		)
		{
			auto start(std::chrono::steady_clock::now());

			func_par_con();

			auto end(std::chrono::steady_clock::now());

			auto elapsed(std::chrono::duration_cast<std::chrono::milliseconds>(
							   end - start));
			obj_pri.upsertIfBetterValue(case_par_con, label_par_con, elapsed.count(), smallerIsBetter_pri_con);
		}

		std::string getDeserializedStr() const
		{
			return eines::serialization::serializeJSON_f(obj_pri);
		}
		bool addNewLabel(const std::string& label_par_con)
		{
			return obj_pri.addNewLabel(label_par_con);
		}
		std::pair<int_fast64_t, bool> getValue(
			const std::string& case_par_con
			, const std::string& label_par_con
		)
		{
			return obj_pri.getValue(case_par_con, label_par_con);
		}
};


}
#endif /* COMUSO_BENCHMARKTEMPLATES_H_ */
