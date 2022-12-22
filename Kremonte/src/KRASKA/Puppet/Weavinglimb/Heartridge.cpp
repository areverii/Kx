#include "Heartridge.h"

namespace KRASKA {

	Heartridge::Heartridge(HeartridgeOptions options)
		//: _options()
		: _options(options)
	{

	}

	std::vector<u8> Heartridge::loadROM() {
		return _ROM;
	}

	void Heartridge::setROM(std::vector<u8> ROM) {
		_ROM = ROM;
	}

	//void Heartridge::setOptions(HeartridgeOptions options) {
	//	_options = options;
	//}

	HeartridgeOptions Heartridge::getOptions() {
		return _options;
	}

}