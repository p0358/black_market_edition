#include "pch.h"
#include "TTFSDK.h"
#include "tier0.h"
#include "MemoryAddress.h"
//#include "Global.h"
#include "SigScanning.h"
#include "ConVar.h"

HookedFuncStaticWithType<int(__fastcall*)(void*)> CRender_GetHitchMetrics("engine.dll", 0x9ECD0); // new
HookedFuncStaticWithType<__int64(__fastcall*)(uintptr_t)> CFPSPanel_Draw("client.dll", 0x28BEA0); // new
FuncStaticWithType<bool(__fastcall*)(void*)> sub_180071A30("engine.dll", 0x71A30); // new
//
FuncStaticWithType<void*(__cdecl*)()> get_cl("engine.dll", 0x5F4B0); // new


enum HitchFlags
{
	SERVER_HITCHED = 1 << 0, //1
	NET_CHOKED = 1 << 1, //2
	LARGE_SNAPSHOT = 1 << 2, //4
	OUT_OF_SNAPSHOTS = 1 << 3, //8
	// r2+:
	CLIENT_HITCHED = 1 << 4,//16 // we readd this
	//FULL_SNAPSHOT = 1 << 5,//32 // we don't readd this
	// our new:
	SERVER_PACKET_DROPPED = 1 << 6,//64
};

int CRender_GetHitchMetrics_Hook(void* cl)
{
	HitchFlags flags = static_cast<HitchFlags>(CRender_GetHitchMetrics(cl));
	static auto engine = MemoryAddress(Util::GetModuleBaseAddress("engine.dll"));
	static auto& cl__m_nSignonState = (reinterpret_cast<_DWORD*>(cl))[29];
	//bool cl_m_bPaused = false; // cl+220
	//static bool& host_initialized = engine.Offset(0x242FA06).GetValueRef<bool>();
	static auto lastTime = 0.0;
	auto newTime = Plat_FloatTime();
	auto diff = newTime - lastTime;
	// Apex first checks diff for >1/50, then does some more checks and then checks for >1/10
	// it doesn't make any sense, so we check for >1/10 right away...
	if (lastTime > 0.0 && diff > (1.0 / 10.0)
		&& cl__m_nSignonState == 8
		//&& !cl_m_bPaused && host_initialized
		&& !sub_180071A30(cl)
		&& !GetSystemMetrics(SM_REMOTESESSION)) [[unlikely]]
	{
		flags = (HitchFlags)(flags | CLIENT_HITCHED);
	}
	lastTime = newTime;

	extern bool g_droppedPacketFlag;
	if (g_droppedPacketFlag) [[unlikely]]
	{
		g_droppedPacketFlag = false;
		flags = (HitchFlags)(flags | SERVER_PACKET_DROPPED);
	}

	auto& hitch_log_to_console = SDK().GetVstdlibCvar()->FindVar("hitch_log_to_console")->GetIntRef();
	if (hitch_log_to_console)
	{
		if (flags & SERVER_HITCHED) spdlog::warn("SERVER HITCHED");
		if (flags & NET_CHOKED) spdlog::warn("NET CHOKED");
		if (flags & LARGE_SNAPSHOT) spdlog::warn("LARGE SNAPSHOT");
		if (flags & OUT_OF_SNAPSHOTS) spdlog::warn("OUT OF SNAPSHOTS");
		if (flags & CLIENT_HITCHED) spdlog::warn("CLIENT HITCHED");
		if (flags & SERVER_PACKET_DROPPED) spdlog::warn("SERVER PACKET DROPPED");
	}

	return flags;
}

void DrawHitchWarning(uintptr_t a1, int* pY, const char* text, bool cond, double* disappearTime)
{
	//static float& currentTime = SDK().GetClientGlobals()->curtime;
	double currentTime = Plat_FloatTime();
	if (cond)
		*disappearTime = currentTime + 3.0;

	if (*disappearTime > currentTime)
	{
		double flOpacity = 0.0;
		double flTargetOpacity = (*disappearTime - currentTime) / 3.0;
		if (flTargetOpacity > 0.0)
			flOpacity = fmin(1.0, flTargetOpacity);
		unsigned char r = 0xFFui8, g = 0xFFui8, b = 0ui8, a;
		a = 0xFFui8 * flOpacity;

		//static ConVarRef hitch_alert_huge_ref{ "hitch_alert_huge" };
		//static auto& hitch_alert_huge = hitch_alert_huge_ref->GetIntRef();
		//auto textStyle = hitch_alert_huge ? 16 : *(unsigned int*)(a1 + 604); // 5
		// 5 = default that's set on +620, 16 = bigger with underline,
		// 4, 11, 13, 17, 19=(smol, but better than 5), 23, 31=huge, 44=(like 31 but less bold), 47
		static ConVarRef hitch_alert_font_ref{ "hitch_alert_font" };
		static auto& hitch_alert_font = hitch_alert_font_ref->GetIntRef();
		auto textStyle = hitch_alert_font ? hitch_alert_font : *(unsigned int*)(a1 + 604); // 5

		static __int64& g_pMatSystemSurface = MemoryAddress(Util::GetModuleBaseAddress("client.dll")).Offset(0x380E728).GetValueRef<__int64>();
		static __int64& g_pVGuiSurface = MemoryAddress(Util::GetModuleBaseAddress("client.dll")).Offset(0x380E738).GetValueRef<__int64>();

		// g_pMatSystemSurface->DrawTextLen
		//auto textWidth = (*(__int64(__fastcall**)(__int64, _QWORD, const char*))(*(_QWORD*)g_pMatSystemSurface + 1400i64))(
		auto textWidth = (*(int(__fastcall**)(__int64, int, const char*, ...))(*(_QWORD*)g_pMatSystemSurface + 1400i64))(
			g_pMatSystemSurface,
			textStyle,//*(unsigned int*)(a1 + 604), // 5
			text);
		//auto screenWidth = 1920;
		static auto GetPanelSurfaceWidth_orsomething_sub_1806889C0 = (__int64(__fastcall*)(__int64))(Util::GetModuleBaseAddress("client.dll") + 0x6889C0);
		auto screenWidth = GetPanelSurfaceWidth_orsomething_sub_1806889C0(a1);
		auto x = (screenWidth - textWidth) / 2 + 1;

		// surface()->GetFontTall( font )
		//auto textHeight = (*(__int64(__fastcall**)(__int64, _QWORD))(*(_QWORD*)g_pVGuiSurface + 656i64))(
		auto textHeight = (*(int(__fastcall**)(__int64, int))(*(_QWORD*)g_pVGuiSurface + 656i64))(
			g_pVGuiSurface,
			textStyle);// *(unsigned int*)(a1 + 604));
		*pY += textHeight + 2;
		auto y = *pY;

		// g_pMatSystemSurface->DrawColoredText
		//(*(void(__fastcall**)(__int64, _QWORD, _QWORD, _QWORD, int, _DWORD, _DWORD, int, const char*))(*(_QWORD*)g_pMatSystemSurface + 1376i64))(
		(*(int(__fastcall**)(__int64, int, int, int, int, int, int, int, const char*, ...))(*(_QWORD*)g_pMatSystemSurface + 1376i64))(
			g_pMatSystemSurface,
			textStyle,//*(unsigned int*)(a1 + 604), // 5
			// height,
			x,
			y,
			r,
			g,
			b,
			a,
			text);
	}
}

void DrawHitchWarnings(uintptr_t a1)
{
	static HitchFlags& g_HitchFlags = (HitchFlags&)MemoryAddress(Util::GetModuleBaseAddress("materialsystem_dx11.dll")).Offset(0x382774).GetValueRef<unsigned int>();
	static double disappearTimes[10];
	auto y = 30;
	DrawHitchWarning(a1, &y, "SERVER HITCHED", g_HitchFlags & SERVER_HITCHED, &disappearTimes[0]);
	DrawHitchWarning(a1, &y, "NET CHOKED", g_HitchFlags & NET_CHOKED, &disappearTimes[1]);
	DrawHitchWarning(a1, &y, "LARGE SNAPSHOT", g_HitchFlags & LARGE_SNAPSHOT, &disappearTimes[2]);
	DrawHitchWarning(a1, &y, "OUT OF SNAPSHOTS", g_HitchFlags & OUT_OF_SNAPSHOTS, &disappearTimes[3]);
	DrawHitchWarning(a1, &y, "CLIENT HITCHED", g_HitchFlags & CLIENT_HITCHED, &disappearTimes[4]);
	//DrawHitchWarning(a1, &y, "FULL SNAPSHOT", g_HitchFlags & FULL_SNAPSHOT, &disappearTimes[5]);
	DrawHitchWarning(a1, &y, "SERVER PACKET DROPPED", g_HitchFlags & SERVER_PACKET_DROPPED, &disappearTimes[6]);
}

__int64 __fastcall CFPSPanel_Draw_Hook(uintptr_t a1)
{
	auto ret = CFPSPanel_Draw(a1);
	DrawHitchWarnings(a1);
	return ret;
}

void HitchAlert_Setup()
{
	CRender_GetHitchMetrics.Hook(CRender_GetHitchMetrics_Hook);
	CFPSPanel_Draw.Hook(CFPSPanel_Draw_Hook);
	//SDK().GetConCommandManager().RegisterConVar("hitch_alert_huge", "0", 0, "Use this if you're blind");
	SDK().GetConCommandManager().RegisterConVar("hitch_alert_font", "17", 0, "0 = use default");
	SDK().GetConCommandManager().RegisterConVar("hitch_log_to_console", "1", 0, "Log hitch warnings to console in addition to displaying them on screen");
}
