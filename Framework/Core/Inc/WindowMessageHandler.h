#pragma once

namespace CASTLEEngine::Core
{
    class WindowMessageHandler
    {
    public:
        using Callback = LRESULT(CALLBACK*)(HWND, UINT, WPARAM, LPARAM);

        void Hook(HWND window, Callback cb);
        void Unhook();

        LRESULT ForwardMessage(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

    private:
        HWND mWIndow = nullptr;
        Callback mPreviousCallback = nullptr;
    };
}