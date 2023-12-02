#include "Precompiled.h"
#include "CASTLE_Engine.h"

CASTLEEngine::App& CASTLEEngine::MainApp()
{
    static App sApp;
    return sApp;
}