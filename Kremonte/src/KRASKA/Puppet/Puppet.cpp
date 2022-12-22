#include "Puppet.h"

namespace Kremonte {

	Puppet::Puppet()
		: _heartridge(nullptr)//, _kraskaboy(KRASKA::KRASKAboy(std::vector<u8>, KRASKA::Options))
	{
		const std::vector<u8> empty_ROM;
		KRASKA::Options empty_options;
		_kraskaboy = std::make_unique<KRASKA::KRASKAboy>(empty_ROM, empty_options);
		//_kraskaboy = make_unique<KRASKA::KRASKAboy>()
	}

	void Puppet::loadHeartridge(int argc, char* kb_args[]) {
		if (pstate != STANDBY) {
			// error
			return;
		}
		//_heartridge.reset();
		_heartridge = std::make_unique<KRASKA::Heartridge>(KRASKA::Heartridge(KRASKA::constructOptions(argc, kb_args)));
		//_heartridge.setOptions(KRASKA::constructOptions(argc, kb_args));
		auto rom_data = KRASKA::read_bytes(_heartridge->getOptions()._filename);
		_heartridge->setROM(rom_data);
		pstate = LOADED; 
	}

	//TODO: Load new rom function

	void Puppet::run() {
		//_kraskaboy.reset();
		if (_heartridge == nullptr) {
			//error
			return;
		}
		//_kraskaboy.reset();
		_kraskaboy = std::make_unique<KRASKA::KRASKAboy>(_heartridge->loadROM(), _heartridge->getOptions()._options);
		//_kraskaboy = std::make_unique<KRASKA::KRASKAboy>(KRASKA::KRASKAboy(_heartridge->loadROM(), _heartridge->getOptions()._options));
		_kraskaboy->run(&is_closed, &draw);
	}

	void Puppet::testCMYK() {
		//KR_INFO("{0}{1}{2}", Trit::C, Trit::M, Trit::Y);
		//KR_INFO("Testing trytes");
		//Tryte t("YCM");
		//Hept h(14);
		//KR_INFO("Made hept of 14: {0}", h);
		//KR_INFO("PRINT t: {0}", t);
		//KR_INFO("PRINT MEMBERS t: {0}{1}{2}", t[0], t[1], t[2]);


		//Tryte tt("cMY");
		//Tryte tet("kMY");
		//Tryte tot("CMYY");

		//KR_INFO("testing tryte 27");
		//t27 tryte_one("MMMMMMMMMMMMMMMMMMMMMMMMMMC");
	}

}