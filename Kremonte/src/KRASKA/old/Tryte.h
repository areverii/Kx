#pragma once

#include "Kremonte/krpch.h"
#include "Trit.h"
#include "Hept.h"

#include <iostream>

namespace Kremonte {

	class t27 {
	public:

		Trit operator!() const {
			return ter27_neg(_val);
		}

		Trit operator&&(const Trit& t) const {
			return ter27_min(_val, t._val);
		}

		Trit operator||(const Trit& t) const {
			return ter27_max(ter27_neg(_val), t._val);
		}

		Trit operator>>(const Trit& t) const {
			return ter27_max(ter27_neg(_val), t._val);
		}

		Trit operator==(const Trit& t) const {
			return ter27_equ(_val, t._val);
		}

		//A operator+ (A x, A const& y) { x += y; return x; }
		//A& A::operator+=(A const &y) { /* modify *this using y */ ; return *this; }

	protected:
		typedef enum { _C = -1, _M = 0, _Y = 1 } CMY;
		bter27_t _val;

		Tryte(std::string trits) {
			KR_INFO("input length: {0}", trits.length());
			KR_ASSERT_MESSAGE(trits.length() <= 27, "Attempted to construct tryte from more than 27 trits!");

			bter27_t word = BTER27_C_0;

			for (int i = 0; i < trits.length(); i++) {
				char c = trits[i];
				c &= ~0x20;

				uter27_t lsb = 27 - i;
				uter27_t hi = lsb + 1; /* lsb + width */

				word = ((word >> hi) << hi) | (word << (27 - lsb)) >> (27 - lsb);

				//x000000000

				/* shl:
					word << (uter27) bits
					shr:
					word >> (uter27) bits

					hi = lsb + width /* one beyond most significant trit
					shl(shr(word, hi), hi)
					| shr(shl(word, 27 - lsb), 27 - lsb)
					| (value << lsb);
				*/

				switch (c) {
				case 'C':
					//_data[i] = ; //need to set ith trit to value C or -1
					uter27_t cval = (BTER27_C_N1 << (27 - hi)) >> 26;
					word = word | (cval << lsb);
					KR_INFO("Got C, word is now {0}", word);
					break;
				case 'M':
					//_data[i] = Trit::M;
					uter27_t mval = (BTER27_C_0 << (27 - hi)) >> 26;
					word = word | (mval << lsb);
					KR_INFO("Got M, word is now {0}", word);
					break;
				case 'Y':
					//_data[i] = Trit::Y;
					uter27_t yval = (BTER27_C_1 << (27 - hi)) >> 26;
					word = word | (yval << lsb);
					KR_INFO("Got Y, word is now {0}", word);
					break;
				default:
					KR_ERROR("Attempted to construct a trit from a non CMY character!");
				}
			}
			_val = word;
		}
	};

	class t9 {

	};


#ifdef disabled
	class Tryte {

	public:

		Tryte(std::string trits) {
			KR_INFO("input length: {0}", trits.length());
			KR_ASSERT_MESSAGE(trits.length() <= 3, "Attempted to construct tryte from more than 3 trits!");
			for (int i = 0; i < 3; i++) {
				char c = trits[i];
				c &= ~0x20;

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

		/* function to convert to hept */

	protected:
		Trit _data[3] = { Trit::M, Trit::M, Trit::M };
	};

	std::ostream& operator<<(std::ostream& ostr, const Tryte& t) {
		ostr << t[0] << t[1] << t[2];
		return ostr;
	}
#endif

}