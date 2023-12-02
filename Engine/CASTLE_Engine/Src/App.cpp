#include "Precompiled.h"

#include "App.h"
#include "AppState.h"
#include "AudioSystem.h"
#include "SoundEffectManager.h"

//#define _IS_EDITOR

using namespace CASTLEEngine;
using namespace CASTLEEngine::Core;
using namespace CASTLEEngine::Graphics;
using namespace CASTLEEngine::Graphics::DebugUI;
using namespace CASTLEEngine::Input;
using namespace CASTLEEngine::Physics;

void App::ChangeState(size_t stateId)
{
    auto iter = mAppStates.find(stateId);

    if (iter != mAppStates.end())
    {
        mNextState = iter->second.get();
    }
}

void App::Run()
{
    ASSERT(false, "NO LONGER USED");
    AppConfig config;
    Run(config);
}

void App::Run(const AppConfig& config)
{
    CASTLEEngine::Core::Window myWindow;
    myWindow.Initialize(
        GetModuleHandle(nullptr),
        config.appName,
        config.winWidth,
        config.winHeight);

    auto handle = myWindow.GetWindowHandle();
    InputSystem::StaticInitialize(handle);
    GraphicsSystem::StaticInitialize(handle, false);
    DebugUI::StaticInitialize(handle, false, true);
    SimpleDraw::StaticInitialize(config.debugDrawLimit);
    TextureManager::StaticInitialize("../../Assets/");
    ModelManager::StaticInitialize();
    AudioSystem::StaticInitialize();
    SoundEffectManager::StaticInitialize("../../Assets/Audio/");

    PhysicsWorld::Settings settings =
    {
        config.gravity,
        config.simulationSteps,
        config.fixedTimeStep
    };
    PhysicsWorld::StaticInitialize(settings);

    ASSERT(mCurrentState, "App --  no app state found!");
    mCurrentState->Initialize();
    size_t currentState = 0;
    mRunning = true;

    while (mRunning)
    {
        myWindow.ProcessMessage();

        auto inputSystem = InputSystem::Get();
        inputSystem->Update();

        if (!myWindow.IsActive() || inputSystem->IsKeyPressed(Input::KeyCode::ESCAPE))
        {
            Quit();
            continue;
        }

        if (inputSystem->IsKeyPressed(KeyCode::ENTER))
        {
            currentState = (currentState + 1) % (size_t)mAppStates.size();
            ChangeState(currentState);
        }

        if (mNextState != nullptr)
        {
            mCurrentState->Terminate();
            mCurrentState = std::exchange(mNextState, nullptr);
            mCurrentState->Initialize();

            // Swap
            // mCurrentState <> mNextState
            // mNextState {}{}{} mCurrenState

            // Exchange
            // mCurrentState << mNextState << nullptr
            // mNextState {}{}{} mCurrentState
        }

        AudioSystem::Get()->Update();

        auto deltaTime = TimeUtil::GetDeltaTime();
        if (deltaTime < 0.5f)
        {
#ifndef _IS_EDITOR
            PhysicsWorld::Get()->Update(deltaTime);
#endif
            mCurrentState->Update(deltaTime);
        }

        auto graphicsSystem = GraphicsSystem::Get();
        graphicsSystem->BeginRender();
        mCurrentState->Render();

#ifdef _IS_EDITOR
        DebugUI::BeginRender();
            mCurrentState->EditorUI();
        DebugUI::EndRender();
#else
        DebugUI::BeginRender();
        mCurrentState->DebugUI();
        DebugUI::EndRender();
#endif // _IS_DEBUG

        graphicsSystem->EndRender();
    }

    mCurrentState->Terminate();

    PhysicsWorld::StaticTerminate();
    SoundEffectManager::StaticTerminate();
    AudioSystem::StaticTerminate();
    ModelManager::StaticTerminate();
    TextureManager::StaticTerminate();
    SimpleDraw::StaticTerminate();
    DebugUI::StaticTerminate();
    GraphicsSystem::StaticTerminate();
    InputSystem::StaticTerminate();
    myWindow.Terminate();
}

void App::Quit()
{
    mRunning = false;
}