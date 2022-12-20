#pragma once

#include "Kremonte/krpch.h"
//#include "Kremonte/src/KRASKA/Weavinglimb/Heartdrive.h"
#include "KMachine.h"
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
		

		//KRASKAMachine::KRASKAMachine(const K_MachineState machineState) : machineState(machineState) { }
		//KRASKAMachine(K_MachineState machineState) {

		//}
		//KRASKAmachine();


		void testCMYK() {
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

	protected:
		KMachine kMachine;
		PuppetState pstate = INCOMPLETE;
	};
}