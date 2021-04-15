#pragma once
#include "pch.h"
#include "ConCommandManager.h"
#include "FileSystemManager.h"
#include "ISurface.h"

// https://github.com/tpn/winsdk-10/blob/master/Include/10.0.16299.0/shared/dxgi.h#L1766
// as defining CINTERFACE breaks ImGui on the other hand, we define needed things manually
// in fact, this is probably because we've set up pch.h to be loaded into every file (I think we did, right?)
// but I'm too lazy to fix that; it works, don't touch xd
typedef struct IDXGISwapChainVtbl
{
    BEGIN_INTERFACE

        HRESULT(STDMETHODCALLTYPE* QueryInterface)(
            IDXGISwapChain* This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */
            _COM_Outptr_  void** ppvObject);

    ULONG(STDMETHODCALLTYPE* AddRef)(
        IDXGISwapChain* This);

    ULONG(STDMETHODCALLTYPE* Release)(
        IDXGISwapChain* This);

    HRESULT(STDMETHODCALLTYPE* SetPrivateData)(
        IDXGISwapChain* This,
        /* [annotation][in] */
        _In_  REFGUID Name,
        /* [in] */ UINT DataSize,
        /* [annotation][in] */
        _In_reads_bytes_(DataSize)  const void* pData);

    HRESULT(STDMETHODCALLTYPE* SetPrivateDataInterface)(
        IDXGISwapChain* This,
        /* [annotation][in] */
        _In_  REFGUID Name,
        /* [annotation][in] */
        _In_opt_  const IUnknown* pUnknown);

    HRESULT(STDMETHODCALLTYPE* GetPrivateData)(
        IDXGISwapChain* This,
        /* [annotation][in] */
        _In_  REFGUID Name,
        /* [annotation][out][in] */
        _Inout_  UINT* pDataSize,
        /* [annotation][out] */
        _Out_writes_bytes_(*pDataSize)  void* pData);

    HRESULT(STDMETHODCALLTYPE* GetParent)(
        IDXGISwapChain* This,
        /* [annotation][in] */
        _In_  REFIID riid,
        /* [annotation][retval][out] */
        _COM_Outptr_  void** ppParent);

    HRESULT(STDMETHODCALLTYPE* GetDevice)(
        IDXGISwapChain* This,
        /* [annotation][in] */
        _In_  REFIID riid,
        /* [annotation][retval][out] */
        _COM_Outptr_  void** ppDevice);

    HRESULT(STDMETHODCALLTYPE* Present)(
        IDXGISwapChain* This,
        /* [in] */ UINT SyncInterval,
        /* [in] */ UINT Flags);

    HRESULT(STDMETHODCALLTYPE* GetBuffer)(
        IDXGISwapChain* This,
        /* [in] */ UINT Buffer,
        /* [annotation][in] */
        _In_  REFIID riid,
        /* [annotation][out][in] */
        _COM_Outptr_  void** ppSurface);

    HRESULT(STDMETHODCALLTYPE* SetFullscreenState)(
        IDXGISwapChain* This,
        /* [in] */ BOOL Fullscreen,
        /* [annotation][in] */
        _In_opt_  IDXGIOutput* pTarget);

    HRESULT(STDMETHODCALLTYPE* GetFullscreenState)(
        IDXGISwapChain* This,
        /* [annotation][out] */
        _Out_opt_  BOOL* pFullscreen,
        /* [annotation][out] */
        _COM_Outptr_opt_result_maybenull_  IDXGIOutput** ppTarget);

    HRESULT(STDMETHODCALLTYPE* GetDesc)(
        IDXGISwapChain* This,
        /* [annotation][out] */
        _Out_  DXGI_SWAP_CHAIN_DESC* pDesc);

    HRESULT(STDMETHODCALLTYPE* ResizeBuffers)(
        IDXGISwapChain* This,
        /* [in] */ UINT BufferCount,
        /* [in] */ UINT Width,
        /* [in] */ UINT Height,
        /* [in] */ DXGI_FORMAT NewFormat,
        /* [in] */ UINT SwapChainFlags);

    HRESULT(STDMETHODCALLTYPE* ResizeTarget)(
        IDXGISwapChain* This,
        /* [annotation][in] */
        _In_  const DXGI_MODE_DESC* pNewTargetParameters);

    HRESULT(STDMETHODCALLTYPE* GetContainingOutput)(
        IDXGISwapChain* This,
        /* [annotation][out] */
        _COM_Outptr_  IDXGIOutput** ppOutput);

    HRESULT(STDMETHODCALLTYPE* GetFrameStatistics)(
        IDXGISwapChain* This,
        /* [annotation][out] */
        _Out_  DXGI_FRAME_STATISTICS* pStats);

    HRESULT(STDMETHODCALLTYPE* GetLastPresentCount)(
        IDXGISwapChain* This,
        /* [annotation][out] */
        _Out_  UINT* pLastPresentCount);

    END_INTERFACE
} IDXGISwapChainVtbl;

interface IDXGISwapChainC
{
    CONST_VTBL struct IDXGISwapChainVtbl* lpVtbl;
};

enum CursorCode
{
    dc_user,
    dc_none,
    dc_arrow,
    dc_ibeam,
    dc_hourglass,
    dc_waitarrow,
    dc_crosshair,
    dc_up,
    dc_sizenwse,
    dc_sizenesw,
    dc_sizewe,
    dc_sizens,
    dc_sizeall,
    dc_no,
    dc_hand,
    dc_blank,
    dc_last,
};

struct draw_callback
{
    draw_callback(bool* newDraw, const std::function<void()>& newFunc)
        : draw(newDraw), func(newFunc) {}
    bool* draw;
    const std::function<void()>& func;
};

class UIManager
{
public:
    UIManager(ConCommandManager& conCommandManager/*, SquirrelManager& sqManager*/, FileSystemManager& fsManager/*, ID3D11Device* ppD3DDevice*/);
    ~UIManager();

    void InitImGui(const fs::path& modsPath);
    void ShowCursorCommand(const CCommand& args);

    //SQInteger SQShowCursor(HSQUIRRELVM v);
    //SQInteger SQHideCursor(HSQUIRRELVM v);
    char SQShowCursor(char v); // temp?
    char SQHideCursor(char v); // temp?

    void DrawFPS();
    void DrawGUI();
    void AddDrawCallback(const std::string& name, bool* draw, const std::function<void()>& func);
    //void AddDrawCallback(const std::string& name, draw_callback dcb);
    void RemoveDrawCallback(const std::string& name);

    bool IsACursorVisible();

    void UpdateImGuiKeyStates();

    int WindowProcHook(void* game, HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
    void SetCursorHook(ISurface* surface, unsigned int cursor);
    void LockCursorHook(ISurface* surface);
    HRESULT STDMETHODCALLTYPE PresentHook(IDXGISwapChain* SwapChain, UINT SyncInterval, UINT Flags);
    void DrawTest();

private:
    std::shared_ptr<spdlog::logger> m_logger;

    ID3D11Device** m_ppD3DDevice = nullptr;
    ID3D11DeviceContext** m_ppD3D11DeviceContext = nullptr;
    IDXGISwapChain** m_ppSwapChain = nullptr;
    ID3D11RenderTargetView* m_guiRenderTargetView = nullptr;

    //std::map<std::string, std::function<void()>> m_drawCallbacks;
    //std::multimap<std::string, bool*, std::function<void()>> m_drawCallbacks;
    //std::map<std::string, draw_callback> m_drawCallbacks;
    std::map<std::string, std::pair<bool*, std::function<void()>>> m_drawCallbacks;
    SourceInterface<ISurface> m_surface;

    std::atomic_bool m_enableCursor;
    std::atomic_bool m_engineCursorSet;
};