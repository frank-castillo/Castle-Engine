#include "Precompiled.h"
#include "PhysicsDebugDrawer.h"

#include <Graphics/Inc/SimpleDraw.h>

using namespace CASTLEEngine;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Physics;

void PhysicsDebugDrawer::drawLine(const btVector3& from, const btVector3& to, const btVector3& color)
{
    SimpleDraw::AddLine(ConvertToVector3(from), ConvertToVector3(to), ConvertToColor(color));
}

void PhysicsDebugDrawer::drawContactPoint(const btVector3& pointOnB, const btVector3& normalOnB, btScalar distance, int lifeTime, const btVector3& color)
{
    //NTA
}

void PhysicsDebugDrawer::reportErrorWarning(const char* warningString)
{
    LOG("[PhysicsWarning] %s", warningString);
}

void PhysicsDebugDrawer::draw3dText(const btVector3& location, const char* textString)
{
    //NTA
}

void PhysicsDebugDrawer::setDebugMode(int debugMode)
{
    mDebugMode = debugMode;
}

int  PhysicsDebugDrawer::getDebugMode() const
{
    return mDebugMode;
}