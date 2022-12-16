#pragma once

#include "Kremonte/krpch.h"
#include "CMYK.h"

namespace Kremonte {

	/* KRASKAmachine
	Central interface used by CLIENT applications to compute KRASKA systems.
	A KRASKAMachine represents 
	*/
	class KRASKAmachine {

	public:
		typedef enum { INCOMPLETE = 0, PUPPET_STANDBY = 1, PUPPET_RUNNING = 2 } K_MachineState;
		K_MachineState machineState;


		//KRASKAMachine::KRASKAMachine(const K_MachineState machineState) : machineState(machineState) { }
		//KRASKAMachine(K_MachineState machineState) {

		//}
		KRASKAmachine() {

		}


		void testCMYK() {
			KR_INFO("{0}{1}{2}", Trit::C, Trit::M, Trit::Y);

		}

	protected:
		
		
	};
}