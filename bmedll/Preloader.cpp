#include "Util.h"
#include "tier0.h"

size_t writeFunction(void* ptr, size_t size, size_t nmemb, std::string* data)
{
    data->append((char*)ptr, size * nmemb);
    return size * nmemb;
}

//char __fastcall loadPlaylists_sub_180160B30(__int64 a1)
typedef char(__fastcall* LOADPLAYLISTSFN) (const char* a1);
DWORD WINAPI precachePlaylists(PVOID pThreadParameter)
{
    auto enginedllBaseAddress = Util::GetModuleBaseAddress("engine.dll");
    auto logger = spdlog::get("logger");
    //MessageBoxA(0, "hey2", "hey", 0);

    __int64* something_related_to_playlists_ptr = (__int64*)(enginedllBaseAddress + 0x2ED7708);
    //*((unsigned char*)ptr) = 0xEB;
    if (*something_related_to_playlists_ptr) return 0; // playlists are already loaded

    auto curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://r1-pc.s3.amazonaws.com/playlists.txt");
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, ""); // automatically uses all built-in supported encodings
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        //curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L);

        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, _("Respawn HTTPS/1.0"));
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        CURLcode res = curl_easy_perform(curl);

        long response_code;
        //double elapsed;
        //char* url;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        //curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        //curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

        curl_easy_cleanup(curl);
        curl = NULL;

        if (*something_related_to_playlists_ptr) return 0; // playlists are already loaded

        if (response_code == 200)
        {
            //std::stringstream ss;
            //ss << "Resp code: " << response_code << "\nLen: " << response_string.length();
            //MessageBoxA(0, ss.str().c_str(), "Gonna load playlists", 0);
            LOADPLAYLISTSFN loadPlaylists = (LOADPLAYLISTSFN)(enginedllBaseAddress + 0x160B30);
            if (response_string.length() < 300000)
            {
                memcpy((void*)(enginedllBaseAddress + 0x221CF50), response_string.c_str(), response_string.length());
                loadPlaylists((const char*)(enginedllBaseAddress + 0x221CF50));
            }
            else
            {
                loadPlaylists(response_string.c_str());
            }
            //MessageBoxA(0, ss.str().c_str(), "Loaded playlists", 0);
            SPDLOG_LOGGER_DEBUG(logger, _("[Preloader] Preloaded playlists"));
        }
        else
        {
            if (res != CURLE_OK)
                spdlog::error("[Preloader] curl_easy_perform() failed for playlists: {}", curl_easy_strerror(res));
            else
                spdlog::error("[Preloader] Unexpected response code for playlists (expected 200): {}", response_code);
        }
    }

    return 0;
}

//__int64 __fastcall sub_18042AD30(__int64 a1, unsigned int *a2, __int64 a3, int a4, int a5, unsigned int a6)
typedef __int64(__fastcall* SUBD30FN) (__int64 a1, unsigned int* a2, __int64 a3, int a4, int a5, unsigned int a6);

//char __fastcall sub_180217C30(__int64 a1, __int64 a2, _QWORD *a3, __int64 a4)
typedef char(__fastcall* SUBC30FN) (__int64 a1, __int64 a2, unsigned __int64* a3, __int64 a4);

DWORD WINAPI precachePdef(PVOID pThreadParameter)
{
    //MessageBoxA(0, "hey2", "hey", 0);
    auto enginedllBaseAddress = Util::GetModuleBaseAddress("engine.dll");
    auto logger = spdlog::get("logger");

    __int64* isPdefLoaded_ptr = (__int64*)(enginedllBaseAddress + 0x310D1F0); // is set to 0 on disconnect for some reason
    __int64* persistencePdefVersion_ptr = (__int64*)(enginedllBaseAddress + 0x3116340);
    if (*persistencePdefVersion_ptr) return 0; // already loaded

    auto curl = curl_easy_init();

    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, "https://titanfall.p0358.net/pdef.bz2");
        curl_easy_setopt(curl, CURLOPT_ACCEPT_ENCODING, ""); // automatically uses all built-in supported encodings
        curl_easy_setopt(curl, CURLOPT_HTTP_VERSION, CURL_HTTP_VERSION_2_0);
        curl_easy_setopt(curl, CURLOPT_NOPROGRESS, 1L);
        //curl_easy_setopt(curl, CURLOPT_TCP_KEEPALIVE, 0L);

        std::string response_string;
        std::string header_string;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
        curl_easy_setopt(curl, CURLOPT_HEADERDATA, &header_string);

        CURLcode res = curl_easy_perform(curl);

        long response_code;
        //double elapsed;
        //char* url;
        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &response_code);
        //curl_easy_getinfo(curl, CURLINFO_TOTAL_TIME, &elapsed);
        //curl_easy_getinfo(curl, CURLINFO_EFFECTIVE_URL, &url);

        curl_easy_cleanup(curl);
        curl = NULL;

        if (*persistencePdefVersion_ptr) return 0; // already loaded

        if (response_code == 200)
        {
            //std::stringstream ss;
            //ss << "Resp code: " << response_code << "\nLen: " << response_string.length();
            //MessageBoxA(0, ss.str().c_str(), "Gonna load pdef", 0);

            if (response_string.length() > 0xD000) return 0; // too big!

            //LOADPLAYLISTSFN loadPlaylists = (LOADPLAYLISTSFN)(enginedllBaseAddress + 0x160B30);
            memcpy((void*)(enginedllBaseAddress + 0x30F31E0), response_string.c_str(), response_string.length());
            __int64* pdef_buf_len_ptr = (__int64*)(enginedllBaseAddress + 0x310D1F8);
            *pdef_buf_len_ptr = response_string.length();
            //loadPlaylists((const char*)(enginedllBaseAddress + 0x221CF50));

            char decompressedBuf[0xD000];
            unsigned int decompressedLen = 0xD000;

            SUBD30FN sub_18042AD30 = (SUBD30FN)(enginedllBaseAddress + 0x42AD30);
            unsigned int bzresult = sub_18042AD30((__int64)&decompressedBuf, &decompressedLen, (__int64)(enginedllBaseAddress + 0x30F31E0), response_string.length(), 1, 0);

            if ((bzresult & 0x80000000) != 0)
            {
#if SHOW_PRECACHE_ERRORS
                std::stringstream ss2; ss2 << "BZ2 error " << bzresult << " decompressing pdef source from server";
                MessageBoxA(0, ss2.str().c_str(), "Error", 0);
#endif
                logger->error("[Preloader] BZ2 error {} decompressing pdef source from server", bzresult);
                return 0;
            }

            SUBC30FN sub_180217C30 = (SUBC30FN)(enginedllBaseAddress + 0x217C30);

            if (!sub_180217C30((__int64)&decompressedBuf, decompressedLen, (unsigned __int64*)(enginedllBaseAddress + 0x310D2B0), 299))
            {
#if SHOW_PRECACHE_ERRORS
                MessageBoxA(0, "Error parsing persistent data definition file received from server.", "Error", 0);
#endif
                logger->error("[Preloader] Error parsing persistent data definition file received from server.");
                return 0;
            }

            //*isPdefLoaded_ptr = 1; // not sure if we should set this, it's also set to 1 if we're using processusecached...
            //ss << "\nDecompressed length: " << decompressedLen; MessageBoxA(0, ss.str().c_str(), "Loaded pdef", 0);
            SPDLOG_LOGGER_DEBUG(logger, "[Preloader] Preloaded pdef, decompressed length: {}", decompressedLen);
        }
        else
        {
            if (res != CURLE_OK)
                spdlog::error("[Preloader] curl_easy_perform() failed for pdef: {}", curl_easy_strerror(res));
            else
                spdlog::error("[Preloader] Unexpected response code for pdef (expected 200): {}", response_code);
        }
    }

    return 0;
}

void StartPreloading()
{
    if (!CommandLine()->CheckParm("-nopreload"))
    {
        CreateThread(0, 0, precachePlaylists, 0, 0, NULL);
        CreateThread(0, 0, precachePdef, 0, 0, NULL);
    }
}
