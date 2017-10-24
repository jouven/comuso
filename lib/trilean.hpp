#ifndef COMUSO_TRILEAN_H_
#define COMUSO_TRILEAN_H_

#ifdef DEBUGJOUVEN
#include "backwardSTso/backward.hpp"
#endif

#include <cxxtools/json.h>

#include <string>
#include <ostream>
#include <istream>

namespace eines
{
namespace trilean
{

class trilean_c
{
	public:
		enum class trilean_ec
		{
			undefined_value,
			true_value,
			false_value
		};
	protected:
		trilean_ec data_pro = trilean_ec::undefined_value;
	public:
		trilean_c() = default;
		trilean_c(const trilean_ec& data_par_con) : data_pro(data_par_con)
		{}
		trilean_c(const bool& data_par_con)
		{
			if (data_par_con)
			{
				data_pro = trilean_ec::true_value;
			}
			else
			{
				data_pro = trilean_ec::false_value;
			}
		}
		//Always check data_pro != trilean_ec::undefined_value first
		operator bool() const
		{
			return data_pro == trilean_ec::true_value;
		}
		trilean_c operator&&(const trilean_c& obj_par_con)
		{
			switch (obj_par_con.data_pro)
			{
				case trilean_ec::false_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{

									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::undefined_value;
								}
								break;
						}
					}
					break;
				case trilean_ec::true_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{

									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::undefined_value;
								}
								break;
						}
					}
					break;
				case trilean_ec::undefined_value:
					{
						return trilean_ec::undefined_value;
					}
					break;
			}
		}

		trilean_c operator&&(const bool& bool_par_con)
		{
			switch (data_pro)
			{
				case trilean_ec::false_value:
					{
						return trilean_ec::false_value;
//						switch (obj)
//						{
//							case false:
//								{
//									return trilean_ec::false_value;
//								}
//								break;
//							case true:
//								{
//									return trilean_ec::false_value;
//								}
//								break;
//						}
					}
					break;
				case trilean_ec::true_value:
					{
						if (bool_par_con)
						{
							return trilean_ec::true_value;
						}
						else
						{
							return trilean_ec::false_value;
						}
//						switch (obj)
//						{
//							case false:
//								{
//									return trilean_ec::false_value;
//								}
//								break;
//							case true:
//								{
//									return trilean_ec::true_value;
//								}
//								break;
//						}
					}
					break;
				case trilean_ec::undefined_value:
					{
						return trilean_ec::undefined_value;
					}
					break;
			}
		}

		trilean_c operator||(const trilean_c& obj_par_con)
		{
			switch (obj_par_con.data_pro)
			{
				case trilean_ec::false_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{
									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::false_value;
								}
								break;
						}
					}
					break;
				case trilean_ec::true_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::true_value;
								}
								break;
						}
					}
					break;
				case trilean_ec::undefined_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{
									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::undefined_value;
								}
								break;
						}
					}
					break;
			}
		}

		trilean_c operator||(const bool& bool_par_con)
		{
			switch (data_pro)
			{
				case trilean_ec::false_value:
					{
						if (bool_par_con)
						{
							return trilean_ec::true_value;
						}
						else
						{
							return trilean_ec::false_value;
						}
//						switch (obj)
//						{
//							case false:
//								{
//									return trilean_ec::false_value;
//								}
//								break;
//							case true:
//								{
//									return trilean_ec::true_value;
//								}
//								break;
//						}
					}
					break;
				case trilean_ec::true_value:
					{
						if (bool_par_con)
						{
							return trilean_ec::true_value;
						}
						else
						{
							return trilean_ec::true_value;
						}
//						switch (obj)
//						{
//							case false:
//								{
//									return trilean_ec::true_value;
//								}
//								break;
//							case true:
//								{
//									return trilean_ec::true_value;
//								}
//								break;
//						}
					}
					break;
				case trilean_ec::undefined_value:
					{
						if (bool_par_con)
						{
							return trilean_ec::true_value;
						}
						else
						{
							return trilean_ec::false_value;
						}
//						switch (obj)
//						{
//							case false:
//								{
//									return trilean_ec::false_value;
//								}
//								break;
//							case true:
//								{
//									return trilean_ec::true_value;
//								}
//								break;
//						}
					}
					break;
			}
		}

		trilean_c operator==(const trilean_c& obj_par_con)
		{
			switch (obj_par_con.data_pro)
			{
				case trilean_ec::false_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::false_value;
								}
								break;
						}
					}
					break;
				case trilean_ec::true_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{
									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::false_value;
								}
								break;
						}
					}
					break;
				case trilean_ec::undefined_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{
									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::true_value;
								}
								break;
						}
						break;
					}
			}
			return trilean_ec::undefined_value;
		}

		trilean_c operator==(const bool& bool_par_con)
		{
			if (bool_par_con)
			{
				switch (data_pro)
				{
					case trilean_ec::false_value:
						{
							return trilean_ec::false_value;
						}
						break;
					case trilean_ec::true_value:
						{
							return trilean_ec::true_value;
						}
						break;
					case trilean_ec::undefined_value:
						{
							return trilean_ec::undefined_value;
						}
						break;
				}
			}
			else
			{
				switch (data_pro)
				{
					case trilean_ec::false_value:
						{
							return trilean_ec::true_value;
						}
						break;
					case trilean_ec::true_value:
						{
							return trilean_ec::false_value;
						}
						break;
					case trilean_ec::undefined_value:
						{
							return trilean_ec::undefined_value;
						}
						break;
				}
			}



//			switch (obj)
//			{
//				case false:
//					{
//						switch (_data)
//						{
//							case trilean_ec::false_value:
//								{
//									return trilean_ec::true_value;
//								}
//								break;
//							case trilean_ec::true_value:
//								{
//									return trilean_ec::false_value;
//								}
//								break;
//							case trilean_ec::undefined_value:
//								{
//									return trilean_ec::undefined_value;
//								}
//								break;
//						}
//					}
//					break;
//				case true:
//					{
//						switch (_data)
//						{
//							case trilean_ec::false_value:
//								{
//									return trilean_ec::false_value;
//								}
//								break;
//							case trilean_ec::true_value:
//								{
//									return trilean_ec::true_value;
//								}
//								break;
//							case trilean_ec::undefined_value:
//								{
//									return trilean_ec::undefined_value;
//								}
//								break;
//						}
//					}
//					break;
//			}
		}

		bool operator==(trilean_c& obj_par_con) const
		{
			return data_pro == obj_par_con.data_pro;
		}

		bool operator==(const trilean_c& obj_par_con) const
		{
			return data_pro == obj_par_con.data_pro;
		}

		trilean_c operator!=(const trilean_c& obj_par_con)
		{
			switch (obj_par_con.data_pro)
			{
				case trilean_ec::false_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{
									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::true_value;
								}
								break;
						}
					}
					break;
				case trilean_ec::true_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::false_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::true_value;
								}
								break;
						}
					}
					break;
				case trilean_ec::undefined_value:
					{
						switch (data_pro)
						{
							case trilean_ec::false_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::true_value:
								{
									return trilean_ec::true_value;
								}
								break;
							case trilean_ec::undefined_value:
								{
									return trilean_ec::false_value;
								}
								break;
						}
					}
					break;
			}
		}

		trilean_c operator!=(const bool& bool_par_con)
		{
			if(bool_par_con)
			{
				switch (data_pro)
				{
					case trilean_ec::false_value:
						{
							return trilean_ec::true_value;
						}
						break;
					case trilean_ec::true_value:
						{
							return trilean_ec::false_value;
						}
						break;
					case trilean_ec::undefined_value:
						{
							return trilean_ec::undefined_value;
						}
						break;
				}
			}
			else
			{
				switch (data_pro)
				{
					case trilean_ec::false_value:
						{
							return trilean_ec::false_value;
						}
						break;
					case trilean_ec::true_value:
						{
							return trilean_ec::true_value;
						}
						break;
					case trilean_ec::undefined_value:
						{
							return trilean_ec::undefined_value;
						}
						break;
				}
			}

//			switch (obj)
//			{
//				case false:
//					{
//						switch (_data)
//						{
//							case trilean_ec::false_value:
//								{
//									return trilean_ec::false_value;
//								}
//								break;
//							case trilean_ec::true_value:
//								{
//									return trilean_ec::true_value;
//								}
//								break;
//							case trilean_ec::undefined_value:
//								{
//									return trilean_ec::undefined_value;
//								}
//								break;
//						}
//					}
//					break;
//				case true:
//					{
//						switch (_data)
//						{
//							case trilean_ec::false_value:
//								{
//									return trilean_ec::true_value;
//								}
//								break;
//							case trilean_ec::true_value:
//								{
//									return trilean_ec::false_value;
//								}
//								break;
//							case trilean_ec::undefined_value:
//								{
//									return trilean_ec::undefined_value;
//								}
//								break;
//						}
//					}
//					break;
//			}
		}

		bool operator!=(const trilean_c& obj_par_con) const
		{
			return data_pro != obj_par_con.data_pro;
		}

		bool operator==(const int& rhs_par_con)
		{
			return rhs_par_con == 1 and data_pro == trilean_ec::true_value;
		}

		trilean_c operator!()
		{
			switch (data_pro)
			{
				case trilean_ec::false_value:
					{
						return trilean_ec::true_value;
					}
					break;
				case trilean_ec::true_value:
					{
						return trilean_ec::false_value;
					}
					break;
				case trilean_ec::undefined_value:
					{
						return trilean_ec::undefined_value;
					}
					break;
			}
		}

		friend std::ostream& operator<<(std::ostream& ostream_par,
		                                const trilean_c& obj_par_con)
		{
			switch (obj_par_con.data_pro)
			{
				case trilean_ec::false_value:
					{
						ostream_par << "false";
					}
					break;
				case trilean_ec::true_value:
					{
						ostream_par << "true";
					}
					break;
				case trilean_ec::undefined_value:
					{
						ostream_par << "undefined";
					}
					break;
			}
			return ostream_par;
		}

		friend std::istream& operator>>(
			std::istream& istream_par
			, trilean_c& obj_par
		)
		{
			std::string tmp;
			istream_par >> tmp;
			if (tmp == "false")
			{
				obj_par.data_pro = trilean_ec::false_value;
				return istream_par;
			}
			if (tmp == "true")
			{
				obj_par.data_pro = trilean_ec::true_value;
				return istream_par;
			}
			obj_par.data_pro = trilean_ec::undefined_value;
			return istream_par;
		}
		friend void operator<<=(cxxtools::SerializationInfo& si_par,
		                        const trilean_c& obj_par_con)
		{
			switch (obj_par_con.data_pro)
			{
				case trilean_ec::false_value:
					{
						si_par.setValue("false");
					}
					break;
				case trilean_ec::true_value:
					{
						si_par.setValue("true");
					}
					break;
				case trilean_ec::undefined_value:
					{
						si_par.setValue("undefined");
					}
					break;
			}
		}

		friend void operator>>=(const cxxtools::SerializationInfo& si_par_con,
		                        trilean_c& obj_par)
		{
			std::string tmp;
			si_par_con.getValue(tmp);
			if (tmp == "false")
			{
				obj_par.data_pro = trilean_ec::false_value;
				return;
			}
			if (tmp == "true")
			{
				obj_par.data_pro = trilean_ec::true_value;
				return;
			}
			if (tmp == "undefined")
			{
				obj_par.data_pro = trilean_ec::undefined_value;
				return;
			}
		}
};

}
}

#endif /* COMUSO_TRILEAN_H_ */
