#pragma once

#include "Kremonte/krpch.h"
//#include "Kremonte/src/Core/Log.h"

//#include <stdlib.h>
#include <iostream>

namespace Kremonte {

	class Trit {

	public:
		/*
		░ = C = 176 = \xb2 = [===] = -
		▒ = M = 177 = \xb1 = [///] = 0
		▓ = Y = 178 = \xb0 = [|||] = +
		*/
		static const Trit C, M, Y;

		Trit operator!() const {
			return static_cast<CMYKvalue>(-value);
		}

		Trit operator&&(const Trit& t) const {
			return (value < t.value) ? static_cast<CMYKvalue>(value) : t.value;
		}

		Trit operator||(const Trit& t) const {
			return (-value > t.value) ? static_cast<CMYKvalue>(-value) : t.value;
		}

		Trit operator>>(const Trit& t) const {
			return (-value > t.value) ? static_cast<CMYKvalue>(-value) : t.value;
		}

		Trit operator==(const Trit& t) const {
			return static_cast<CMYKvalue>((value * t.value));
		}

		char chr() const {
			return "\xb0\xb1\xb2"[value + 1];
		}

	protected:
		typedef enum { _C = -1, _M = 0, _Y = 1 } CMYKvalue;
		CMYKvalue value;
		Trit(const CMYKvalue value) : value(value) {  } /* constructor */
	};

	const Trit Trit::C = Trit(Trit::_C);
	const Trit Trit::M = Trit(Trit::_M);
	const Trit Trit::Y = Trit(Trit::_Y);

	std::ostream& operator<<(std::ostream& ostr, const Trit& t) {
		ostr << t.chr();
		return ostr;
	}

}