#include "Puppet.h"


namespace KRASKA {


	/*Puppet::Puppet()
		: _heartridge(nullptr)//, _kraskaboy(KRASKA::KRASKAboy(std::vector<u8>, KRASKA::Options))
	{
		const std::vector<u8> empty_ROM;
		KRASKA::Options empty_options;
		_kraskaboy = std::make_unique<KRASKA::KRASKAboy>(empty_ROM, empty_options);
		//_kraskaboy = make_unique<KRASKA::KRASKAboy>()
	}*/

	Puppet::Puppet() {
		KR_INFO("CONSTRUCTING PUPPET");

		std::vector<std::string> arguments = { "01-special.gb" };

		std::vector<char*> argv;
		for (const auto& arg : arguments) {
			argv.push_back((char*)arg.data());
		}
		argv.push_back(nullptr);

		//_heartridge = std::make_uniqu e<KRASKA::Heartridge>(KRASKA::constructOptions(argv.size() - 1, argv.data()));
		//_kraskaboy = std::make_unique<KRASKA::KRASKAboy>(_heartridge->loadROM(), _heartridge->getOptions()._options);
		_heartridge = std::make_unique<KRASKA::Heartridge>(KRASKA::constructOptions(argv.size() - 1, argv.data()));
		loadHeartridge("C:/Kremonte_Engine/bazel-bin/Clients/Sandbox/src/01-special.gb");
		//temph.setROM("01-special.gb");

		//KR_ASSERT_MESSAGE(temph.loadROM(), "loadROM is null");
		//KR_ASSERT_MESSAGE(temph.getOptions()._options, "options are null");

		KR_INFO("about to construct kraskaboy");
		//if (temph.loadROM() == NULL || temph.getOptions()._options == NULL) {
		//	KR_INFO("AAAA bad null nto good");
		//}
		//KR_INFO("rom is {0} and options is {1}", temph.loadROM(), temph.getOptions()._options);
		KRASKA::KRASKAboy tempg(_heartridge->loadROM(), _heartridge->getOptions()._options);

	}

	//void Puppet::loadHeartridge(int argc, char* kb_args[]) {
	void Puppet::loadHeartridge(std::string filename) {
		/*if (pstate != STANDBY) {
			// error
			return;
		}*/
		//_heartridge.reset();
		// 
		//_heartridge = std::make_unique<KRASKA::Heartridge>(KRASKA::Heartridge(KRASKA::constructOptions(argc, kb_args)));
		// 
		//_heartridge.setOptions(KRASKA::constructOptions(argc, kb_args));
		//auto rom_data = KRASKA::read_bytes(_heartridge->getOptions()._filename);
		auto rom_data = KRASKA::read_bytes(filename);
		_heartridge->setROM(rom_data);
		pstate = LOADED;
	}

	//TODO: Load new rom function

	void Puppet::run() {
		/*
		//_kraskaboy.reset();
		if (_heartridge == nullptr) {
			//error
			return;
		}
		//_kraskaboy.reset();
		_kraskaboy = std::make_unique<KRASKA::KRASKAboy>(_heartridge->loadROM(), _heartridge->getOptions()._options);
		//_kraskaboy = std::make_unique<KRASKA::KRASKAboy>(KRASKA::KRASKAboy(_heartridge->loadROM(), _heartridge->getOptions()._options));
		_kraskaboy->run(&is_closed, &draw);*/
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