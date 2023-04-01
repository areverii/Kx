#pragma once

#include "Kremonte/krpch.h"

#include "../KRASKAboy/Base/KRASKAboy_prelude.h"

//#include "../KRASKAboy/Base/Options.h"
#include "Kremonte/src/KRASKA/Puppet/Weavinglimb/Heartridge.h"

//#include "Tryte.h"

namespace KRASKA {

	/* Puppet
	* Defines a puppet, the central interface object used to store all frontend
	* and backend systems.
	* Used by CLIENT applications to compute KRASKA systems.
	* A single heartdrive node is the minimum requirement for an incomplete puppet.
	*/
	class Puppet {

	public:

		/* Frontend enum used to define a puppet's state in the client world
		(does not denote any backend state) */
		typedef enum { INCOMPLETE = 0, STANDBY = 1, COMPILING = 2, LOADED = 3, RUNNING = 4 } PuppetState;

		Puppet();
		void initialize(std::vector<std::string> arguments, std::string directory);
		void loadHeartridge(std::string filename);
		void run();

		void testCMYK();

		static void draw(const KRASKA::FrameBuffer& buffer) {
		}

		static bool is_closed() {
			return false;
		}

	private:
		PuppetState pstate = INCOMPLETE;

		std::unique_ptr<KRASKA::Heartridge> _heartridge;
		std::unique_ptr<KRASKA::KRASKAboy> _kraskaboy;
	};
}