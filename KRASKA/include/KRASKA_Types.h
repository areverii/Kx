#pragma once

//#include "KRASKA.h"
//#include "third_party/libter27/libter9.h"

#ifndef _KRASKA_TYPES_H
#define _KRASKA_TYPES_H

#include "Kremonte/kraspch.h"

namespace KRASKA {

	enum class channel {
		Cx,
		Mx,
		Yx,
		Kx,
	};

	typedef struct swatchStr {
		channel channel;
		bter9_t value;
	} swatch;

	//typedef bter9_t swatch;

// TODO: define more macros?
//#define Cx0 { channel::Cx, BTER9_C_0 }
//#define Cx0 swatch Cx0 = { .channel = channel::Cx, .value = BTER9_C_0 }
//#define Mx0 swatch Mx0 = { .channel = channel::Mx, .value = BTER9_C_0 }
//#define Yx0 swatch Yx0 = { .channel = channel::Yx, .value = BTER9_C_0 }

//#define SWATCH(channel, value) { channel::#channel, BTER9_C_#value}

	class patch {
	public:
		patch() {
			//_glyphID = BTER9_C_0;
		}
		
		void setInputs(std::string inputs);
			//_inputs.clear();
			// TODO: set inputs

	private:
		//bter9_t _glyphID;
		//std::vector<cell> _inputs;
	};
}

#endif