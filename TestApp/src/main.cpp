#include "AppForgue.h"
#include <format>


void mainLoop(Windowing::Window* window)
{
	const float titlebarHeight = 58.0f;
	auto* fgDrawList = ImGui::GetForegroundDrawList();

	const bool isMaximized = window->IsMaximized();
	float titlebarVerticalOffset = isMaximized ? -6.0f : 0.0f;
	const ImVec2 windowPadding = ImGui::GetCurrentWindow()->WindowPadding;

	ImGui::SetCursorPos(ImVec2(windowPadding.x, windowPadding.y + titlebarVerticalOffset));
	const ImVec2 titlebarMin = ImGui::GetCursorScreenPos();
	const ImVec2 titlebarMax = { ImGui::GetCursorScreenPos().x + ImGui::GetWindowWidth() - windowPadding.y * 2.0f,
								 ImGui::GetCursorScreenPos().y + titlebarHeight };

	fgDrawList->AddRect(titlebarMin, titlebarMax, ImColor::ImColor(255,0,0));

	const float w = ImGui::GetContentRegionAvail().x;
	const float buttonsAreaWidth = 94;
	ImGui::InvisibleButton("##titleBarDragZone", ImVec2(w - buttonsAreaWidth, titlebarHeight));

	window->SetTitleBarHitted(ImGui::IsItemHovered());

	ImGui::Begin("Ventana Aplicacion", NULL);
	ImGui::Text(std::format("Abrir {}", ICON_FA_FOLDER).c_str());
	ImGui::End();
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

int APIENTRY WinMain(_In_ HINSTANCE hInstance,_In_opt_ HINSTANCE hPrevInstance,_In_ LPSTR lpCmdLine,_In_ int nShowCmd)
{
	createApplication(__argc, __argv);
}
#else
int main(int argc, char** argv)
{
	createApplication(__argc, __argv);
}
#endif