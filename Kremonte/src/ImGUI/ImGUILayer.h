#pragma once

#include "imgui.h"

#include "Core/Layer.h"

namespace Kremonte {

	class ImGUILayer : public Layer
	{
		static ImGUILayer* CreateLayer();

	};

}