#pragma once

#include "Core/Application.h"

#ifdef _KR_PLATFORM_WINDOWS_

extern KxGUI::Application* KxGUI::CreateApplication(int argc, char** argv);
bool g_ApplicationRunning = true;

namespace KxGUI {

	int Main(int argc, char** argv)
	{
		while (g_ApplicationRunning)
		{
			KxGUI::Application* app = KxGUI::CreateApplication(argc, argv);
			app->Run();
			delete app;
		}

		return 0;
	}

}

#ifdef _KR_DIST_

#include <Windows.h>

int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow)
{
	return KxGUI::Main(__argc, __argv);
}

#else

int main(int argc, char** argv)
{
	return KxGUI::Main(argc, argv);
}

#endif // _KR_DIST_

#endif // _KR_PLATFORM_WINDOWS_
