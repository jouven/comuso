//to get if two containers have the same elements std::is_permutation

#ifndef COMUSO_PRACTICALTEMPLATES_H_
#define COMUSO_PRACTICALTEMPLATES_H_


#ifdef DEBUGJOUVEN
#include "macros.hpp"
#include "backwardSTso/backward.hpp"
#include "comuso/loggingMacros.hpp"
#include <iostream>
#endif

#include <algorithm>
#include <iterator>
#include <vector>
#include <functional>


template <typename T, typename U>
bool equalOnce_ft(
	const T &a_par_con
	, const U &b_par_con)
{
    return a_par_con == b_par_con;
}

template <typename T, typename U, typename... Others>
bool equalOnce_ft(
	const T &a_par_con
	, const U &b_par_con
	, Others const &... others_par_con)
{
    return (a_par_con == b_par_con)
    	or equalOnce_ft(a_par_con, others_par_con...);
}

//use only on sortable non unique containers
template <typename T>
void removeDuplicates_ft(T& obj_par)
{
	std::sort(obj_par.begin(), obj_par.end());
	obj_par.erase(
		std::unique(
			obj_par.begin(),
			obj_par.end())
		, obj_par.end()
	);
}


template<typename T>
uint_fast32_t removeIfPredicateTrue_ft(T& obj_par, const std::function<bool(const typename T::const_iterator&)>& func_par_con)
{
	uint_fast32_t countTmp(0);
	for (auto it = obj_par.cbegin(); it != obj_par.cend() /* not hoisted */; /* no increment */)
	{
		if (func_par_con(it))
		{
			it = obj_par.erase(it);
			countTmp = countTmp + 1;
		}
		else
		{
			++it;
		}
	}
	return countTmp;
}

//removes anything smaller than 1
//useful for DB Ids/sequences that usually start at 1
template <typename T>
void removeNonPositive_ft(T& obj_par)
{
	obj_par.erase(std::remove_if(obj_par.begin(), obj_par.end(),
		[](const auto number_ite_con) { return number_ite_con < 1; }), obj_par.end());
}

//removes anything smaller than 0
//useful for 0 index starting stuff
template <typename T>
void removeNegative_ft(T& obj_par)
{
	obj_par.erase(std::remove_if(obj_par.begin(), obj_par.end(),
		[](const auto number_ite_con) { return number_ite_con < 0; }), obj_par.end());
}

template <typename T>
void removeEmpty_ft(T& obj_par)
{
	obj_par.erase(std::remove_if(obj_par.begin(), obj_par.end(),
		[](const auto& item_ite_con) { return item_ite_con.empty(); }), obj_par.end());
}

template <typename T, typename U>
bool allEqual_ft(
	const T &a_par_con
	, const U &b_par_con)
{
    return a_par_con == b_par_con;
}

template <typename T, typename U, typename... Others>
bool allEqual_ft(
	const T &a_par_con
	, const U &b_par_con
	, Others const &... others_par_con)
{
    return (a_par_con == b_par_con)
    	and allEqual_ft(a_par_con, others_par_con...);
}

//use to create std::unordered_map<actions, bool, EnumClassHash> actionsRequireLoginMap
//this works because it "converts" the enums to integer (which "they are" already)
//and every enum element has a different value underneath
struct EnumClassHash
{
    template <typename T>
    std::size_t operator()(const T& obj_par) const
    {
        return static_cast<std::size_t>(obj_par);
    }
};

////the dots (variadic template) is needed because even though std::vector (and other containers)
////normally uses one template parameter
////it truly has another one, the allocator with default value, and when using templates it requires to explicitly
////put every one, using the variadic syntax allows to use the default value
//template<typename T, template <typename ...> class ContainerDerived, typename U, template <typename ...> class ContainerBase>
////template <typename T, typename U, template <U> class W>
//ContainerBase<U> basecastContainer_f(const ContainerDerived<T>& containerWithDerived)
//{
//	ContainerBase<U> result;
//	if (not containerWithDerived.empty())
//	{
//		result.reserve(containerWithDerived.size());
//		for (const auto& item_ite_con : containerWithDerived)
//		{
//			result.emplace_back(item_ite_con);
//		}
//	}
//	return result;
//}

//the dots (variadic template) is needed because even though std::vector (and other containers)
//normally uses one template parameter
//it truly has another one, the allocator with default value, and when using templates it requires to explicitly
//put every one, using the variadic syntax allows to use the default value
template<typename T, template <typename ...> class ContainerBase, typename U, template <typename ...> class ContainerDerived>
ContainerDerived<U> moveContainer_ft(const ContainerBase<T>&& containerWithBase)
{
	ContainerDerived<U> result;
	if (not containerWithBase.empty())
	{
		result.reserve(containerWithBase.size());
		for (const auto& item_ite_con : containerWithBase)
		{
			result.emplace_back(std::move(item_ite_con));
		}
	}
	return result;
}

template <typename T, template <typename ...> class Container>
bool insertIfNotExists_ft(const T& item, Container<T>& container)
{
	for (const auto& containerItem_ite_con : container)
	{
		if (item == containerItem_ite_con)
		{
			return false;
		}
	}
	container.emplace_back(item);
	return true;
}

template<class T, class Container>
bool containsOnce_ft(const Container& container_par_con, const T& value_par_con)
{
	return container_par_con.cend() != std::find(container_par_con.cbegin(), container_par_con.cend(), value_par_con);
}

template<typename T>
std::vector<T> copySplitVectors_ft(
	const T& vectorToSplit_par_con
	, const int_fast32_t splitSize_par_con
)
{
	int_fast32_t foundVectorSize(vectorToSplit_par_con.size());
//#ifdef DEBUGJOUVEN
//	std::cout << "foundVectorSize: " << foundVectorSize << std::endl;
//#endif
	size_t lastChunk(foundVectorSize % splitSize_par_con);
//#ifdef DEBUGJOUVEN
//	std::cout << "lastChunk: " << lastChunk << std::endl;
//#endif
	int_fast32_t numberOfParts(foundVectorSize / splitSize_par_con);
//#ifdef DEBUGJOUVEN
//	std::cout << "numberOfParts: " << numberOfParts << std::endl;
//#endif

	std::vector<T> splitting;
	splitting.reserve(numberOfParts + (lastChunk > 0 ? 1 : 0));
	for (int_fast32_t i = 0, l = numberOfParts; i < l; ++i)
	{
		T tmpVector(vectorToSplit_par_con.begin() + (i * splitSize_par_con), vectorToSplit_par_con.begin() + ((i+1) * splitSize_par_con));
		splitting.emplace_back(tmpVector);
	}
	if (lastChunk > 0)
	{
		T tmpVector(vectorToSplit_par_con.begin() + (numberOfParts * splitSize_par_con), vectorToSplit_par_con.begin() + (numberOfParts * splitSize_par_con) + lastChunk);
		splitting.emplace_back(tmpVector);
	}

//#ifdef DEBUGJOUVEN
//	{
//		int_fast32_t counter(0);
//		for (const auto& splitItem_ite_con : splitting)
//		{
//			counter = counter + splitItem_ite_con.size();
//		}
//		std::cout << "counter: " << counter << std::endl;
//	}
//#endif
	return splitting;
}

template<typename T>
std::vector<T> moveSplitVectors_ft(
	T&& vectorToSplit_par_con
	, const int_fast32_t splitSize_par_con
) noexcept
{
	int_fast32_t foundVectorSize(vectorToSplit_par_con.size());
//#ifdef DEBUGJOUVEN
//	std::cout << "foundVectorSize: " << foundVectorSize << std::endl;
//#endif
	size_t lastChunk(foundVectorSize % splitSize_par_con);
//#ifdef DEBUGJOUVEN
//	//std::cout << "lastChunk: " << lastChunk << std::endl;
//#endif
	int_fast32_t numberOfParts(foundVectorSize / splitSize_par_con);
//#ifdef DEBUGJOUVEN
//	std::cout << "numberOfParts: " << numberOfParts << std::endl;
//#endif

	std::vector<T> splitting;
	splitting.reserve(numberOfParts + (lastChunk > 0 ? 1 : 0));
	for (int_fast32_t i = 0, l = numberOfParts; i < l; ++i)
	{
		T tmpVector(
			std::make_move_iterator(vectorToSplit_par_con.begin() + (i * splitSize_par_con))
			, std::make_move_iterator(vectorToSplit_par_con.begin() + ((i+1) * splitSize_par_con))
		);
		splitting.emplace_back(std::move(tmpVector));
	}
	if (lastChunk > 0)
	{
		T tmpVector(
			std::make_move_iterator(vectorToSplit_par_con.begin() + (numberOfParts * splitSize_par_con))
			, std::make_move_iterator(vectorToSplit_par_con.begin() + (numberOfParts * splitSize_par_con) + lastChunk));
		splitting.emplace_back(std::move(tmpVector));
	}

//#ifdef DEBUGJOUVEN
//	{
//		int_fast32_t counter(0);
//		for (const auto& splitItem_ite_con : splitting)
//		{
//			counter = counter + splitItem_ite_con.size();
//		}
//		std::cout << "counter: " << counter << std::endl;
//	}
//#endif
	return splitting;
}

template<class T, class Container>
int_fast64_t getValuePosition_ft(
	const Container& container_par_con
	, const T& value_par_con)
{
	auto it( std::find(container_par_con.begin(), container_par_con.end(), value_par_con));
	if (it == container_par_con.end())
	{
		return -1;
	}
	else
	{
		return std::distance(container_par_con.begin(), it);
	}
}

#endif /* COMUSO_PRACTICALTEMPLATES_H_ */
