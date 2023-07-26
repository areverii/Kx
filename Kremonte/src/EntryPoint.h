#pragma once

#ifdef _KR_PLATFORM_WINDOWS_


extern Kremonte::Application* Kremonte::CreateApplication(int arc, char** argv);
bool m_ApplicationRunning = true;

/* Main -- Program entrypoint */
int main(int argc, char** argv) {

	while (m_ApplicationRunning) {
		Kremonte::Log::Init();
		//KR_CORE_WARN("Initialized log");
		//KR_INFO("Hello");

		Kremonte::Application* app = Kremonte::CreateApplication(argc, argv);
		//KR_CORE_ASSERT(app, "Client application is null!");
		app->Run();

		delete app;
		return EXIT_SUCCESS;
	}

}

#endif