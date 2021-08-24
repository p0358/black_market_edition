#include "pch.h"
#include <regex>
#include <algorithm>
#include <string>
#include "ISurface.h"
#include "SigScanning.h"
#include "ModuleScan.h"
#include "UIManager.h"
#include "IInputSystem.h"
#include "TTFSDK.h"

UIManager& UIMan()
{
    /*if (!&SDK() || !&(SDK().GetUIManager())) {
        UIManager* u = nullptr;
        return *u;
    }*/
    return SDK().GetUIManager();
}

#define WRAPPED_MEMBER(name) MemberWrapper<decltype(&UIManager::##name), &UIManager::##name, decltype(&UIMan), &UIMan>::Call

//SigScanFunc<void> d3d11ContextFinder("materialsystem_dx11.dll", "\x40\x53\x48\x83\xEC\x00\x48\x8B\x0D\x00\x00\x00\x00\x48\x8B\x01\xFF\x90\x00\x00\x00\x00\xE8\x00\x00\x00\x00", "xxxxx?xxx????xxxxx????x????");
//SigScanFunc<void> d3d11SwapChainFinder("materialsystem_dx11.dll", "\x48\x89\x5C\x24\x00\x57\x48\x83\xEC\x00\x48\x83\x3D\x00\x00\x00\x00\x00\x8B\xDA", "xxxx?xxxx?xxx?????xx");

HookedVTableFunc<decltype(&IDXGISwapChainVtbl::Present), &IDXGISwapChainVtbl::Present> IDXGISwapChain_Present;

HookedSigScanFunc<int, void*, HWND, UINT, WPARAM, LPARAM> GameWindowProc("inputsystem.dll", "\x48\x89\x54\x24\x00\x55\x56\x41\x54", "xxxx?xxxx");

HookedVTableFunc<decltype(&ISurface::VTable::LockCursor), &ISurface::VTable::LockCursor> ISurface_LockCursor; // does it work?
HookedVTableFunc<decltype(&ISurface::VTable::SetCursor), &ISurface::VTable::SetCursor> ISurface_SetCursor; // does it work?

/*typedef void* voidptr_t;

template <typename X, int (X::* fn)(int, voidptr_t[], void*)>
int wrap_function(Args... args) {
    return (static_cast<X*>(args[0])->*fn)(argc - 1, &args[1], data);
}*/

UIManager::UIManager(ConCommandManager& conCommandManager/*, SquirrelManager& sqManager*/, FileSystemManager& fsManager/*, ID3D11Device** ppD3DDevice*/) :
    m_surface("vguimatsurface.dll", "VGUI_Surface031")
{
    m_logger = spdlog::get("logger");

    // Get pointer to d3d context
    //char* funcBase = (char*)d3d11ContextFinder.GetFuncPtr();
    //int offset = *(int*)(funcBase + 9);
    //m_ppD3D11DeviceContext = (ID3D11DeviceContext**)(funcBase + 13 + offset); // +0x14E8DD8
/* // in sub_180014FB0:
  TxaaU4 TxaaOpenDX(
  TxaaCtxDX* __TXAA_RESTRICT__ const ctx,
  ID3D11Device* __TXAA_RESTRICT__ const dev,
  ID3D11DeviceContext* __TXAA_RESTRICT__ const dxCtx);
*/
    m_ppD3DDevice = (ID3D11Device**)(Util::GetModuleBaseAddress("materialsystem_dx11.dll") + 0x290D88);
    m_ppD3D11DeviceContext = (ID3D11DeviceContext**)(Util::GetModuleBaseAddress("materialsystem_dx11.dll") + 0x290D90);

    // Get the swap chain
    /*funcBase = (char*)d3d11SwapChainFinder.GetFuncPtr();
    offset = *(int*)(funcBase + 13);
    m_ppSwapChain = (IDXGISwapChain**)(funcBase + 18 + offset);*/
    m_ppSwapChain = (IDXGISwapChain**)(Util::GetModuleBaseAddress("materialsystem_dx11.dll") + 0x293348);

    SPDLOG_LOGGER_DEBUG(m_logger, "m_ppD3D11DeviceContext = {}", (void*)m_ppD3D11DeviceContext);
    SPDLOG_LOGGER_DEBUG(m_logger, "pD3D11DeviceContext = {}", (void*)*m_ppD3D11DeviceContext);

    SPDLOG_LOGGER_DEBUG(m_logger, "m_ppSwapChain = {}", (void*)m_ppSwapChain);
    SPDLOG_LOGGER_DEBUG(m_logger, "pSwapChain = {}", (void*)*m_ppSwapChain);

    InitImGui(fsManager.GetModsPath());

    using namespace std::placeholders;

    SPDLOG_LOGGER_TRACE(m_logger, "Will hook IDXGISwapChain_Present");
    //IDXGISwapChain_Present.Hook(((IDXGISwapChainC*) *m_ppSwapChain)->lpVtbl, WRAPPED_MEMBER(PresentHook));
    HRESULT STDMETHODCALLTYPE IDXGISwapChain_Present_Hook(IDXGISwapChain * SwapChain, UINT SyncInterval, UINT Flags);
    IDXGISwapChain_Present.Hook(((IDXGISwapChainC*) *m_ppSwapChain)->lpVtbl, IDXGISwapChain_Present_Hook);

    SPDLOG_LOGGER_TRACE(m_logger, "Will hook GameWindowProc");
    //GameWindowProc.Hook(WRAPPED_MEMBER(WindowProcHook));
    //auto f = std::bind(&UIManager::WindowProcHook, this, _1, _2, _3, _4, _5);
    //GameWindowProc.Hook(f);
    //GameWindowProc.Hook( /*(int(*)(void*, HWND, UINT, WPARAM, LPARAM))*/ (LPVOID) [this](void* a1, HWND a2, UINT a3, WPARAM a4, LPARAM a5) -> int {return this->WindowProcHook(a1, a2, a3, a4, a5);});
    //    using my_lambda_type = int(*)(void*, HWND, UINT, WPARAM, LPARAM);
    //    //my_lambda_type my_func = [this](void* a1, HWND a2, UINT a3, WPARAM a4, LPARAM a5) -> int {return 0;/*this->WindowProcHook(a1, a2, a3, a4, a5);*/ };
    //    my_lambda_type a = [](void* a1, HWND a2, UINT a3, WPARAM a4, LPARAM a5) -> int {
    //        //if (&UIMan() == nullptr) return 0;
    //        if (&UIMan() == nullptr) return GameWindowProc(a1, a2, a3, a4, a5);
    //        return UIMan().WindowProcHook(a1, a2, a3, a4, a5);
    //    };//this->WindowProcHook(a1, a2, a3, a4, a5);
    ///////////////GameWindowProc.Hook( /*(int(*)(void*, HWND, UINT, WPARAM, LPARAM))*/ (void*)a );
    int GameWindowProc_Hook(void* game, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    GameWindowProc.Hook(GameWindowProc_Hook);
    SPDLOG_LOGGER_TRACE(m_logger, "Will hook ISurface_SetCursor and ISurface_LockCursor");
    //ISurface_SetCursor.Hook(m_surface->m_vtable, WRAPPED_MEMBER(SetCursorHook));
    //ISurface_LockCursor.Hook(m_surface->m_vtable, WRAPPED_MEMBER(LockCursorHook));
    void ISurface_SetCursor_Hook(ISurface * surface, unsigned int cursor);
    void ISurface_LockCursor_Hook(ISurface * surface);
    ISurface_SetCursor.Hook(m_surface->m_vtable, ISurface_SetCursor_Hook);
    ISurface_LockCursor.Hook(m_surface->m_vtable, ISurface_LockCursor_Hook);

    conCommandManager.RegisterCommand("show_cursor", WRAPPED_MEMBER(ShowCursorCommand), "Set visibility of cursor", 0);

    //sqManager.AddFuncRegistration(CONTEXT_CLIENT, "void", "ShowCursor", "", "", WRAPPED_MEMBER(SQShowCursor));
    //sqManager.AddFuncRegistration(CONTEXT_CLIENT, "void", "HideCursor", "", "", WRAPPED_MEMBER(SQHideCursor));
}

UIManager::~UIManager()
{
    SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "UIManager destructor");
    IDXGISwapChain_Present.Unhook();
    GameWindowProc.Unhook();
    ISurface_SetCursor.Unhook();
    ISurface_LockCursor.Unhook();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void UIManager::InitImGui(const fs::path& modsPath)
{
    m_gameWindow = FindWindowW(L"Respawn001", L"Titanfall");
    m_logger->info("Game window = {}", (void*)m_gameWindow);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    
    ImGui::StyleColorsLight();
    /*ImGui::StyleColorsDark(); SPDLOG_LOGGER_TRACE(m_logger, "After ImGui::StyleColorsDark");
    ImGuiStyle* style = &ImGui::GetStyle(); SPDLOG_LOGGER_TRACE(m_logger, "After ImGui::GetStyle");
    ImVec4* colors = style->Colors;
    // lorange = #B25612 = 
    colors[ImGuiCol_Header] = ImVec4(0.7f, 0.34f, 0.07f, 0.41f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.7f, 0.34f, 0.07f, 0.80f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.7f, 0.34f, 0.07f, 1.00f);*/

    ImGui::GetIO().IniFilename = nullptr; SPDLOG_LOGGER_TRACE(m_logger, "After ImGui::GetIO().IniFilename");

    // Check if the font file exists in the icepick mod
    /*fs::path fontPath = modsPath / "Icepick.Framework/fonts/NotoSans-Medium.ttf";
    if (fs::exists(fontPath))
    {
        ImGui::GetIO().Fonts->AddFontFromFileTTF(fontPath.string().c_str(), 16.0f);
    }*/
}

void UIManager::ShowCursorCommand(const CCommand& args)
{
    if (strcmp(args[1], "1") == 0)
    {
        SQShowCursor(0); // TODO: Fix this
    }
    else if (strcmp(args[1], "0") == 0)
    {
        SQHideCursor(0); // TODO: Fix this
    }
    else
    {
        m_logger->error("Invalid argument to show_cursor, must be 1 or 0");
    }
}

/*SQInteger*/char UIManager::SQShowCursor(/*HSQUIRRELVM*/char v)
{
    m_enableCursor = true;
    SPDLOG_LOGGER_DEBUG(m_logger, "Showing cursor");
    UpdateImGuiKeyStates();
    m_surface->m_vtable->UnlockCursor(m_surface);
    ISurface_SetCursor(m_surface, dc_arrow);
    return 0;
}

/*SQInteger*/char UIManager::SQHideCursor(/*HSQUIRRELVM*/char v)
{
    m_enableCursor = false;
    SPDLOG_LOGGER_DEBUG(m_logger, "Hiding cursor");
    UpdateImGuiKeyStates();
    return 0;
}

void UIManager::DrawFPS()
{
    const float DISTANCE = 10.0f;
    static int corner = 0; // -1 = custom; 0 = top-left; 1 = top-right; 2 = bottom-left; 3 = bottom-right
    ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
    ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
    if (corner != -1)
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowBgAlpha(0.0f); // really transparent background
    ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
    ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(1.0f, 1.0f, 1.0f, 1.0f));
    if (ImGui::Begin("FPSOverlay", nullptr, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav | (corner != -1 ? ImGuiWindowFlags_NoInputs : 0)))
    {
        ImGui::Text("FPS: %.0f", ImGui::GetIO().Framerate);
    }
    ImGui::End();
    ImGui::PopStyleVar();
    ImGui::PopStyleColor();
    ImGui::PopStyleColor();
}

void UIManager::DrawGUI()
{
    const float DISTANCE = 10.0f;
    static int corner = 0;
    ImVec2 window_pos = ImVec2((corner & 1) ? ImGui::GetIO().DisplaySize.x - DISTANCE : DISTANCE, (corner & 2) ? ImGui::GetIO().DisplaySize.y - DISTANCE : DISTANCE);
    ImVec2 window_pos_pivot = ImVec2((corner & 1) ? 1.0f : 0.0f, (corner & 2) ? 1.0f : 0.0f);
    if (corner != -1)
        ImGui::SetNextWindowPos(window_pos, ImGuiCond_Always, window_pos_pivot);
    ImGui::SetNextWindowBgAlpha(0.3f); // Transparent background
    if (ImGui::Begin("DebugOverlay", nullptr, (corner != -1 ? ImGuiWindowFlags_NoMove : 0) | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoFocusOnAppearing | ImGuiWindowFlags_NoNav))
    {
        ImGui::Text("FPS: %.1f", ImGui::GetIO().Framerate);
        if (ImGui::IsMousePosValid())
            ImGui::Text("Mouse Position: (%.1f,%.1f)", ImGui::GetIO().MousePos.x, ImGui::GetIO().MousePos.y);
        else
            ImGui::Text("Mouse Position: <invalid>");
        ImGui::Text("m_enableCursor: %d", (int)m_enableCursor);
        ImGui::Text("m_engineCursorSet: %d", (int)m_engineCursorSet);
        ImGui::Text("IsCursorVisible: %d", m_surface->m_vtable->IsCursorVisible(m_surface));
        ImGui::Text("WantCaptureMouse: %d", ImGui::GetIO().WantCaptureMouse);
        ImGui::Text("WantCaptureKeyboard: %d", ImGui::GetIO().WantCaptureKeyboard);
        ImGui::Text("Mouse Delta X: %d", SDK().GetInputSystem()->m_analogDeltaX);
        ImGui::Text("Mouse Delta Y: %d", SDK().GetInputSystem()->m_analogDeltaY);
        for (int i = 0; i < 256; i++)
        {
            if (ImGui::GetIO().KeysDown[i] == 1)
            {
                ImGui::Text("Key Down: %d", i);
            }
        }
    }
    ImGui::End();
}

void UIManager::AddDrawCallback(const std::string& name, bool* draw, const std::function<void()>& func)
//void UIManager::AddDrawCallback(const std::string& name, draw_callback dcb)
{
    //draw_callback dcb = {draw, func};
    //m_drawCallbacks[name] = draw_callback(draw, func);
    //m_drawCallbacks.insert(std::pair(name, dcb));
    m_drawCallbacks[name] = std::pair(draw, func);
}

void UIManager::RemoveDrawCallback(const std::string& name)
{
    m_drawCallbacks.erase(name);
}

bool IsKeyMsg(UINT uMsg)
{
    return uMsg >= WM_KEYFIRST && uMsg <= WM_KEYLAST;
}

bool IsMouseMsg(UINT uMsg)
{
    return uMsg >= WM_MOUSEFIRST && uMsg <= WM_MOUSELAST;
}

bool UIManager::IsACursorVisible()
{
    return m_enableCursor || m_engineCursorSet;
}

void UIManager::UpdateImGuiKeyStates()
{
    for (int i = 0; i < 256; i++)
    {
        ImGui::GetIO().KeysDown[i] = (GetKeyState(i) & 0x8000) != 0 ? 1 : 0;
    }
}

int GameWindowProc_Hook(void* game, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (IsSDKReady())
        return UIMan().WindowProcHook(game, hWnd, uMsg, wParam, lParam);
    return GameWindowProc(game, hWnd, uMsg, wParam, lParam);
}

extern LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
int UIManager::WindowProcHook(void* game, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    if (uMsg == WM_QUERYENDSESSION && lParam == ENDSESSION_CLOSEAPP)
        return true;

    if (uMsg == WM_ENDSESSION && lParam == ENDSESSION_CLOSEAPP)
    {
        /*SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "WM_ENDSESSION");
        isProcessTerminating = true;
        SDK().GetEngineClient()->ClientCmd_Unrestricted("quit");
        if (!SDK().runFrameHookCalled)
        {
            FreeSDK();
            //TerminateProcess(GetCurrentProcess(), 0);
        }
        //return true;
        return GameWindowProc(game, hWnd, uMsg, wParam, lParam);*/
    }

    if (uMsg == WM_CLOSE)
    {
        /*SPDLOG_LOGGER_DEBUG(spdlog::get(_("logger")), "WM_CLOSE");
        isProcessTerminating = true;
        if (&SDK() != nullptr && SDK().GetEngineClient() != nullptr && SDK().GetEngineClient() != NULL)
            SDK().GetEngineClient()->ClientCmd_Unrestricted("quit");
        if (!SDK().runFrameHookCalled)
        {
            FreeSDK();
            //TerminateProcess(GetCurrentProcess(), 0);
        }
        //return true;
        return GameWindowProc(game, hWnd, uMsg, wParam, lParam);*/
    }

    // Don't pass to imgui if there's no cursor visible
    if (uMsg == WM_SETCURSOR || !IsACursorVisible())
    {
        return GameWindowProc(game, hWnd, uMsg, wParam, lParam);
    }

    ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam);

    // Do not pass to game if we're forcing the cursor
    bool forcedCursor = m_enableCursor && !m_engineCursorSet;

    // Only block from game if imgui capturing
    if (IsMouseMsg(uMsg) && (forcedCursor || ImGui::GetIO().WantCaptureMouse))
    {
        return 0;
    }

    if (IsKeyMsg(uMsg) && ImGui::GetIO().WantCaptureKeyboard)
    {
        return 0;
    }

    return GameWindowProc(game, hWnd, uMsg, wParam, lParam);
}

static bool ImGui_UpdateMouseCursor(ISurface* surface)
{
    ImGuiIO& io = ImGui::GetIO();
    //if (io.ConfigFlags & ImGuiConfigFlags_NoMouseCursorChange)
    //    return false;

    ImGuiMouseCursor imgui_cursor = io.MouseDrawCursor ? ImGuiMouseCursor_None : ImGui::GetMouseCursor();
    if (imgui_cursor == ImGuiMouseCursor_None)
    {
        // Hide OS mouse cursor if imgui is drawing it or if it wants no cursor
        ISurface_SetCursor(surface, dc_none);
    }
    else
    {
        // Hardware cursor type
        unsigned int cursor = dc_arrow;
        switch (imgui_cursor)
        {
        case ImGuiMouseCursor_Arrow:        cursor = dc_arrow; break;
        case ImGuiMouseCursor_TextInput:    cursor = dc_ibeam; break;
        case ImGuiMouseCursor_ResizeAll:    cursor = dc_sizeall; break;
        case ImGuiMouseCursor_ResizeEW:     cursor = dc_sizewe; break;
        case ImGuiMouseCursor_ResizeNS:     cursor = dc_sizens; break;
        case ImGuiMouseCursor_ResizeNESW:   cursor = dc_sizenesw; break;
        case ImGuiMouseCursor_ResizeNWSE:   cursor = dc_sizenwse; break;
        }
        ISurface_SetCursor(surface, cursor);
    }
    return true;
}

void ISurface_SetCursor_Hook(ISurface* surface, unsigned int cursor)
{
    if (IsSDKReady())
        return UIMan().SetCursorHook(surface, cursor);
}

void UIManager::SetCursorHook(ISurface* surface, unsigned int cursor)
{
    bool cursorSet = (cursor != dc_user && cursor != dc_none && cursor != dc_blank);
    if (!IsACursorVisible() && cursorSet != m_engineCursorSet)
    {
        UpdateImGuiKeyStates();
    }

    m_engineCursorSet = cursorSet;

    // If no cursors, let the engine deal with it
    if (!IsACursorVisible())
    {
        return ISurface_SetCursor(surface, cursor);
    }

    // If there's a cursor, and ImGui is capturing, let that handle it
    if (ImGui::GetIO().WantCaptureMouse)
    {
        ImGui_UpdateMouseCursor(surface);
        return;
    }

    // If we're forcing the cursor and the engine isn't, use ours
    if (m_enableCursor && !m_engineCursorSet)
    {
        ImGui_UpdateMouseCursor(surface);
        return;
    }

    // Otherwise let the game handle it
    ISurface_SetCursor(surface, cursor);
}

void ISurface_LockCursor_Hook(ISurface* surface)
{
    if (IsSDKReady())
        return UIMan().LockCursorHook(surface);
}

void UIManager::LockCursorHook(ISurface* surface)
{
    // Only allow the cursor to be locked if we're not forcing it
    if (!m_enableCursor)
    {
        return ISurface_LockCursor(surface);
    }
}

HRESULT STDMETHODCALLTYPE IDXGISwapChain_Present_Hook(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)
{
    if (IsSDKReady())
    {
        UIMan().PresentHook(SwapChain, SyncInterval, Flags);
    }
    return IDXGISwapChain_Present(SwapChain, SyncInterval, Flags);
}

void UIManager::PresentHook(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags)
{
    //SPDLOG_LOGGER_TRACE(m_logger, "IDXGISwapChain_Present");
    static bool deviceObjectsInitialised = false;
    if (!deviceObjectsInitialised)
    {
        ImGui_ImplWin32_Init(m_gameWindow); SPDLOG_LOGGER_TRACE(m_logger, "After ImGui_ImplWin32_Init");
        ImGui_ImplDX11_Init(*m_ppD3DDevice, *m_ppD3D11DeviceContext); SPDLOG_LOGGER_TRACE(m_logger, "After ImGui_ImplDX11_Init");

        ImGui_ImplDX11_CreateDeviceObjects();
        deviceObjectsInitialised = true;

        static bool drawFPS = true;
        AddDrawCallback("DrawFPS", &drawFPS, std::bind(&UIManager::DrawFPS, this));
    }

    bool anyDraw = false;
    for (const auto& entry : m_drawCallbacks)
        if (*entry.second.first) anyDraw = true;

    if (anyDraw) {

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        //DrawGUI();
        for (const auto& entry : m_drawCallbacks)
        {
            SPDLOG_LOGGER_TRACE(m_logger, "UIManager::PresentHook: will execute function for {}", entry.first);
            entry.second.second();
            SPDLOG_LOGGER_TRACE(m_logger, "UIManager::PresentHook: did execute function for {}", entry.first);
        }

        ImGui::Render();
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

    }

    //return IDXGISwapChain_Present(SwapChain, SyncInterval, Flags);
}

void UIManager::DrawTest()
{
    /*static bool deviceObjectsInitialised = false;
    if (!deviceObjectsInitialised)
    {
        ImGui_ImplDX11_CreateDeviceObjects();
        deviceObjectsInitialised = true;
    }

    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    DrawGUI();
    for (const auto& entry : m_drawCallbacks)
    {
        entry.second();
    }

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());*/
}