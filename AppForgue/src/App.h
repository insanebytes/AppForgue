#pragma once
#include "Window.h"
#include <functional>
#include "UI/UI.h"

class App
{
public:
	static void Run(Windowing::Window &mainWindow, std::function<void(Windowing::Window*)> mainLoop);
};

