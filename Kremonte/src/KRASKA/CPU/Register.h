#pragma once

#include "Kremonte/src/KRASKA/libter27/libter9.h"

namespace Kremonte {

	class Register {
	public:
		Register() = default;
		virtual ~Register() = default;

		virtual void set(bter9_t value);
		void reset();
		auto value() const -> bter9_t;

		auto check_trit(bter9_t trit) const -> bool;
		void set_trit(bter9_t trit, bool set);

		void increment();
		void decrement();

		auto operator==(bter9_t other) const -> bool;


	private:
		bter9_t _val = BTER9_C_0;
	};

	class FlagRegister : public Register {
	public:
		FlagRegister() = default;

	};

	class Word {

	};

	class WordRegister : public Word {

	};

	class RegisterPair : public Word {

	};

}