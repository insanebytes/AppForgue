#pragma once
#include <stdlib.h>
#include <stdio.h>
#ifndef APPFORGUE_INCLUDE_NONE
#include "Glad/glad.h"
#include "GLFW/glfw3.h"
#endif

namespace Windowing
{
	/// <summary>
	/// Window creation hints struct
	/// </summary>
	struct WindowHints
	{
		/// <summary>
		/// Window Application Name
		/// </summary>
		const char* appTitle;

		/// <summary>
		/// Window should be maximized
		/// </summary>
		bool maximized = false;

		/// <summary>
		/// Window should have titlebar (if false there will be custom titlebar)
		/// </summary>
		bool titlebar =false;

		/// <summary>
		/// UI of window supports docking
		/// </summary>
		bool docking =false;

		/// <summary>
		/// UI of window supports getting outside of window
		/// </summary>
		bool viewport = false;

		/// <summary>
		/// Default width of window
		/// </summary>
		int width = 1024;

		/// <summary>
		/// Default height of window
		/// </summary>
		int height = 768;
	};

	/// <summary>
	/// Graphical Window
	/// </summary>
	class Window
	{
	public:
		/// <summary>
		/// Create a new graphical window
		/// </summary>
		/// <param name="hints">Window creation parameters</param>
		Window(WindowHints& hints);
		~Window();

		bool IsMinimized();
		bool IsMaximized();
		void SetTitleBarHitted(bool hitted);
		void ResizeWindow(int width, int height);

		WindowHints* creationHints;

#ifndef APPFORGUE_INCLUDE_NONE
		/// <summary>
		/// Native handle of GLFW window
		/// </summary>
		GLFWwindow* windowHandle;
#endif
#ifdef APPFORGUE_INCLUDE_NONE

		/// <summary>
		/// Opaque type for library use
		/// </summary>
		void* windowHandle;
#endif

	private:
		bool titleBarHit = false;
	};
}

