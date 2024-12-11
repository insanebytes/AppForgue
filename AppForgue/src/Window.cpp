#include "Window.h"

namespace Windowing
{
	Window::Window(WindowHints& hints)
	{
		creationHints = &hints;

		if (!glfwInit())
		{
			const char* description;
			glfwGetError(&description);
			printf("Error %s\n", description);
			exit(EXIT_FAILURE);
		}

		if (!hints.titlebar)
		{
			glfwWindowHint(GLFW_TITLEBAR, false);
		}

		glfwWindowHint(GLFW_MAXIMIZED, hints.maximized);
		windowHandle = glfwCreateWindow(creationHints->width-1, creationHints->height-1, hints.appTitle, NULL, NULL);

		if (!windowHandle)
		{
			const char* description;
			glfwGetError(&description);
			printf("Error: %s\n", description);
			glfwTerminate();
			exit(EXIT_FAILURE);
		}

		if (!hints.titlebar) {
			glfwSetWindowUserPointer(windowHandle, this);
			glfwSetTitlebarHitTestCallback(windowHandle, [](GLFWwindow* window, int x, int y, int* hit)
			{
					Window* windowInstance = (Window*)glfwGetWindowUserPointer(window);
					*hit = windowInstance->titleBarHit;
			});
		}

		glfwSetWindowSizeCallback(windowHandle, [](GLFWwindow* window, int width, int height) {
			glViewport(0, 0, width, height);
		});

		glfwSetInputMode(windowHandle, GLFW_STICKY_KEYS, GLFW_TRUE);
		glfwMakeContextCurrent(windowHandle);
		gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

		if (hints.maximized)
		{
			int width;
			int height;
			glfwGetWindowSize(windowHandle, &width, &height);

			glViewport(0, 0, width, height);
		}
		else
		{
			glViewport(0, 0, creationHints->width-1, creationHints->height-1);
		}
	}

	Window::~Window()
	{
		glfwDestroyWindow(windowHandle);
		glfwTerminate();
	}

	bool Window::IsMinimized()
	{
		return glfwGetWindowAttrib(windowHandle, GLFW_ICONIFIED) != 0;
	}

	bool Window::IsMaximized()
	{
		return glfwGetWindowAttrib(windowHandle, GLFW_MAXIMIZED) != 0;
	}

	void Window::SetTitleBarHitted(bool hitted)
	{
		titleBarHit = hitted;
	}

	void Window::ResizeWindow(int width, int height)
	{
		glfwSetWindowSize(windowHandle, width, height);
	}
}