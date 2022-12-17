#pragma once

#include "Kremonte/krpch.h"
#include "Tryte.h"

namespace Kremonte {

	/* KRASKAmachine
	Central interface used by CLIENT applications to compute KRASKA systems.
	A KRASKAMachine represents a single puppet (complete or incomplete).
	A single KRASKA node is the minimum requirement for an incomplete puppet.
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
			KR_INFO("Testing trytes");
			Tryte t("YCM");
			KR_INFO("PRINT t: {0}", t);
			KR_INFO("PRINT MEMBERS t: {0}{1}{2}", t[0], t[1], t[2]);
			//Tryte tt("cMY");
			//Tryte tet("kMY");
			//Tryte tot("CMYY");
		}

	protected:
		
		
	};
}