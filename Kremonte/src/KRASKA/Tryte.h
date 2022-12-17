#pragma once

#include "Kremonte/krpch.h"
#include "Trit.h"
//#include "Kremonte/src/Core/Log.h"

//#include <stdlib.h>
#include <iostream>

namespace Kremonte {
	
	class Tryte {

	public:

		/*Tryte() {
			_data[0] = Trit::M;
			_data[1] = Trit::M;
			_data[2] = Trit::M;
		}*/

		Tryte(std::string trits) {
			KR_INFO("input length: {0}", trits.length());
			KR_ASSERT_MESSAGE(trits.length() <= 3, "Attempted to construct tryte from more than 3 trits!");
			for (int i = 0; i < 3; i++) {
				char c = trits[i];
				c &= ~0x20;
				//KR_INFO("char is: {0}", c);

				switch (c) {
				case 'C':
					_data[i] = Trit::C;
					break;
				case 'M':
					_data[i] = Trit::M;
					break;
				case 'Y':
					_data[i] = Trit::Y;
					break;
				default:
					KR_ERROR("Attempted to construct a trit from a non CMY character!");
				}
			}
		}

		char operator[](int i) const {
			return _data[i].chr();
		}

	protected:
		Trit _data[3] = { Trit::M, Trit::M, Trit::M };
	};

	std::ostream& operator<<(std::ostream& ostr, const Tryte& t) {
		ostr << t[0] << t[1] << t[2];
		return ostr;
	}

}