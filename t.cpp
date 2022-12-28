#include <iostream>
#include <cstring>
#include <curl/curl.h>
#include <typeinfo>


int main() {
    char url[100];
    std::cout << "What's your Mastodon instance's URL? " << std::endl;
    std::cin >> url;
    /*
     curl -X POST \
    -F 'client_name=Mastopo' \
    -F 'redirect_uris=urn:ietf:wg:oauth:2.0:oob' \
    -F 'scopes=read write push' \
    -F 'website=https://zev.averba.ch/learning_cpp/1' \
    https://recurse.social/api/v1/apps
    */
    // TODO: trim the input
    // TODO: add the https:// if it's not included
    std::cout << "Okay, I got " << url << std::endl;
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();

    curl_global_init(CURL_GLOBAL_ALL);
    strcat(url, "/api/v1/apps");
    std::cout << "type of url: " << typeid(url).name() << '\n';
    std::cout << "url: " << url << '\n';

    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(
        curl, 
        CURLOPT_POSTFIELDS, 
        "client_name=Mastopo&redirect_uris=urn:ietf:wg:oauth:2.0:oob&scopes=read%20write%20push&website=https://zev.averba.ch/learning_cpp/1"
    );
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
    curl_easy_perform(curl);

    if (res != CURLE_OK) {
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    std::cout << "readBuffer: " << readBuffer << std::endl;


    return 0;
}
