#pragma once

#include "HeartridgeOptions.h"
#include "../../KRASKAboy/Base/Definitions.h"

#include <vector>

namespace KRASKA {

	class Heartridge {
	public:

		Heartridge(HeartridgeOptions options);

		std::vector<u8> loadROM();
		void setROM(std::vector<u8> ROM);
		HeartridgeOptions getOptions();
		//void setOptions(HeartridgeOptions options);

	protected:
		HeartridgeOptions _options;
		std::vector<u8> _ROM;
	};

}