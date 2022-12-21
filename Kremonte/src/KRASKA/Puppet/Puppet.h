#pragma once

#include "Kremonte/krpch.h"
//#include "Kremonte/src/KRASKA/Weavinglimb/Heartdrive.h"
//#include "Tryte.h"

namespace Kremonte {

	/* Puppet
	* Defines a puppet, the central interface object used to store all frontend
	* and backend systems.
	* Used by CLIENT applications to compute KRASKA systems.
	* A single heartdrive node is the minimum requirement for an incomplete puppet.
	*/
	class Puppet {

	public:
		/* Frontend enum used to define a puppet's state in the world (does not denote
		* any backend state)
		*/
		typedef enum { INCOMPLETE = 0, PUPPET_STANDBY = 1, PUPPET_RUNNING = 2 } PuppetState;

		Puppet();	

		//KRASKAMachine::KRASKAMachine(const K_MachineState machineState) : machineState(machineState) { }
		//KRASKAMachine(K_MachineState machineState) {

		//}
		//KRASKAmachine();


		void testCMYK();

	protected:
		PuppetState pstate = INCOMPLETE;
	};
}