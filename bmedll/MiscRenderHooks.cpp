#include "pch.h"
#include "tier0.h"
#include "TTFSDK.h"
#include "MiscHooks.h"
#include "Hudwarp.h"

#include <d3d11_1.h>

bool shouldUseGPUHudwarp = false;
bool isHudwarpDisabled = false;

bool isRenderingHud = false;
HudwarpProcess* hudwarpProcess = nullptr;

typedef void(__fastcall* sub_18000BAC0_type)(float*, float*, float*);
sub_18000BAC0_type sub_18000BAC0_org = nullptr;
void __fastcall sub_18000BAC0(float* a1, float* a2, float* a3)
{
    // Ported from TFORevive by Barnaby

    if (!shouldUseGPUHudwarp)
    {
        // If hudwarp is disabled and running on CPU do just the scaling
        if (isHudwarpDisabled)
        {
            // Still perform scaling for HUD when warping is disabled
            float viewWidth = a1[2];
            float viewHeight = a1[3];

            float xScale = a1[7];
            float yScale = a1[9];

            a3[0] = (a2[0] - 0.5f * viewWidth) * xScale + 0.5f * viewWidth;
            a3[1] = (a2[1] - 0.5f * viewHeight) * yScale + 0.5f * viewHeight;
            a3[2] = a2[2];
            return;
        }

        return sub_18000BAC0_org(a1, a2, a3);
    }

    // We prevent the hud from reaching bounds of render texture by adding a border of 0.025 * width/height to the texture
    // We need to offset the verts to account for that here
    const float hudOffset = HUD_TEX_BORDER_SIZE;
    const float hudScale = 1.0f - 2.0f * hudOffset;

    float viewWidth = a1[2];
    float viewHeight = a1[3];

    a3[0] = a2[0] * hudScale + hudOffset * viewWidth;
    a3[1] = a2[1] * hudScale + hudOffset * viewHeight;
    a3[2] = a2[2];
}

typedef void(__fastcall* CMatSystemSurface__ApplyHudwarpSettings_type)(void*, HudwarpSettings*, unsigned int, unsigned int);
CMatSystemSurface__ApplyHudwarpSettings_type CMatSystemSurface__ApplyHudwarpSettings_org = nullptr;
void __fastcall CMatSystemSurface__ApplyHudwarpSettings(void* thisptr, HudwarpSettings* hudwarpSettings, unsigned int screenX, unsigned int screenY)
{
    // Ported from TFORevive by Barnaby

    static ConVarRef hudwarp_chopsize{ "hudwarp_chopsize" };
    unsigned int originalChopsize = hudwarp_chopsize->GetInt();

    static ConVarRef hudwarp_disable{ "hudwarp_disable" };
    HudwarpSettings newSettings = *hudwarpSettings;
    if (hudwarp_disable->GetInt())
    {
        // Override hudwarp settings if hudwarp_disable is 1.
        // NOTE: Comment below refers to original CPU version, we can set them to 0 when using our shader.
        // Stuff breaks if you set the warp values to 0.
        // Respawn set them to a min of 1deg in rads (0.017453292), we can do that too because it'll result in so little distortion you won't notice it :)
        newSettings.xWarp = 0.0f;
        if (newSettings.xScale > 1.0f) newSettings.xScale = 1.0f;
        newSettings.yWarp = 0.0f;
        if (newSettings.yScale > 1.0f) newSettings.yScale = 1.0f;
    }

    if (hudwarpProcess)
        hudwarpProcess->UpdateSettings(&newSettings);

    static ConVarRef hudwarp_use_gpu{ "hudwarp_use_gpu" };
    // If using GPU hudwarp or hudwarp is disabled do this
    // Replace chopsize, it gets set from the cvar in CMatSystemSurface__ApplyHudwarpSettings
    if (hudwarp_use_gpu->GetInt() || hudwarp_disable->GetInt())
    {
        if (screenX > screenY) [[likely]]
        {
            hudwarp_chopsize->SetValueInt(screenX);
        }
        else
        {
            hudwarp_chopsize->SetValueInt(screenY);
        }
    }

    CMatSystemSurface__ApplyHudwarpSettings_org(thisptr, &newSettings, screenX, screenY);

    hudwarp_chopsize->SetValueInt(originalChopsize);
}

ID3D11Device* pDevice;
ID3D11DeviceContext** ppID3D11DeviceContext;
ID3DUserDefinedAnnotation* pPerf;

typedef __int64(*__fastcall SetPixMarker_type)(__int64 queuedRenderContext, unsigned long color, const char* pszName);
FuncStaticWithType<SetPixMarker_type> SetPixMarker("materialsystem_dx11", 0x5D7E0);

void QueueSetMarker(const char* markerName)
{
    static DWORD64 enginedllBaseAddress = Util::GetModuleBaseAddress("engine.dll");
    static auto materials = *(__int64*)(enginedllBaseAddress + 0x318A688);
    auto queuedRenderContext = (*(__int64(__fastcall**)(__int64))(*(_QWORD*)materials + 896i64))(materials);

    SetPixMarker(queuedRenderContext, 0, markerName);
}

void QueueBeginEvent(const char* markerName)
{
    static DWORD64 enginedllBaseAddress = Util::GetModuleBaseAddress("engine.dll");
    static auto materials = *(__int64*)(enginedllBaseAddress + 0x318A688);
    auto queuedRenderContext = (*(__int64(__fastcall**)(__int64))(*(_QWORD*)materials + 896i64))(materials);

    SetPixMarker(queuedRenderContext, 111111, markerName); // hijack color field for our purposes
}

void QueueEndEvent()
{
    static DWORD64 enginedllBaseAddress = Util::GetModuleBaseAddress("engine.dll");
    static auto materials = *(__int64*)(enginedllBaseAddress + 0x318A688);
    auto queuedRenderContext = (*(__int64(__fastcall**)(__int64))(*(_QWORD*)materials + 896i64))(materials);

    SetPixMarker(queuedRenderContext, 222222, ""); // hijack color field for our purposes
}

void HudRenderStart()
{
    if (!shouldUseGPUHudwarp)
        return;

    if (hudwarpProcess)
        hudwarpProcess->Begin();
}

void HudRenderFinish()
{
    if (!shouldUseGPUHudwarp)
        return;

    if (hudwarpProcess)
        hudwarpProcess->Finish();
}

typedef void(__fastcall* OnWindowSizeChanged_type)(unsigned int, unsigned int, bool);
OnWindowSizeChanged_type OnWindowSizeChanged_org = nullptr;
void __fastcall OnWindowSizeChanged(unsigned int w, unsigned int h, bool isInGame)
{
    OnWindowSizeChanged_org(w, h, isInGame);

    if (hudwarpProcess)
        hudwarpProcess->Resize(w, h);
}

HookedFuncStaticWithType<SetPixMarker_type> sub_5ADC0("materialsystem_dx11.dll", 0x5ADC0);
__int64 __fastcall sub_5ADC0_Hook(__int64 queuedRenderContext, unsigned long color, const char* pszName)
{
    static unsigned int hudEventDepth = 0;

    switch (color)
    {
    case 111111:
        pPerf->BeginEvent(Util::Widen(pszName).c_str());

        if (!strcmp(pszName, "HUD"))
        {
            isRenderingHud = true;
            HudRenderStart();
        }

        if (isRenderingHud)
            hudEventDepth++;
        break;
    case 222222:
        if (isRenderingHud)
        {
            hudEventDepth--;
            if (hudEventDepth == 0)
            {
                isRenderingHud = false;
                HudRenderFinish();
            }
        }

        pPerf->EndEvent();
        break;
    default:
        pPerf->SetMarker(Util::Widen(pszName).c_str());
    }

    return sub_5ADC0(queuedRenderContext, color, pszName);
}

typedef void(*__fastcall RenderHud_type)(__int64 a1, __int64 a2, __int64 a3);
HookedFuncStaticWithType<RenderHud_type> RenderHud("client.dll", 0x2AE630);
void __fastcall RenderHud_Hook(__int64 a1, __int64 a2, __int64 a3)
{
    // Update state once per frame to prevent possible issues with one or neither applying
    static ConVarRef hudwarp_use_gpu{ "hudwarp_use_gpu" };
    shouldUseGPUHudwarp = hudwarp_use_gpu->GetInt();

    static ConVarRef hudwarp_disable{ "hudwarp_disable" };
    isHudwarpDisabled = hudwarp_disable->GetInt();

    QueueBeginEvent("HUD");
    RenderHud(a1, a2, a3);
    QueueEndEvent();
}

void SetupHudwarp()
{
    pDevice = *(ID3D11Device**)(Util::GetModuleBaseAddress("materialsystem_dx11.dll") + 0x290D88);
    ppID3D11DeviceContext = (ID3D11DeviceContext**)(Util::GetModuleBaseAddress("materialsystem_dx11.dll") + 0x290D90);

    HRESULT hr = (*ppID3D11DeviceContext)->QueryInterface(__uuidof(pPerf), reinterpret_cast<void**>(&pPerf));
    if (FAILED(hr))
        pPerf = nullptr;

    hudwarpProcess = new HudwarpProcess(pDevice, ppID3D11DeviceContext);
}

typedef bool(__fastcall* sub_63D0_type)(HWND, unsigned int, __int64);
sub_63D0_type sub_63D0_org;
char __fastcall sub_63D0(HWND a1, unsigned int a2, __int64 a3)
{
    // Initialization of DirectX swapchain and related device/context setup
    auto ret = sub_63D0_org(a1, a2, a3);

    // Init GPU Hudwarp
    SetupHudwarp();

    return ret;
}

void DoMiscRenderHooks()
{
    DWORD64 vguimatsurfacedllBaseAddress = Util::GetModuleBaseAddress("vguimatsurface.dll");
    DWORD64 materialsystem_dx11dllBaseAddress = Util::GetModuleBaseAddress("materialsystem_dx11.dll");

    CreateMiscHook(vguimatsurfacedllBaseAddress, 0xBAC0, &sub_18000BAC0, reinterpret_cast<LPVOID*>(&sub_18000BAC0_org));
    CreateMiscHook(vguimatsurfacedllBaseAddress, 0x15A30, &CMatSystemSurface__ApplyHudwarpSettings, reinterpret_cast<LPVOID*>(&CMatSystemSurface__ApplyHudwarpSettings_org));

    RenderHud.Hook(RenderHud_Hook);

    sub_5ADC0.Hook(sub_5ADC0_Hook);
    CreateMiscHook(materialsystem_dx11dllBaseAddress, 0x63D0, &sub_63D0, reinterpret_cast<LPVOID*>(&sub_63D0_org));
}