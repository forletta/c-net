#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    int socket_fd;
    struct sockaddr_in server_addr;

    const char *get_request = "GET / HTTP/1.1\r\n\r\n";

    char recv_buf[BUFFER_SIZE];
    int bytes_read;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <address>", argv[0]);
        exit(EXIT_FAILURE);
    }

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(80);

    if (inet_pton(AF_INET, argv[1], &server_addr.sin_addr) <= 0) {
        perror("failed to parse address");
        exit(EXIT_FAILURE);
    }

    if (connect(socket_fd, (struct sockaddr *)&server_addr,
                sizeof(server_addr)) != 0) {
        perror("failed to connect to socket");
        exit(EXIT_FAILURE);
    }

    if (write(socket_fd, get_request, strlen(get_request)) !=
        strlen(get_request)) {
        perror("failed to write to socket");
        exit(EXIT_FAILURE);
    }

    bzero(recv_buf, sizeof(recv_buf));

    while ((bytes_read = read(socket_fd, recv_buf, sizeof(recv_buf) - 1)) > 0) {
        printf("%s", recv_buf);
    }

    if (bytes_read < 0) {
        perror("failed to read from socket");
        exit(EXIT_FAILURE);
    }

    close(socket_fd);

    return 0;
}
