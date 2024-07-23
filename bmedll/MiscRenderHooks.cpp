#include "pch.h"
#include "tier0.h"
#include "TTFSDK.h"
#include "MiscHooks.h"

typedef void(__fastcall* sub_18000BAC0_type)(float*, float*, float*);
sub_18000BAC0_type sub_18000BAC0_org = nullptr;
void __fastcall sub_18000BAC0(float* a1, float* a2, float* a3)
{
    static auto& hudwarp_disable = SDK().GetVstdlibCvar()->FindVar("hudwarp_disable")->GetIntRef();
    if (hudwarp_disable) {
        // Still perform scaling for HUD when warping is disabled
        // Ported from TFORevive by Barnaby
        float viewWidth = a1[2];
        float viewHeight = a1[3];

        float xScale = a1[7];
        float yScale = a1[9];

        if (xScale < 1.0f)
            a3[0] = (a2[0] - 0.5f * viewWidth) * xScale + 0.5f * viewWidth;
        else
            a3[0] = a2[0];

        if (yScale < 1.0f)
            a3[1] = (a2[1] - 0.5f * viewHeight) * yScale + 0.5f * viewHeight;
        else
            a3[1] = a2[1];

        a3[2] = a2[2];
        return;
    }
    sub_18000BAC0_org(a1, a2, a3);
}

struct HudwarpSettings {
    float xWarp;
    float xScale;
    float yWarp;
    float yScale;
    float viewDist;
};

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

    // If hudwarp is disabled do this
    // Replace chopsize, it gets set from the cvar in CMatSystemSurface__ApplyHudwarpSettings
    if (hudwarp_disable->GetInt())
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

void DoMiscRenderHooks()
{
    DWORD64 vguimatsurfacedllBaseAddress = Util::GetModuleBaseAddress("vguimatsurface.dll");
    CreateMiscHook(vguimatsurfacedllBaseAddress, 0xBAC0, &sub_18000BAC0, reinterpret_cast<LPVOID*>(&sub_18000BAC0_org));
    CreateMiscHook(vguimatsurfacedllBaseAddress, 0x15A30, &CMatSystemSurface__ApplyHudwarpSettings, reinterpret_cast<LPVOID*>(&CMatSystemSurface__ApplyHudwarpSettings_org));
}