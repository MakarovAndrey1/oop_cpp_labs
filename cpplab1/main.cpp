#include <iostream>
#include <string>
#include "include/time_converter.h"


int main() {
    int hour, minute;
    std::string period;

    std::cin >> hour >> minute >> period;

    std::string result = convertTo24Hour(hour, minute, period);
    std::cout << result << std::endl;

    return 0;
}