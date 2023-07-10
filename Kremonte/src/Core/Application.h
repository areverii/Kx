#pragma once

#include "Kremonte/src/Core/Base.h"
#include "Kremonte/src/Core/Window.h"
#include "Kremonte/src/Core/LayerStack.h"
#include "Kremonte/src/Events/Event.h"
#include "Kremonte/src/Events/ApplicationEvent.h"


namespace Kremonte {

	struct ApplicationSpec {
		std::string Name = "Kremonte Engine";
		uint32_t windowWidth = 1600, windowHeight = 900;
		bool fullscreen = false;
		bool vsync = true;
		std::string workingDirectory;
		bool enableimgui = true;
	};

	class Application {

	public:
		Application(const ApplicationSpec& spec);
		virtual ~Application();

		void Run();

		virtual void OnInit() {}

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		static inline Application& Get() { return *s_Instance; }
		inline Window& GetWindow() { return *m_Window; }
		
	private:
		bool OnWindowClose(WindowCloseEvent& e);

	private:
		std::unique_ptr<Window> m_Window;
		ApplicationSpec m_Spec;
		bool m_Running = true, m_Minimized = false;
		LayerStack m_LayerStack;

		static Application* s_Instance;
	};

	// To be defined in CLIENT
	Application* CreateApplication(int argc, char** argv);

}


