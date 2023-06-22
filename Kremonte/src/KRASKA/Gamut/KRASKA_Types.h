#pragma once

#include "KRASKA.h"
#include <variant>

namespace KRASKA {

	enum class channel {
		Cx,
		Mx,
		Yx,
	};

	struct swatch {
		channel channel;
		bter9_t value;
	};

// TODO: define more macros?
//#define Cx0 swatch Cx0 = { .channel = channel::Cx, .value = BTER9_C_0 }
//#define Mx0 swatch Mx0 = { .channel = channel::Mx, .value = BTER9_C_0 }
//#define Yx0 swatch Yx0 = { .channel = channel::Yx, .value = BTER9_C_0 }

	class patch {
	public:
		patch() {
			_glyphID = BTER9_C_0;
		}

		void setInputs(std::string inputs) {
			//_inputs.clear();
			// TODO: set inputs
		}

	private:
		bter9_t _glyphID;
		//std::vector<cell> _inputs;

	};
}