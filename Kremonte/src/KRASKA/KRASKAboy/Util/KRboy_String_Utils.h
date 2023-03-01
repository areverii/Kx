#pragma once

#include <string>
#include <vector>

#include <cstdio>
#include <sstream>

#include <cstdarg>

namespace KRASKA {

	auto str_format(const char* fmt, va_list args)->std::string;
	auto str_format(const char* fmt, ...)->std::string;

	auto split(const std::string& str, char delim = ' ')->std::vector<std::string>;
}