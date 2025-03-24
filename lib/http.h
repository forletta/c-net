#ifndef HTTP_H
#define HTTP_H

#include <sys/types.h>

typedef enum HttpMethod {
    GET,
    POST,
} http_method_t;

static const char *http_method_t_strs[2] = {
    "GET",
    "POST",
};

typedef struct HttpRequest {
    http_method_t method;
    const char *path;
} http_request_t;

ssize_t http_format_request(http_request_t *request, void *buf,
                           size_t bufc);

#endif
