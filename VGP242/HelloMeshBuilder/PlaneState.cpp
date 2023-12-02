#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "PlaneState.h"

using namespace CASTLEEngine::Graphics;

void PlaneState::CreateMesh()
{
    mMesh = MeshBuilder::CreatePlanePC(4, 4, 4.0f);
}