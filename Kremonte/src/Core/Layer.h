#pragma once

#include "Core/Base.h"
#include "Event/Event.h"

namespace Kremonte {

	class Layer {

	public:
		Layer(const std::string& name = "Layer");
		virtual ~Layer();

		virtual void OnAttach() { }
		virtual void OnDetach() { }
		virtual void OnUpdate() { }
		virtual void OnEvent(Event& event) { }

		inline const std::string& GetName() { return m_DebugName; }

	protected:
		std::string m_DebugName;
	};

}