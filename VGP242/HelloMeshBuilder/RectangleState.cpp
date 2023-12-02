#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "RectangleState.h"

using namespace CASTLEEngine::Graphics;

void RectangleState::CreateMesh()
{
    mMesh = MeshBuilder::CreateRectanglePC(2.0f, 1.5f, 2.0f);
}