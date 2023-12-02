#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "GameState.h"
#include "SphereState.h"

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
    mainApp.AddState<GameState>((size_t)States::GameState);
    //mainApp.AddState<RectangleState>((size_t)States::Rectangle);
    //mainApp.AddState<QuadState>((size_t)States::Quad);
    //mainApp.AddState<PlaneState>((size_t)States::Plane);
    //mainApp.AddState<CylinderState>((size_t)States::Cylinder);
    //mainApp.AddState<SphereState>((size_t)States::Sphere);

    mainApp.Run();

    return 0;
}