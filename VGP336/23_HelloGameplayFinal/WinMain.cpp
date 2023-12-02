#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Rectangle,
    Quad,
    Plane,
    Cylinder,
    Sphere
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    CASTLEEngine::App& mainApp = CASTLEEngine::MainApp();

    CASTLEEngine::AppConfig config;
    config.appName = L"HelloGameplayFinal";
    config.winWidth = 1280;
    config.winHeight = 720;

    mainApp.AddState<GameState>((size_t)States::GameState);

    mainApp.Run(config);

    return 0;
}