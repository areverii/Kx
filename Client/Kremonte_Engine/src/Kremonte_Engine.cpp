#ifdef KREMONTEVER

#include "Kremonte.h"

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

class Kremonte_Engine : public Kremonte::Application {

public:
	/* MAIN SANDBOX APP*/
	Kremonte_Engine(const Kremonte::ApplicationSpec& spec)
		: Application(spec) {

		//PushLayer(new ExampleLayer());
		KR_INFO("test");
	}

	virtual void OnInit() override {

	}

};

Kremonte::Application* Kremonte::CreateApplication(int argc, char** argv) {

	Kremonte::ApplicationSpec spec;
	spec.Name = "Kremonte Editor";
	spec.windowWidth = 1600;
	spec.windowHeight = 900;
	spec.vsync;

	return new Kremonte_Engine(spec);

}

#endif

#include "KxGUI.h"

class ExampleLayer : public KxGUI::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello");
		ImGui::Button("Button");
		ImGui::End();

		ImGui::ShowDemoWindow();
	}
};

KxGUI::Application* KxGUI::CreateApplication(int argc, char** argv)
{
	KxGUI::ApplicationSpecification spec;
	spec.Name = "KxGUI Example";

	KxGUI::Application* app = new KxGUI::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
		{
			if (ImGui::BeginMenu("File"))
			{
				if (ImGui::MenuItem("Exit"))
				{
					app->Close();
				}
				ImGui::EndMenu();
			}
		});
	return app;
}