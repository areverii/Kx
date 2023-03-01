#pragma once

#include <vector>
#include <string>

#include "../Base/Definitions.h"

#include "KRboy_Log.h"
#include <fstream>

namespace KRASKA {

	auto read_bytes(const std::string& filename)->std::vector<u8>;

}