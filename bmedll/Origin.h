#pragma once

// TFOrigin start: engine.dll+2ECB770
/*class TFOrigin;
class curlWrapper;
class curlWrapper2_0x1000;*/

class curlWrapper
{
public:
	__int32 state; //0x0000 
	char pad_0x0004[0x4]; //0x0004
	char* data; //0x0008 
	__int32 datasize1; //0x0010 
	__int32 datasize2; //0x0014 
	__int32 N000007CC; //0x0018 
	__int32 responseCode; //0x001C 
	__int32 N000007CD; //0x0020 
	float time; //0x0024 
	char pad_0x0028[0x48]; //0x0028
	char url[1025]; //0x69E5E9C0 
	char pad_0x0471[0x1F]; //0x0471

}; //Size=0x0490

class curlWrapper2_0x1000
{
public:
	char pad_0x0000[0x1000]; //0x0000

}; //Size=0x1000

class TFOrigin
{
public:
	unsigned char isInitialized; //0x0000 
	unsigned char isOnline; //0x0001 
	unsigned char isOnlineCheckPending; //0x0002 
	unsigned char gotProfile; //0x0003 
	unsigned char N000007AC; //0x0004 
	unsigned char isRequestingAuthCode; //0x0005 
	unsigned char isAuthCodeFailed; //0x0006 
	unsigned char isRequestingPersistenceToken; //0x0007 
	unsigned char isRefreshingPersistenceToken; //0x0008 
	unsigned char isLoggedOut; //0x0009 
	unsigned char isEnvProduction; //0x000A 
	unsigned char didDisconnectAlready; //0x000B 
	__int32 errorCode; //0x000C 
	unsigned __int64 uid; //0x0010 
	char pad_0x0018[0x8]; //0x0018
	double authCodeReceivedTime; //0x0020 
	double requestTokenStartedTime; //0x0028 
	__int32 timeAfterTokenShouldBeRefreshed; //0x0030 
	char pad_0x0034[0x4]; //0x0034
	curlWrapper N0000000E; //0x0038 
	curlWrapper2_0x1000 N00000097; //0x04C8 
	char nucleusOauthServerTokenURI[1024]; //0x69E5E9C0 
	char pad_0x18C8[0x58]; //0x18C8
	curlWrapper N00000322; //0x1920 
	curlWrapper2_0x1000 N00000323; //0x1DB0 
	char oauthRefreshServerTokenURI[1024]; //0x69E5E9C0 
	char pad_0x31B0[0x58]; //0x31B0
	char authCode[256]; //0x69E5E9C0 
	char nucleusToken[1024]; //0x69E5E9C0 
	char playerName[64]; //0x69E5E9C0 
	char locale[64]; //0x69E5E9C0 
	char playerAvatar[260]; //0x69E5E9C0 
	char environment[64]; //0x69E5E9C0 
	unsigned char isPresenceUpdatePending; //0x38CC 
	unsigned char N00000FCB; //0x38CD 
	char presenceString[256]; //0x69E5E9C0 
	char presenceString2Unused[256]; //0x69E5E9C0 
	char presenceString3Unused[256]; //0x69E5E9C0 
	char pad_0x3BCE[0x2]; //0x3BCE

}; //Size=0x3BD0
