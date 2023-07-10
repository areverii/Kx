#pragma once

#include "Kremonte/src/Core/Layer.h"
#include "imgui.h"

namespace Kremonte {

	class ImGUILayer : public Layer
	{
		static ImGUILayer* CreateLayer();

	};

}