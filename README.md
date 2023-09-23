# CMicroWeb
Single header micro web framework in C with templating support

Based on https://github.com/jeremycw/httpserver.h

# Example

```c
#define HTTPSERVER_IMPL
#include "cmicroweb.h"

struct http_response_s* hello_world() {
    struct http_response_s* response = http_response_init();
    http_response_status(response, 200);
    http_response_header(response, "Content-Type", "text/html");
    char *text = "Hello, World!";
    http_response_body(response, text, strlen(text));
    return response;
}

void handle_request(struct http_request_s* request) {
    char *url = http_request_path(request);

    struct http_response_s* response;
    if (strcmp(url, "/") == 0) {
        response = hello_world();
    } else {
        response = http_quick_response(404, "404 not found!");
    }

    http_respond(request, response);
}

int main() {
    struct http_server_s* server = http_server_init(8080, handle_request);
    http_server_listen(server);
}
```

See the `example` directory for more examples.

## Warning
NOT production ready.

Bodged together in a afternoon.

I don't even know what most of the code in the `httpserver.h` file does.
