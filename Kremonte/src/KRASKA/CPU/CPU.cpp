#include "CPU.h"

#include "Kremonte/src/KRASKA/KMachine.h"

namespace Kremonte {

	CPU::CPU(KMachine& kMachine_in) {

	}

	int CPU::tick() {

		if (halted) {
			return 1;
		}
		return 0;
	}
}

