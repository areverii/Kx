#pragma once

#include "Core/Base.h"
#include "Core/Window.h"
#include "Core/LayerStack.h"
#include "Event/Event.h"
#include "Event/ApplicationEvent.h"


namespace Kremonte {

	struct ApplicationSpec {
		std::string Name = "Kremonte Application";
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
		void Quit();

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


