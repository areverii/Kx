#include "Kremonte/Kremonte.h"

/*class ExampleLayer : public Kremonte::Layer {

public:
	ExampleLayer()
		: Layer("Example") {

	}

	void OnUpdate() override {
		KR_INFO("ExampleLayer::Update");
	}

	void OnEvent(Kremonte::Event& event) override {
		KR_TRACE("{0}", event);
	}

};
*/

class SandboxApp : public Kremonte::Application {

public:
	SandboxApp(const Kremonte::ApplicationSpec& spec)
		: Application(spec) {

		//PushLayer(new ExampleLayer());
	}

	//virtual void OnInit() override {
		
	//}

};

Kremonte::Application* Kremonte::CreateApplication(int argc, char** argv) {

	Kremonte::ApplicationSpec spec;
	spec.Name = "Kremonte Engine Sandbox";
	spec.windowWidth = 1600;
	spec.windowHeight = 900;
	spec.vsync;
	
	return new SandboxApp(spec);

}