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

	HeartridgeOptions constructOptions(int argc, char* argv[]) {
		if (argc < 2) {
			fatal_error("Please provide a ROM file to run");
		}

		//HeartridgeOptions heartridgeOptions;
		//heartridgeOptions._filename = argv[1];
		std::string filename = argv[1];
		Options options;

		std::vector<std::string> flags(argv + 2, argv + argc);

		for (std::string& flag : flags) {
			if (flag == "--debug") { options.debugger = true; }
			else if (flag == "--trace") { options.trace = true; }
			else if (flag == "--silent") { options.disable_logs = true; }
			else if (flag == "--headless") { options.headless = true; }
			else if (flag == "--whole-framebuffer") { options.show_full_framebuffer = true; }
			else if (flag == "--exit-on-infinite-jr") { options.exit_on_infinite_jr = true; }
			else if (flag == "--print-serial") { options.print_serial = true; }
			else { fatal_error("Unknown flag: %s", flag.c_str()); }
		}

		return HeartridgeOptions(options, filename);
	}

}