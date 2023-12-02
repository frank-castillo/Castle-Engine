#include "Core/Inc/Core.h"

int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
    LOG("New Log");

    ASSERT(false, "JUST TESTING ASSERT");

    return 0;
}