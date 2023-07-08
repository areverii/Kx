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
	/* MAIN SANDBOX APP*/
	SandboxApp(const Kremonte::ApplicationSpec& spec)
		: Application(spec) {

		//PushLayer(new ExampleLayer());
		KR_INFO("Hello KREMONTE");
		//Kremonte::KRASKAmachine krmachine;
		//krmachine.testCMYK();
		//KRASKA::Puppet puppet;
		//KR_INFO("running");
		//puppet.run();
		//puppet.testCMYK();
		
		//KRASKA::Geometry geo;
		//geo.Icosahedron(true);

		KRASKA::Matrix matrix;

		/* Expand unit tests */
		KR_ASSERT(matrix.Expand(new KRASKA::SwatchNode(KRASKA::swatch{ KRASKA::channel::Cx, BTER9_C_0 })));
		KR_ASSERT(matrix.Expand(new KRASKA::SwatchNode(KRASKA::swatch{ KRASKA::channel::Yx, BTER9_C_2 })));
		KR_ASSERT(matrix.Expand(new KRASKA::SwatchNode(KRASKA::swatch{ KRASKA::channel::Mx, BTER9_C_13 })));
		KR_ASSERT(!matrix.Expand(new KRASKA::SwatchNode(KRASKA::swatch{ KRASKA::channel::Kx, BTER9_C_13 })));
		KR_INFO("KRASKA: Matrix Unit Tests - EXPAND passed.");

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