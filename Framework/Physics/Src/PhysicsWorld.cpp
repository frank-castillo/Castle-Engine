#include "Precompiled.h"
#include "PhysicsWorld.h"
#include "PhysicsDebugDrawer.h"
#include "RigidBody.h"
#include "../Engine/CASTLE_Engine/Inc/GameObject.h"

using namespace CASTLEEngine;
using namespace CASTLEEngine::Physics;

namespace
{
    std::unique_ptr<PhysicsWorld> sPhysicsWorld;
}

void PhysicsWorld::StaticInitialize(const Settings& settings)
{
    ASSERT(sPhysicsWorld == nullptr, "PhysicsWorld: is already initialize");
    sPhysicsWorld = std::make_unique<PhysicsWorld>();
    sPhysicsWorld->Initialize(settings);
}

void PhysicsWorld::StaticTerminate()
{
    if (sPhysicsWorld != nullptr)
    {
        sPhysicsWorld->Terminate();
        sPhysicsWorld.reset();
    }
}

PhysicsWorld* PhysicsWorld::Get()
{
    ASSERT(sPhysicsWorld != nullptr, "PhysicsWorld: is not initialized");
    return sPhysicsWorld.get();
}

PhysicsWorld::~PhysicsWorld()
{
    ASSERT(mDynamicWorld == nullptr, "PhysicsWorld: terminate must be called before deletion");
}

void PhysicsWorld::Initialize(const Settings& settings)
{
    mSettings = settings;
    mCollisionConfiguration = new btDefaultCollisionConfiguration();
    mDispatcher = new btCollisionDispatcher(mCollisionConfiguration);
    mInterface = new btDbvtBroadphase();
    mSolver = new btSequentialImpulseConstraintSolver();
    mDynamicWorld = new btDiscreteDynamicsWorld(mDispatcher, mInterface, mSolver, mCollisionConfiguration);
    mDynamicWorld->setGravity(ConvertTobtVector3(settings.gravity));

    mDebugdrawer = new PhysicsDebugDrawer();
    mDynamicWorld->setDebugDrawer(mDebugdrawer);
    mRenderDebugUI = true;
}

void PhysicsWorld::Terminate()
{
    SafeDelete(mDebugdrawer);
    SafeDelete(mDynamicWorld);
    SafeDelete(mSolver);
    SafeDelete(mInterface);
    SafeDelete(mDispatcher);
    SafeDelete(mCollisionConfiguration);
}

void PhysicsWorld::Update(float deltaTime)
{
    mDynamicWorld->stepSimulation(deltaTime, mSettings.simulationSteps, mSettings.fixedTimeStep);

    int numManifolds = mDispatcher->getNumManifolds();
    for (int i = 0; i < numManifolds; ++i)
    {
        // Contact point cache that gets created as soon as objects are colliding. It stores up to 4 points
        // The number of points depends on the collision check algorithm but it always prioritizes deeper penetrations
        btPersistentManifold* contactManifold = mDispatcher->getManifoldByIndexInternal(i);

        int numContacts = contactManifold->getNumContacts();

        for (int j = 0; j < numContacts; ++j)
        {
            btManifoldPoint& pt = contactManifold->getContactPoint(j);

            // On this check, if we go inside, there was contact
            if (pt.getDistance() < 0.0f)
            {
                auto userPointerA = contactManifold->getBody0()->getUserPointer();
                auto userPointerB = contactManifold->getBody1()->getUserPointer();

                if (userPointerA != nullptr && userPointerB != nullptr)
                {
                    
                    GameObject* gameObjectA = static_cast<GameObject*>(userPointerA);
                    GameObject* gameObjectB = static_cast<GameObject*>(userPointerB);
                    gameObjectA->OnCollision(gameObjectB);
                    gameObjectB->OnCollision(gameObjectA);

                    //std::function<void(void*, void*)>* cb = static_cast<std::function<void(void*, void*)>*>(userPointerA);
                    //(*cb)(userPointerA, userPointerB);
                }

                const btVector3& ptA = pt.getPositionWorldOnA();
                const btVector3& ptB = pt.getPositionWorldOnB();
                const btVector3& normalB = pt.m_normalWorldOnB;

                // Need our version of objects
                // Need a delegate function to call (or "OnCollision")

            }
        }
    }

    for (auto& rb : mRigidBodies)
    {
        // Run sim, update rigid body object, and apply the btTransform to move the graphic
        rb->UpdateTransform();
    }
}

void PhysicsWorld::DebugUI()
{
    ImGui::Checkbox("RenderPhysics##", &mRenderDebugUI);

    if (mRenderDebugUI)
    {
        int debugMode = mDebugdrawer->getDebugMode();
        bool isEnabled = (debugMode & btIDebugDraw::DBG_DrawWireframe) > 0;

        if (ImGui::Checkbox("[DBG]DrawWireFrame##", &isEnabled))
        {
            debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawWireframe : debugMode & ~btIDebugDraw::DBG_DrawWireframe;
        }

        isEnabled = (debugMode & btIDebugDraw::DBG_DrawAabb) > 0;

        if (ImGui::Checkbox("[DBG]DrawAabb##", &isEnabled))
        {
            debugMode = (isEnabled) ? debugMode | btIDebugDraw::DBG_DrawAabb : debugMode & ~btIDebugDraw::DBG_DrawAabb;
        }

        mDebugdrawer->setDebugMode(debugMode);
        mDynamicWorld->debugDrawWorld();
    }
}

void PhysicsWorld::SetGravity(const CASTLEEngine::CEMath::Vector3& gravity)
{
    mDynamicWorld->setGravity(ConvertTobtVector3(gravity));
}

void PhysicsWorld::Register(RigidBody* rigidBody)
{
    if (rigidBody != nullptr)
    {
        mRigidBodies.push_back(rigidBody);

        if (rigidBody->GetRigidBody() != nullptr)
        {
            mDynamicWorld->addRigidBody(rigidBody->GetRigidBody());
        }
    }
}

void PhysicsWorld::Unregister(RigidBody* rigidBody)
{
    if (rigidBody != nullptr)
    {
        auto iter = std::find(mRigidBodies.begin(), mRigidBodies.end(), rigidBody);
        if (iter != mRigidBodies.end())
        {
            if (rigidBody->GetRigidBody() != nullptr)
            {
                mDynamicWorld->removeRigidBody(rigidBody->GetRigidBody());
            }
            mRigidBodies.erase(iter);
        }
    }
}