#include "Precompiled.h"
#include "DebugUtil.h"
#include "WindowMessageHandler.h"

using namespace CASTLEEngine::Core;

void WindowMessageHandler::Hook(HWND window, Callback cb)
{
    mWIndow = window;
    mPreviousCallback = (Callback)GetWindowLongPtrA(window, GWLP_WNDPROC); // Retrieves information about the espcfified window
    SetWindowLongPtrA(window, GWLP_WNDPROC, (LONG_PTR)cb);
}

void WindowMessageHandler::Unhook()
{
    SetWindowLongPtrA(mWIndow, GWLP_WNDPROC, (LONG_PTR)mPreviousCallback);
    mWIndow = nullptr;
}

LRESULT WindowMessageHandler::ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
    ASSERT(mPreviousCallback, "WindowsMessageHandler -- No callback is hooked.");
    return CallWindowProcA((WNDPROC)mPreviousCallback, window, message, wParam, lParam);
}