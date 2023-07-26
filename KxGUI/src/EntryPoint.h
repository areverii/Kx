#pragma once

#ifdef KR_PLATFORM_WINDOWS

extern KrGUI::Application* KrGUI::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace KrGUI {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			KrGUI::Application* app = KrGUI::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#ifdef KR_DIST

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return KrGUI::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return KrGUI::Main(argc, argv);
}

#endif // KR_DIST

#endif // KR_PLATFORM_WINDOWS
