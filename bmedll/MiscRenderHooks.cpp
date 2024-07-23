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

void DoMiscRenderHooks()
{
    DWORD64 vguimatsurfacedllBaseAddress = Util::GetModuleBaseAddress("vguimatsurface.dll");
    CreateMiscHook(vguimatsurfacedllBaseAddress, 0xBAC0, &sub_18000BAC0, reinterpret_cast<LPVOID*>(&sub_18000BAC0_org));
}