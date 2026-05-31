#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>

// Automated Intelligence: Headers ko analyze karne wala function
void analyze_security(char *header_data) {
    printf("\n--- Automated Intelligence Analysis ---\n");
    
    // Check for XSS Protection
    if (header_data != NULL && strstr(header_data, "x-xss-protection: 0") != NULL) {
        printf("[!] VULNERABILITY: XSS Protection is DISABLED (Risk High)\n");
    } else {
        printf("[+] Security: XSS Protection appears active or not reported.\n");
    }

    // Check for Frame Options
    if (header_data != NULL && strstr(header_data, "x-frame-options") == NULL) {
        printf("[!] VULNERABILITY: Missing Clickjacking protection!\n");
    } else {
        printf("[+] Security: Clickjacking protection (X-Frame-Options) detected.\n");
    }
}

// Write callback function headers ko store karne ke liye
size_t write_data(void *ptr, size_t size, size_t nmemb, char *data) {
    strncat(data, (char *)ptr, size * nmemb);
    return size * nmemb;
}

void evolve_vision(char *target_url) {
    CURL *curl;
    CURLcode res;
    char header_buffer[4096] = {0}; // Buffer jahan headers store honge

    curl = curl_easy_init();
    if(curl) {
        printf("[+] Evolving: Fetching headers for %s...\n", target_url);
        
        curl_easy_setopt(curl, CURLOPT_URL, target_url);
        curl_easy_setopt(curl, CURLOPT_HEADER, 1);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, header_buffer);
        
        res = curl_easy_perform(curl);
        
        if(res == CURLE_OK) {
            printf("%s\n", header_buffer); // Headers print karo
            analyze_security(header_buffer); // Yahan intelligence trigger hogi
        } else {
            fprintf(stderr, "[!] Evolve Error: %s\n", curl_easy_strerror(res));
        }

        curl_easy_cleanup(curl);
    }
}

int main() {
    printf("--- Swayambhu Ghost Core Initialized ---\n");
    evolve_vision("https://google.com");
    printf("\n--- Ghost Evolution Cycle Complete ---\n");
    return 0;
}
