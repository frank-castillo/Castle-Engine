#include "GameState.h"

enum class States : size_t
{
    GameState = 0,
    Triangle,
    Cube,
    TriForce,
    Heart
};

int WINAPI WinMain(HINSTANCE instance, HINSTANCE, LPSTR, int)
{
    CASTLEEngine::App& mainApp = CASTLEEngine::MainApp();
    mainApp.AddState<Cube>((size_t)States::Cube);
    //mainApp.AddState<GameState>((size_t)States::GameState);
    //mainApp.AddState<Triangle>((size_t)States::Triangle);
    //mainApp.AddState<TriForce>((size_t)States::TriForce);
    //mainApp.AddState<Heart>((size_t)States::Heart);

    mainApp.Run();

    return 0;
}