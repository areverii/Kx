#pragma once
#include "Kremonte/krpch.h"

namespace Kremonte {

	class KMachine;

	class CPU {
	public:

		CPU(KMachine& kMachine_in);

		tick();

	private:
		bool halted;


	};

}