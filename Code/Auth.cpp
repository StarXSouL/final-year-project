#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Winmm.lib")
#pragma comment (lib, "Normaliz.lib")
#pragma comment (lib, "Wldap32.lib")
#pragma comment (lib, "advapi32.lib")
#pragma comment (lib, "crypt32.lib")
#define CURL_STATICLIB
#include "curl/curl.h"
#pragma comment (lib, "curl/libcurl_a.lib")
#include <windows.h>
#include <Lmcons.h>

namespace Big
{
	std::string playerUsername;
	std::string playerPassword;

	static size_t my_write(void* buffer, size_t size, size_t nmemb, void* param)
	{
		std::string& text = *static_cast<std::string*>(param);
		size_t totalsize = size * nmemb;
		text.append(static_cast<char*>(buffer), totalsize);
		return totalsize;
	}

	std::string ReadStringFromIni(std::string file, std::string app, std::string key)
	{
		char buf[100];
		GetPrivateProfileStringA(app.c_str(), key.c_str(), "NULL", buf, 100, file.c_str());
		return (std::string)buf;
	}

	uintptr_t m_bytes;

	uintptr_t GetTotalPhysicalMemory()
	{
		MEMORYSTATUSEX status;
		status.dwLength = sizeof(status);
		GlobalMemoryStatusEx(&status);
		m_bytes = status.ullTotalPhys;;
		return m_bytes;
	}

	void auth()
	{
		std::string_view log_path{ "C:\\OverKill\\Log.json" };
		std::ifstream f(log_path.data());
		nlohmann::json js_resp = nlohmann::json::parse(f);
		std::string kkkk = js_resp["lskey"];
		std::string API = "https://lenox.papayahosting.com/api/v7/auth?lskey=" + kkkk;

		CURL* curl;
		CURLcode cCode;
		std::string readBuffer;

		curl = curl_easy_init();

		if (curl)
		{
			curl_easy_setopt(curl, CURLOPT_URL, API.c_str());
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
			curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, my_write);
			curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
			cCode = curl_easy_perform(curl);
			curl_easy_cleanup(curl);

			js_resp = nlohmann::json::parse(readBuffer);
			if (js_resp["Auth"])
			{
				g_authed = true;
				//big::auth_key = js_resp["Message"];
			}
			else
			{
				//std::cout << js_resp["Message"];
				g_Logger->Info(readBuffer.c_str());
				//system("pause > nul");
				exit(0);
			}
		}
		else
		{
			//std::cout << "Curl Failed to initialize\n";
			g_Logger->Info(readBuffer.c_str());
			g_Logger->Info("Falied!");

			//system("pause > nul");
			exit(0);
		}

	}
}