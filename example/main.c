#define HTTPSERVER_IMPL
#include "../httpserver.h"

/* TEMPLATES */
char **base_template;
char **index_template;
char **foo_template;

void initialize_templates() {
    base_template = template_new("./templates/base.html");
    index_template = template_new("./templates/index.html");
    foo_template = template_new("./templates/foo.html");
}

struct http_response_s* root() {
    struct http_response_s* response = http_response_init();
    http_response_status(response, 200);
    http_response_header(response, "Content-Type", "text/html");
    char *context[] = {"<style>body{background-color: gray;}</style>", index_template[0], NULL};
    char *text = template_render(base_template, context);
    http_response_body(response, text, strlen(text));
    return response;
}

struct http_response_s* foo() {
    struct http_response_s* response = http_response_init();
    http_response_status(response, 200);
    http_response_header(response, "Content-Type", "text/html");
    char *context[] = {"<style>body{background-color: red;}</style>", foo_template[0], NULL};
    char *text = template_render(base_template, context);
    http_response_body(response, text, strlen(text));
    return response;
}

void handle_request(struct http_request_s* request) {
    char *url = http_request_path(request);

    struct http_response_s* response;
    if (strcmp(url, "/") == 0) {
        response = root();
    } else if (strcmp(url, "/foo") == 0) {
        response = foo();
    } else {
        response = http_quick_response(404, "404 not found!");
    }

    http_respond(request, response);
}

int main() {
    initialize_templates();
    struct http_server_s* server = http_server_init(8080, handle_request);
    http_server_listen(server);
}
