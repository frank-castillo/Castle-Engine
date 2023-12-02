#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "QuadState.h"

using namespace CASTLEEngine::Graphics;

void QuadState::CreateMesh()
{
    mMesh = MeshBuilder::CreateQuadPC(1.0f, 1.5f);
}