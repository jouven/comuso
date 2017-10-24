#ifndef COMUSO_EMAILVALIDATION_H_
#define COMUSO_EMAILVALIDATION_H_

#include "practicalTemplates.hpp"
#include "boost/asio/ip/address.hpp"

#ifdef DEBUGJOUVEN
#include "comuso/loggingMacros.hpp"
#endif

#include <string>

namespace eines
{
namespace email
{

//based-improved on http://archive.oreilly.com/network/excerpt/spcookbook_chap03/index3.html
//

//bool isValid(const char *address)
//{
inline bool isValidFormat_f(const std::string& address_par_con)
{
	if (address_par_con.empty())
	{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
		return false;
	}
	if (address_par_con.front() == '.')
	{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
		return false;
	}
	if (address_par_con.front() <= ' ' or address_par_con.front() == 127 or address_par_con.back() <= ' ')
	{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
		return false;
	}

	if (address_par_con.size() > 254)
	{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
		return false;
	}

	//case ".+"@ and the last " before isn't escaped
	uint_fast32_t index(0);
	if (address_par_con.front() == '\"')
	{
		bool isValid(false);
		while (index + 1 < address_par_con.size())
		{
			++index;
			//if (address[index] <= ' ' or address[index] == 127)
			if (address_par_con[index] == 127)
			{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
				return false;
			}
			//check for escaping and the following character
			if ((index + 1 < address_par_con.size()) and address_par_con[index] == '\\' and (address_par_con[index + 1] == '\"'))
			{
				++index;
				continue;
			}
			//check for the closing quotes and the following @
			if ((index + 1 < address_par_con.size()) and address_par_con[index] == '\"' and (address_par_con[index + 1] == '@'))
			{
				isValid = true;
				//advance to the @
				++index;
				break;
			}
		}
		if (not isValid)
		{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
			return false;
		}
	}
	else
	{
		//everything else and possible case .+\.".+"\..+@, not in the first position, a dot and then quotes after
		for (index = 0; index < address_par_con.size(); ++index)
		{
			if (address_par_con[index] <= ' ' or address_par_con[index] == 127)
			{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
				return false;
			}
			if (index + 2 < address_par_con.size() and address_par_con[index] != '\\' and address_par_con[index + 1] == '.' and address_par_con[index + 2] == '\"')
			{
				index = index + 2;
				bool isValid(false);
				while (index + 1 < address_par_con.size())
				{
					++index;
					if (address_par_con[index] <= ' ' or address_par_con[index] == 127)
					{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
						return false;
					}
					if (index + 1 < address_par_con.size() and address_par_con[index] == '\"' and address_par_con[index + 1] == '.')
					{
						isValid = true;
						break;
					}
				}
				if (not isValid)
				{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
					return false;
				}
			}
			else
			{
				//
				if (equalOnce_f(address_par_con[index],'\"','(',')',',',':',';','<','>','[','\\',']'))
				{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
					return false;
				}
				if (address_par_con[index] == '@')
				{
					break;
				}
				if (index + 1 < address_par_con.size() and address_par_con[index] == '.' and address_par_con[index + 1] == '.')
				{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
					return false;
				}
			}
		}
	}
	//go past the @
	++index;
	//if the index is at the end just after, it's not valid
	if (not (index < address_par_con.size()))
	{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
		return false;
	}

	if (address_par_con[index] == '[' and address_par_con.back() == ']')
	{
		std::string ipAdressTmp = address_par_con.substr(index + 1);
		std::string ipv6tag(R"(IPv6:)");
		if (ipAdressTmp.substr(0, ipv6tag.length()) == ipv6tag)
		{
			ipAdressTmp.erase(0, ipv6tag.length());
		}
		ipAdressTmp.pop_back();
#ifdef DEBUGJOUVEN
		std::cout << "ipAdressTmp " << ipAdressTmp << '\n';
#endif
		boost::system::error_code ec;
		boost::asio::ip::address::from_string( ipAdressTmp, ec );
		if ( ec )
		{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
			return false;
		}
		else
		{
			return true;
		}
	}

	auto firstPosPassAt(index);
	while (index < address_par_con.size())
	{
		if (address_par_con[index] == '.')
		{
			if (index == firstPosPassAt or address_par_con[index -1] == '.')
			{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
				return false;
			}
		}
		if (address_par_con[index] <= ' ' or address_par_con[index] == 127)
		{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
			return false;
		}
		if (equalOnce_f(address_par_con[index],'\"','(',')',',',':',';','<','>','[','\\',']','@'))
		{
#ifdef DEBUGJOUVEN
		std::cout << DEBUGFULL;
#endif
			return false;
		}
//#ifdef DEBUGJOUVEN
//		std::cout << "index: " << index << " " << address[index] << '\n';
//#endif
		++index;
	}
	return true;

	/////////////////////////////////////////////////////
//	int        count = 0;
//	const char* c, *domain;
//	static char* rfc822_specials = "()<>@,;:\\\"[]";
//
//	/* first we validate the name portion (name@domain) */
//	for (c = address;  *c;  c++)
//	{
//		if (*c == '\"' && (c == address || *(c - 1) == '.' || *(c - 1) ==
//		                   '\"'))
//		{
//			while (*++c)
//			{
//				if (*c == '\"') break;
//				if (*c == '\\' && (*++c == ' ')) continue;
//				if (*c <= ' ' || *c >= 127) return false;
//			}
//			if (!*c++) return 0;
//			if (*c == '@') break;
//			if (*c != '.') return 0;
//			continue;
//		}
//		if (*c == '@') break;
//		if (*c <= ' ' || *c >= 127) return 0;
//		if (strchr(rfc822_specials, *c)) return 0;
//	}
//	if (c == address || *(c - 1) == '.') return 0;
//
//	/* next we validate the domain portion (name@domain) */
//	if (!*(domain = ++c)) return 0;
//	do
//	{
//		if (*c == '.')
//		{
//			if (c == domain || *(c - 1) == '.') return 0;
//			count++;
//		}
//		if (*c <= ' ' || *c >= 127) return 0;
//		if (strchr(rfc822_specials, *c)) return 0;
//	}
//	while (*++c);
//
//	return (count >= 1);
}

}
}

#endif /* COMUSO_EMAILVALIDATION_H_ */
