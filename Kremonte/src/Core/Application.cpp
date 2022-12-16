#include "Kremonte/krpch.h"
#include "Kremonte/src/Core/Application.h"
#include "Kremonte/src/Core/Log.h"

#include <Windows.h>

namespace Kremonte {

	// can use just &x instead and switch to BIND_EVENT_FN(Application::OnEvent) for greater abstraction
	#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	Application* Application::s_Instance = nullptr;

	Application::Application(const ApplicationSpec& spec)
		: m_Spec(spec) {

		s_Instance = this;

		m_Window = std::unique_ptr<Window>(Window::Create());
		m_Window->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}

	Application::~Application() {

		for (Layer* layer : m_LayerStack) {
			layer->OnDetach();
			delete layer;
		}

	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
	}

	void Application::PushOverlay(Layer* layer) {
		m_LayerStack.PushOverlay(layer);
	}

	void Application::OnEvent(Event& e) {
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(OnWindowClose));

		for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();) {
			(*--it)->OnEvent(e);
			// If an overlay layer handles an event, it will not be handled by any other layers.
			if (e.Handled)
				break;
		}
	}

	void Application::Run() {

		while (m_Running) {

			for (Layer* layer : m_LayerStack)
				layer->OnUpdate();

			//auto [x, y] = Input::GetMousePosition();

			m_Window->OnUpdate();
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		m_Running = false;
		return true;
	}

}