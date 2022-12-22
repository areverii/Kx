#pragma once

#include <vector>
#include <string>

#include "../Base/Definitions.h"

namespace KRASKA {

	auto read_bytes(const std::string& filename)->std::vector<u8>;

}