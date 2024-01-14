#include <iostream>  
#include <windows.h>  
#include <wininet.h>  
#include <fstream>  
#pragma comment(lib, "wininet.lib")  
bool DownloadFile(const std::wstring& url, const std::wstring& outputPath) {
    HINTERNET hInternet = InternetOpen(L"MyDownloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    if (!hInternet) {std::wcerr << L"InternetOpen failed: " << GetLastError() << std::endl; return false;}
    HINTERNET hConnect = InternetOpenUrl(hInternet, url.c_str(), NULL, 0, INTERNET_FLAG_RELOAD, 0);
    if (!hConnect) {std::wcerr << L"InternetOpenUrl failed: " << GetLastError() << std::endl; InternetCloseHandle(hInternet); return false;}
    char buffer[4096];
    DWORD dwRead;
    std::ofstream outputFile(outputPath, std::ios::binary);
    do {
        if(!InternetReadFile(hConnect, buffer, sizeof(buffer), &dwRead)){std::wcerr << L"InternetReadFile failed: " << GetLastError() << std::endl; InternetCloseHandle(hConnect); InternetCloseHandle(hInternet); return false;}
        if(dwRead > 0) {outputFile.write(buffer, dwRead);}} while (dwRead > 0);
    outputFile.close();
    InternetCloseHandle(hConnect);
    InternetCloseHandle(hInternet);
    return true;}
int main() {
    std::wstring url = L"";//下载链接
    std::wstring outputPath = L""; //输出目录
    if(DownloadFile(url,outputPath)){std::wcout << L"File downloaded successfully." << std::endl;}
    else{std::wcout << L"File download failed." << std::endl;}
    return 0;}
