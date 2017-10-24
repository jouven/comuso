#ifndef COMUSO_LOGGINGMACROS_H_
#define COMUSO_LOGGINGMACROS_H_

#include "timeso/timepointToStrReversible.hpp"

#include <cstring>

#define DEBUGSOURCE (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__) << " (" << __func__ << ") "

#define DEBUGDATETIME eines::timeUtils::time_point_to_iso()(std::chrono::system_clock::now()) << " "

#define DEBUGDATETIMEANDSOURCE DEBUGDATETIME << DEBUGSOURCE

#define DEBUGSTEADYTIME (std::chrono::steady_clock::now() - steady_start_time).time_since_epoch().count() << " "

#define DEBUGSOURCEBEGIN std::cout << DEBUGDATETIMEANDSOURCE << "BEGIN\n";

#define DEBUGSOURCEEND std::cout << DEBUGDATETIMEANDSOURCE << "END\n";

#define DEBUGFULL DEBUGDATETIMEANDSOURCE << "line: " << __LINE__ << " "

#define DEBUGFULLEND std::cout << DEBUGFULL << "END\n";

#endif /* COMUSO_LOGGINGMACROS_H_ */
