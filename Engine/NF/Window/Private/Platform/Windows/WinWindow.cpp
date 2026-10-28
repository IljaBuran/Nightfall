#include <Private/pch.hpp>

#include <Window/Window.hpp>

namespace NF
{
    namespace
    {
        HWND nativeWindowHandle{};

        u32 width{};
        u32 height{};

        bool isMinimized{ false };
        bool isMaximized{ false };
        bool isFocused{ false };
        bool isFullscreen{ false };
        bool shouldClose{ false };

        const WCHAR* WINDOW_CLASS_NAME = L"NightfallGame";
        constexpr DWORD winStyle{ WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_THICKFRAME | WS_MINIMIZEBOX | WS_MAXIMIZEBOX };

        LRESULT CALLBACK WindowProc(HWND hWnd, u32 uMsg, WPARAM wParam, LPARAM lParam) noexcept;
    }

    void Window::Init(Configuration& config)
    {
        WNDCLASSEXW wc
        {
            .cbSize = sizeof(WNDCLASSEX),
            .style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
            .lpfnWndProc = WindowProc,
            .cbClsExtra{},
            .cbWndExtra{},
            .hInstance = GetModuleHandleW(nullptr),
            .hIcon{},
            .hCursor = LoadCursorW(nullptr, IDC_ARROW),
            .hbrBackground{},
            .lpszMenuName{},
            .lpszClassName = WINDOW_CLASS_NAME,
            .hIconSm{}
        };

        NF_VERIFY(RegisterClassEx(&wc));

        UINT dpi{ GetDpiForSystem() };

        if (config.width == 0 || config.height == 0)
        {
            // size of client window = 3/4 * the monitor's size
            i32 monitorWidth = GetSystemMetricsForDpi(SM_CXSCREEN, dpi);
            i32 monitorHeight = GetSystemMetricsForDpi(SM_CYSCREEN, dpi);

            width  = static_cast<i32>(0.75f * monitorWidth);
            height = static_cast<i32>(0.75f * monitorHeight);

            config.width = width;
            config.height = height;
        }
        else
        {
            width = config.width;
            height = config.height;
        }

        RECT clientRect = { 0, 0, static_cast<i32>(width), static_cast<i32>(height) };

        AdjustWindowRectExForDpi(&clientRect, winStyle, false, 0, dpi);

        WString windowName = ::NF::OS::Windows::Utf8ToWide(config.name);

        i32 x{ CW_USEDEFAULT };
        i32 y{ CW_USEDEFAULT };

        // needs to happen after AdjustWindowRectEx
        const i32 windowW{ clientRect.right - clientRect.left };
        const i32 windowH{ clientRect.bottom - clientRect.top };

        // todo: parent window for editor!!!
        if (!config.windowHandle)
        {
            HMONITOR monitor{ MonitorFromPoint({ 0, 0 }, MONITOR_DEFAULTTOPRIMARY) };
            MONITORINFO info{ .cbSize = sizeof(MONITORINFO) };
            GetMonitorInfoW(monitor, &info);

            const RECT& work{ info.rcWork };

            x = work.left + (work.right - work.left - windowW) / 2;
            y = work.top + (work.bottom - work.top - windowH) / 2;
        }

        // create window
        nativeWindowHandle = CreateWindowEx(
            0,
            WINDOW_CLASS_NAME,
            windowName.data(),
            winStyle,
            x,
            y,
            clientRect.right  - clientRect.left,
            clientRect.bottom - clientRect.top,
            nullptr,
            nullptr,
            GetModuleHandle(nullptr),
            nullptr
        );

        NF_ASSERT(nativeWindowHandle);

        config.windowHandle = nativeWindowHandle;
        //NF_LOG_INFO("Win32 window initialized successfully");

        ShowWindow(nativeWindowHandle, SW_NORMAL);
    }

    void Window::BeginFrame() 
    {
        MSG msg{};

        while (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void Window::PreUpdate() {}
    void Window::FixedUpdate() {}
    void Window::Update() {}
    void Window::PostUpdate() {}
    void Window::Render() {}
    void Window::EndFrame() {}

    void Window::Shutdown()
    {
        UnregisterClassW(WINDOW_CLASS_NAME, GetModuleHandleW(nullptr));
        
        if (nativeWindowHandle)
        {
            DestroyWindow(nativeWindowHandle);
        }
    }

    Pair<u32, u32> Window::GetWindowSize() noexcept
    {
        return { width, height };
    }

    bool Window::IsMinimized() noexcept
    {
        return isMinimized;
    }

    bool Window::IsFocused() noexcept
    {
        return isFocused;
    }

    bool Window::IsFullscreen() noexcept
    {
        return isFullscreen;
    }

    bool Window::ShouldClose() noexcept
    {
        return shouldClose;
    }

    void* Window::GetNativeWindowHandle() noexcept
    {
        return nativeWindowHandle;
    }

    namespace
    {
        LRESULT CALLBACK WindowProc(
            [[maybe_unused]] HWND hWnd,
            u32 uMsg,
            WPARAM wParam,
            LPARAM lParam
        ) noexcept
        {
            static i32 newWidth{}, newHeight{};

            //i32 xMousePos{}, yMousePos{};

            // if mouse -> update new x-y coordinates
            //if (WM_MOUSEFIRST <= uMsg && uMsg <= WM_MOUSELAST)
            //{
            //    xMousePos = static_cast<i16>(LOWORD(lParam));
            //    yMousePos = static_cast<i16>(HIWORD(lParam));
            //    m_input.NotifyNewMousePostition(xMousePos, yMousePos);
            //}

            auto lResize = [&]()
            {
                if (static_cast<i32>(width) == newWidth && static_cast<i32>(height) == newHeight)
                    return;

                //NF_LOG_INFO("[WINDOW] Resized from {}x{} to {}x{}", width, height, newWidth, newHeight);

                width = newWidth;
                height = newHeight;
            };

            switch (uMsg)
            {
                //case WM_KEYDOWN:
                //{
                //    ILL_ASSERT(wParam < 0xFF);

                //    m_input.NotifyKeyDown(static_cast<keyCode>(wParam));
                //    return 0;
                //}

                //case WM_KEYUP:
                //{
                //    ILL_ASSERT(wParam < 0xFF);

                //    m_input.NotifyKeyUp(static_cast<keyCode>(wParam));
                //    return 0;
                //}

                //case WM_LBUTTONDOWN:
                //{
                //    if (!imguiIo || !imguiIo->WantCaptureMouse)
                //    {
                //        m_input.NotifyMouseDown(MouseButton::LEFT);
                //    }
                //    return 0;
                //}

                //case WM_LBUTTONUP:
                //{
                //    if (!imguiIo || !imguiIo->WantCaptureMouse)
                //        m_input.NotifyMouseUp(MouseButton::LEFT);
                //    return 0;
                //}

                //case WM_RBUTTONDOWN:
                //{
                //    if (!imguiIo || !imguiIo->WantCaptureMouse)
                //        m_input.NotifyMouseDown(MouseButton::RIGHT);
                //    return 0;
                //}

                //case WM_RBUTTONUP:
                //{
                //    if (!imguiIo || !imguiIo->WantCaptureMouse)
                //        m_input.NotifyMouseUp(MouseButton::RIGHT);
                //    return 0;
                //}

                //case WM_MBUTTONDOWN:
                //{
                //    if (!imguiIo || !imguiIo->WantCaptureMouse)
                //        m_input.NotifyMouseDown(MouseButton::MIDDLE);
                //    return 0;
                //}

                //case WM_MBUTTONUP:
                //{
                //    if (!imguiIo || !imguiIo->WantCaptureMouse)
                //        m_input.NotifyMouseUp(MouseButton::MIDDLE);
                //    return 0;
                //}

                case WM_CLOSE:
                {
                    //NF_LOG_INFO("[WINDOW] Close button pressed");
                    shouldClose = true;
                    return 0;
                }

                case WM_SETFOCUS:
                {
                    //INFO(L"[WINDOW] Focused");

                    isFocused = true;
                    return 0;
                }

                case WM_KILLFOCUS:
                {
                    //INFO(L"[WINDOW] Unfocused");

                    isFocused = false;
                    //m_input.NotifyInvalidateMousePosition();

                    return 0;
                }

                case WM_SIZE:
                {
                    newWidth = LOWORD(lParam);
                    newHeight = HIWORD(lParam);

                    switch (wParam)
                    {
                        case SIZE_MINIMIZED:
                        {
                            //NF_LOG_INFO("[WINDOW] Minimized");

                            isMinimized = true;
                            return 0;
                        }
                        case SIZE_MAXIMIZED:
                        {
                            //NF_LOG_INFO("[WINDOW] Maximized");

                            isMinimized = false;
                            isMaximized = true;

                            lResize();

                            return 0;
                        }
                        case SIZE_RESTORED:
                        {
                            //NF_LOG_INFO("[WINDOW] Restored");
                            isMinimized = false;

                            if (isMaximized)
                            {
                                isMaximized = false;
                                lResize();
                            }

                            return 0;
                        }
                    }
                    return 0;
                }

                case WM_DPICHANGED:
                {
                    RECT* pRect{ reinterpret_cast<RECT*>(lParam) };

                    SetWindowPos(
                        hWnd,
                        nullptr,
                        pRect->left,
                        pRect->top,
                        pRect->right - pRect->left,
                        pRect->bottom - pRect->top,
                        SWP_NOZORDER | SWP_NOACTIVATE
                    );

                    return 0;
                }

                case WM_EXITSIZEMOVE:
                {
                    lResize();
                    return 0;
                }

                case WM_DESTROY:
                {
                    PostQuitMessage(0);
                    return 0;
                }

                default:
                {
                    return DefWindowProc(hWnd, uMsg, wParam, lParam);
                }
            }
        }
    }
}