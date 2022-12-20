#include "Register.h"

namespace Kremonte {

	void Register::set(const bter9_t val) {
		_val = val;
	}

	void Register::reset() {
		_val = BTER9_C_0;
	}

	auto Register::value() const -> bter9_t {
		return _val;
	};

	void Register::set_trit(bter9_t trit, bool set) {
		
	}

	auto Register::check_trit(bter9_t trit) const -> bool {
		return false;
	}

	void Register::increment() {
		_val += BTER9_C_1;
	}

	void Register::decrement() {
		_val -= BTER9_C_1;
	}

	auto Register::operator==(bter9_t other) const -> bool {
		return _val == other;
	}


}