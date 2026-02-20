#include "../include/time_converter.h"
#include <iomanip>
#include <sstream>

std::string convertTo24Hour(int hour, int minute, const std::string& period) {
    if (period == "am") {
        if (hour == 12) {
            hour = 0;
        }
    } else if (period == "pm") {
        if (hour != 12) {
            hour += 12;
        }
    }

    std::ostringstream oss;
    oss << std::setfill('0') << std::setw(2) << hour << std::setw(2) << minute;
    return oss.str();
}