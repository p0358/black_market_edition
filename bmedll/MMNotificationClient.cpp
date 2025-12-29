#pragma once
#include <Mmdeviceapi.h>
#include <TTFSDK.h>

FuncStatic<void> Snd_Restart_DirectSound("engine.dll", 0x15AF0);
HookedFuncStatic<void> S_Init("engine.dll", 0xEA00);
HookedFuncStatic<void> S_Shutdown("engine.dll", 0x114B0);

class CDevicesManager;
class MMNotificationClient : public IMMNotificationClient
{
public:
	MMNotificationClient() {};
	virtual ~MMNotificationClient() {};
	ULONG STDMETHODCALLTYPE AddRef() { return 1; };
	ULONG STDMETHODCALLTYPE Release() { return 1; };
	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID riid, VOID** ppvInterface);
	HRESULT STDMETHODCALLTYPE OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDeviceId);
	HRESULT STDMETHODCALLTYPE OnDeviceAdded(LPCWSTR pwstrDeviceId) { return S_OK; };
	HRESULT STDMETHODCALLTYPE OnDeviceRemoved(LPCWSTR pwstrDeviceId) { return S_OK; };
	HRESULT STDMETHODCALLTYPE OnDeviceStateChanged(LPCWSTR pwstrDeviceId, DWORD dwNewState) { return S_OK; };
	HRESULT STDMETHODCALLTYPE OnPropertyValueChanged(LPCWSTR pwstrDeviceId, const PROPERTYKEY key) { return S_OK; };
};

HRESULT STDMETHODCALLTYPE MMNotificationClient::QueryInterface(REFIID riid, VOID** ppvInterface)
{
	if (IID_IUnknown == riid)
	{
		AddRef();
		*ppvInterface = (IUnknown*)this;
	}
	else if (__uuidof(IMMNotificationClient) == riid)
	{
		AddRef();
		*ppvInterface = (IMMNotificationClient*)this;
	}
	else
	{
		*ppvInterface = NULL;
		return E_NOINTERFACE;
	}
	return S_OK;
}

HRESULT STDMETHODCALLTYPE MMNotificationClient::OnDefaultDeviceChanged(EDataFlow flow, ERole role, LPCWSTR pwstrDeviceId)
{
	if (!IsSDKReady())
		return E_NOT_VALID_STATE;
	if (role == eMultimedia)
	{
		spdlog::info("[MMNotificationClient::OnDefaultDeviceChanged] Default multimedia audio device changed, requesting game's XAudio to restart.");
		int refresh_rate = *reinterpret_cast<int*>(Util::GetModuleBaseAddress("engine.dll") + 0x7CAEA4);
		SDK().AddDelayedFunc([] { if (IsSDKReady()) SDK().GetConCommandManager().ExecuteCommand("sound_reboot_xaudio"); }, refresh_rate);
	}
	return S_OK;
}

MMNotificationClient g_mmNotificationClient{};
IMMDeviceEnumerator* g_mmDeviceEnumerator = nullptr;

void Init_MMNotificationClient()
{
	HRESULT hr = CoCreateInstance(__uuidof(MMDeviceEnumerator), NULL, CLSCTX_ALL, __uuidof(IMMDeviceEnumerator), (void**)&g_mmDeviceEnumerator);
	if (SUCCEEDED(hr))
	{
		//spdlog::info("Registering MMNotificationClient");
		g_mmDeviceEnumerator->RegisterEndpointNotificationCallback(&g_mmNotificationClient);
	}
}

void Deinit_MMNotificationClient()
{
	if (g_mmDeviceEnumerator)
	{
		//spdlog::info("Unregistering MMNotificationClient");
		g_mmDeviceEnumerator->UnregisterEndpointNotificationCallback(&g_mmNotificationClient);
		g_mmDeviceEnumerator->Release();
		g_mmDeviceEnumerator = nullptr;
	}
}

void ConCommand_sound_reboot_xaudio(const CCommand& args)
{
	spdlog::debug("Restarting XAudio...");
	Snd_Restart_DirectSound();
	spdlog::debug("Restarted XAudio...");
	spdlog::debug("Note: sometimes this doesn't seem to work but oh well...");
}

void S_Init_Hook()
{
	S_Init();
	bool g_bNoSound = *reinterpret_cast<bool*>(Util::GetModuleBaseAddress("engine.dll") + 0x20144E4);
	if (!g_bNoSound)
		Init_MMNotificationClient();
}

void S_Shutdown_Hook()
{
	S_Shutdown();
	bool g_bNoSound = *reinterpret_cast<bool*>(Util::GetModuleBaseAddress("engine.dll") + 0x20144E4);
	if (!g_bNoSound)
		Deinit_MMNotificationClient();
}

void Setup_MMNotificationClient()
{
	S_Init.Hook(S_Init_Hook);
	S_Shutdown.Hook(S_Shutdown_Hook);
}
