#include "krpch.h"
#include "Core/Input.h"
#include "Platform/Windows/WindowsWindow.h"

#include "Core/Application.h"

#include <GLFW/glfw3.h>

namespace Kremonte {

	bool Input::IsKeyPressed(KeyCode keycode)
	{
		/*bool enableImGui = Application::Get().GetSpecification().EnableImGui;
		if (!enableImGui)
		{
			auto& window = static_cast<WindowsWindow&>(Application::Get().GetWindow());
			auto state = glfwGetKey(static_cast<GLFWwindow*>(window.GetNativeWindow()), static_cast<int32_t>(keycode));
			return state == GLFW_PRESS || state == GLFW_REPEAT;
		}*/

		auto& window = static_cast<WindowsWindow&>(Application::Get().GetWindow());
		GLFWwindow* win = static_cast<GLFWwindow*>(window.GetNativeWindow());
		//ImGuiContext* context = ImGui::GetCurrentContext();
		bool pressed = false;
		/*for (ImGuiViewport* viewport : context->Viewports)
		{
			if (!viewport->PlatformUserData)
				continue;

			GLFWwindow* windowHandle = *(GLFWwindow**)viewport->PlatformUserData; // First member is GLFWwindow
			if (!windowHandle)
				continue;
			auto state = glfwGetKey(windowHandle, static_cast<int32_t>(keycode));
			if (state == GLFW_PRESS || state == GLFW_REPEAT)
			{
				pressed = true;
				break;
			}
		}*/
		return pressed;
	}

	bool Input::IsMouseButtonPressed(MouseButton button)
	{
		/*bool enableImGui = Application::Get().GetSpecification().EnableImGui;
		if (!enableImGui)
		{
			auto& window = static_cast<WindowsWindow&>(Application::Get().GetWindow());

			auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(window.GetNativeWindow()), static_cast<int32_t>(button));
			return state == GLFW_PRESS;
		}*/
		
		bool pressed = false;
		/*ImGuiContext* context = ImGui::GetCurrentContext();
		
		for (ImGuiViewport* viewport : context->Viewports)
		{
			if (!viewport->PlatformUserData)
				continue;

			GLFWwindow* windowHandle = *(GLFWwindow**)viewport->PlatformUserData; // First member is GLFWwindow
			if (!windowHandle)
				continue;
			auto state = glfwGetMouseButton(static_cast<GLFWwindow*>(windowHandle), static_cast<int32_t>(button));
			if (state == GLFW_PRESS || state == GLFW_REPEAT)
			{
				pressed = true;
				break;
			}
		}*/
		return pressed;
	}

	float Input::GetMouseX()
	{
		auto [x, y] = GetMousePosition();
		return (float)x;
	}

	float Input::GetMouseY()
	{
		auto [x, y] = GetMousePosition();
		return (float)y;
	}

	std::pair<float, float> Input::GetMousePosition()
	{
		auto& window = static_cast<WindowsWindow&>(Application::Get().GetWindow());

		double x, y;
		glfwGetCursorPos(static_cast<GLFWwindow*>(window.GetNativeWindow()), &x, &y);
		return { (float)x, (float)y };
	}

	// TODO: A better way to do this is to handle it internally, and simply move the cursor the opposite side
	//		of the screen when it reaches the edge
	void Input::SetCursorMode(CursorMode mode)
	{
		auto& window = static_cast<WindowsWindow&>(Application::Get().GetWindow());
		glfwSetInputMode(static_cast<GLFWwindow*>(window.GetNativeWindow()), GLFW_CURSOR, GLFW_CURSOR_NORMAL + (int)mode);
	}

	CursorMode Input::GetCursorMode()
	{
		auto& window = static_cast<WindowsWindow&>(Application::Get().GetWindow());
		return (CursorMode)(glfwGetInputMode(static_cast<GLFWwindow*>(window.GetNativeWindow()), GLFW_CURSOR) - GLFW_CURSOR_NORMAL);
	}

}