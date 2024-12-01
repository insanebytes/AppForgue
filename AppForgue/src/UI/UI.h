#pragma once
#include "../Window.h"
#ifndef APPFORGUE_INCLUDE_NONE
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#endif


namespace Windowing
{
	class UI
	{
	public:
		static void Init(Window &window , bool dockingEnable, bool viewportsEnable);
		static void Shutdown();
		static void NewFrame();
		static void Render();

		static void CreateDockSpace();
		static void EndDockSpace();

	private:
		inline static bool docking = false;
		inline static bool viewports = false;
		inline static bool dockspaceInitialized = false;
	};
}
