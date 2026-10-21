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

        static
        LRESULT WindowProc(HWND hWnd, u32 uMsg, WPARAM wParam, LPARAM lParam) noexcept;
    }

    void Window::Init()
    {
        // Window needs to be initialized with Init(const Config&) method;
        NF_ASSERT(0);
    }

    void Window::Init(const Config& config)
    {
        SetProcessDpiAwarenessContext(
            DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2
        );
        
        WNDCLASSEX wc
        {
            .cbSize = sizeof(WNDCLASSEX),
            .style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW,
            .lpfnWndProc = WindowProc,
            .cbClsExtra{},
            .cbWndExtra{},
            .hInstance = GetModuleHandle(nullptr),
            .hIcon{},
            .hCursor = LoadCursor(nullptr, IDC_ARROW),
            .hbrBackground{},
            .lpszMenuName{},
            .lpszClassName = WINDOW_CLASS_NAME,
            .hIconSm{}
        };

        NF_VERIFY(RegisterClassEx(&wc));

        if (config.width == 0 || config.height == 0)
        {
            // size of client window = 3/4 * the monitor's size
            i32 monitorWidth = GetSystemMetrics(SM_CXSCREEN);
            i32 monitorHeight = GetSystemMetrics(SM_CYSCREEN);

            width = static_cast<i32>(0.75f * monitorWidth);
            height = static_cast<i32>(0.75f * monitorHeight);
        }
        else
        {
            width = config.width;
            height = config.height;
        }

        RECT clientRect = { 0, 0, static_cast<i32>(width), static_cast<i32>(height) };
        AdjustWindowRectEx(&clientRect, winStyle, false, 0);

        WString windowName = ::NF::Windows::Utf8ToWide(config.name);

        //todo: parent window for editor!!!

        // create window
        nativeWindowHandle = CreateWindowEx(
            0,
            WINDOW_CLASS_NAME,
            windowName.data(),
            winStyle,
            CW_USEDEFAULT,
            CW_USEDEFAULT,
            clientRect.right - clientRect.left,
            clientRect.bottom - clientRect.top,
            nullptr,
            nullptr,
            GetModuleHandle(nullptr),
            nullptr
        );

        NF_ASSERT(nativeWindowHandle);

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
        LRESULT WindowProc(
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