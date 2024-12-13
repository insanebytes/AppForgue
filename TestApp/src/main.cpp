#include "AppForgue.h"
#include <format>

void drawTitleBar(Windowing::Window* window)
{
	const float titlebarHeight = 58.0f;
	const bool isMaximized = window->IsMaximized();
	const float windowBorderSize = ImGui::GetCurrentWindow()->WindowBorderSize;
	float titlebarVerticalOffset = isMaximized ? -6.0f : 0.0f;

	ImGui::SetCursorPos(ImVec2(windowBorderSize, titlebarVerticalOffset));
	const ImVec2 titlebarMin = ImGui::GetCursorScreenPos();
	const ImVec2 titlebarMax = { ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth() - (windowBorderSize * 2.0f),ImGui::GetCursorScreenPos().y + titlebarHeight };

	ImDrawList* fgDrawList = ImGui::GetForegroundDrawList();
	fgDrawList->AddRectFilled(titlebarMin, titlebarMax, ImColor::ImColor(24, 24, 24));

	ImGui::BeginHorizontal("Titlebar", { ImGui::GetWindowWidth() - windowBorderSize * 2.0f, ImGui::GetFrameHeightWithSpacing() });

	const float w = ImGui::GetContentRegionAvail().x;
	const float buttonsAreaWidth = 94;
	ImGui::InvisibleButton("##titleBarDragZone", ImVec2(w - buttonsAreaWidth, 58.0f));
	window->SetTitleBarHitted(ImGui::IsItemHovered());
	
	ImGui::Spring();
	ImGui::SetCursorPosY(ImGui::GetCursorPosY() + 8.0f);
	ImGui::Button(ICON_FA_WINDOW_MINIMIZE, ImVec2(30, 30));
	//ImGui::Button(ICON_FA_WINDOW_MAXIMIZE, ImVec2(30, 30));
	ImGui::EndHorizontal();
}

void mainLoop(Windowing::Window* window)
{
	drawTitleBar(window);

	//ImGui::Begin("Ventana Aplicacion", NULL);
	//ImGui::Text(std::format("Abrir {}", ICON_FA_FOLDER).c_str());
	//ImGui::End();
}

void createApplication(int argc, char** argv)
{
	struct Windowing::WindowHints hints;
	hints.appTitle = "TestApp";
	hints.maximized = false;
	hints.titlebar = false;
	hints.docking = true;
	hints.viewport = true;

	Windowing::Window mainWindow(hints);
	App::Run(mainWindow, mainLoop);
}

#if defined(PLATFORM_WINDOWS)
#include <Windows.h>

int APIENTRY WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nShowCmd)
{
	createApplication(__argc, __argv);
}
#else
int main(int argc, char** argv)
{
	createApplication(__argc, __argv);
}
#endif