#include "UI.h"
#include "../fonts/fonts.h"
#include "../IconsFontAwesome6.h"

namespace Windowing
{
	void UI::Init(Window& window, bool dockingEnable, bool viewportsEnable)
	{
		float scaleDpi;
		glfwGetWindowContentScale(window.windowHandle, &scaleDpi, NULL);

		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		ImFontConfig config;
		config.MergeMode = true;
		config.GlyphMinAdvanceX = 18 * scaleDpi; // Use if you want to make the icon monospaced
		io.Fonts->AddFontFromMemoryTTF(Roboto_Regular_ttf, Roboto_Regular_ttf_len, 18 * scaleDpi);
		static const ImWchar icon_ranges[] = { ICON_MIN_FA, ICON_MAX_FA, 0 };
		io.Fonts->AddFontFromMemoryCompressedTTF(fa_solid_900_compressed_data, fa_solid_900_compressed_size, 18 * scaleDpi, &config, icon_ranges);
		io.Fonts->Build();

		ImGui::GetStyle().ScaleAllSizes(scaleDpi);

		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		if (dockingEnable)
			io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking

		if (viewportsEnable)
			io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows

		docking = dockingEnable;
		viewports = viewportsEnable;

		ImGui::StyleColorsDark();
		ImGui_ImplGlfw_InitForOpenGL(window.windowHandle, true);
		ImGui_ImplOpenGL3_Init();
	}

	void UI::Shutdown()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void UI::NewFrame()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void UI::Render()
	{
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (viewports)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void UI::CreateDockSpace()
	{
		dockspaceInitialized = true;
		ImGuiViewport* viewport = ImGui::GetMainViewport();
		ImGui::SetNextWindowPos(viewport->Pos);
		ImGui::SetNextWindowSize(viewport->Size);
		ImGui::SetNextWindowViewport(viewport->ID);

		ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;
		window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
		window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
		ImGui::Begin("DockSpaceWindow", nullptr, window_flags);
	}

	void UI::EndDockSpace()
	{
		if (dockspaceInitialized)
			dockspaceInitialized = false;
			ImGui::End();
	}
}