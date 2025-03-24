#include "http.h"
#include <stdio.h>
#include <string.h>

ssize_t http_format_request(http_request_t *request, void *buf, size_t bufc) {
    const char *version = "HTTP/1.1";
    const char *method = http_method_t_strs[request->method];

    size_t methodc = strlen(method);

    // +5 from 2 spaces, \r, \n, and \0
    size_t size_needed = methodc + strlen(request->path) + strlen(version) + 5;

    if (size_needed > bufc)
        return -1;

    return sprintf(buf, "%s %s %s\r\n", method, request->path, version);
}

int main() {
    const char *path = "/";

    http_request_t request = {
        .method = GET,
        .path = path,
    };

    char str[40] = "";

    http_format_request(&request, str, 40);

    printf("%s\n", str);

    return 0;
}
