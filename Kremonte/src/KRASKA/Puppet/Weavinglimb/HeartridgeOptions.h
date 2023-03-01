#pragma once

#include "../../KRASKAboy/Base/Options.h"
#include "../../KRASKAboy/Base/Definitions.h"
#include <vector>
#include <string>

namespace KRASKA {
	
	struct HeartridgeOptions
	{
		Options& _options;
		std::string& _filename;
		HeartridgeOptions(Options& options, std::string& filename) : _options(options), _filename(filename) { }
	};

	HeartridgeOptions constructOptions(int argc, char* argv[]);

}