#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "CylinderState.h"

using namespace CASTLEEngine::Graphics;

void CylinderState::CreateMesh()
{
    mMesh = MeshBuilder::CreateCylinderPC(32, 32);
}