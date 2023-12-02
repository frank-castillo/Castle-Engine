#include <CASTLE_Engine/Inc/CASTLE_Engine.h>
#include "SphereState.h"

using namespace CASTLEEngine::Graphics;

void SphereState::CreateMesh()
{
    mMesh = MeshBuilder::CreateSpherePC(120, 120, 1.5f);
}