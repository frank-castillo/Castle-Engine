#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    CASTLEEngine::App& mainApp = CASTLEEngine::MainApp();
    mainApp.AddState<GameState>((size_t)States::GameState);

    mainApp.Run();


    // Old Way of creating a window
    /*CASTLEEngine::Core::Window newWindow;
    newWindow.Initialize(instance, L"Hello Window", 1920, 1080);

    while (true)
    {
        newWindow.ProcessMessage();
        if (!newWindow.IsActive())
            break;
        if (GetAsyncKeyState(VK_ESCAPE))
            break;
    }

    newWindow.Terminate();*/

    return 0;
}