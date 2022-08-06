#include "pch.h"
#include <stdio.h>
#include <curl/curl.h>
#include <filesystem>
#include "Globals.h"
namespace fs = std::filesystem;
using namespace System;
#pragma comment (lib, "user32.lib")

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

void downloadFile(std::string theURL) {
    CURL* curl;
    FILE* fp;
    CURLcode res;
    const char* url = theURL.c_str();

    std::stringstream test(theURL);
    std::string segment;
    std::vector<std::string> seglist;
    while (std::getline(test, segment, '/'))
    {
        seglist.push_back(segment);
    }

    fs::create_directories(seglist[2]);
    curl = curl_easy_init();
    if (curl) {
        fp = fopen((seglist[2] + "/" + seglist.rbegin()[0]).c_str(), "wb");
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
        res = curl_easy_perform(curl);
        /* always cleanup */
        curl_easy_cleanup(curl);
        fclose(fp);
    }
}

int main(array<System::String ^> ^args)
{
    return 0;
}