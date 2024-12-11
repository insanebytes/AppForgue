#include "App.h"

void App::Run(Windowing::Window &mainWindow, std::function<void(Windowing::Window*)> mainLoop)
{
    Windowing::UI::Init(mainWindow,mainWindow.creationHints->docking,mainWindow.creationHints->viewport);

    //hack because in initial window creation, viewport displaces up
    mainWindow.ResizeWindow(mainWindow.creationHints->width+1, mainWindow.creationHints->height+1);

    while (!glfwWindowShouldClose(mainWindow.windowHandle))
    {
        glfwPollEvents();
        
        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

        Windowing::UI::NewFrame();
        Windowing::UI::CreateDockSpace();

        mainLoop(&mainWindow);

        Windowing::UI::EndDockSpace();

        Windowing::UI::Render();

        glfwSwapBuffers(mainWindow.windowHandle);
    }

    Windowing::UI::Shutdown();
}