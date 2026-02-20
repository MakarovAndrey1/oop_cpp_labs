#pragma once // говорит компилятору что данный файл должен быть включен только один раз

#ifndef TIME_CONVERTER_H
#define TIME_CONVERTER_H

#include <string>

std::string convertTo24Hour(int hour, int minute, const std::string& period);

#endif // TIME_CONVERTER_H