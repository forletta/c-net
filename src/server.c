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

    const char *response = "HTTP/1.0 200 OK\r\n\r\nHello There!";

    char recv_buf[BUFFER_SIZE];
    int bytes_read;

    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("failed to create socket");
        exit(EXIT_FAILURE);
    }

    bzero(&server_addr, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(8080);

    if (bind(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) <
        0) {
        perror("failed to bind to socket");
        exit(EXIT_FAILURE);
    }

    if (listen(socket_fd, 10) < 0) {
        perror("failed to connect to socket");
        exit(EXIT_FAILURE);
    }

    while (1) {
        int conn_fd = accept(socket_fd, NULL, NULL);

        memset(recv_buf, 0, sizeof(recv_buf));

        while ((bytes_read = read(conn_fd, recv_buf, sizeof(recv_buf))) > 0) {
            printf("%s", recv_buf);

            if (recv_buf[bytes_read - 1] == '\n') {
                break;
            }

            memset(recv_buf, 0, sizeof(recv_buf));
        }

        if (bytes_read < 0) {
            perror("failed to read from socket");
            exit(EXIT_FAILURE);
        }

        write(conn_fd, response, strlen(response));
        close(conn_fd);
    }

    close(socket_fd);

    return 0;
}
