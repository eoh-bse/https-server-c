#include <arpa/inet.h>
#include <bits/sockaddr.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>

#include "modules/common.h"
#include "modules/errors.h"
#include "modules/server.h"

typedef struct sockaddr sockaddr;

int run_server(void) {
  int socketfd = socket(AF_INET, SOCK_STREAM, 0);
  if (socketfd == ERROR) {
    handle_error(SOCKET_FAILURE);
    return ERROR;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(DEFAULT_PORT);
  server_addr.sin_addr.s_addr = htonl(INADDR_ANY);

  if (bind(socketfd, (sockaddr *)&server_addr, sizeof(server_addr)) == ERROR) {
    handle_error(BIND_FAILURE);
    return ERROR;
  }

  if (listen(socketfd, MAX_PENDING) == ERROR) {
    handle_error(LISTEN_FAILURE);
    return ERROR;
  }

  fprintf(stdout, "Listening on port %d\n", DEFAULT_PORT);

  struct sockaddr_in req_addr;
  socklen_t req_len;
  char *request = malloc(MAX_REQ_SIZE + 1);
  while (1) {
    memset(request, 0, MAX_REQ_SIZE);
    memset(&req_addr, 0, sizeof(req_addr));
    req_len = 0;

    int requestfd = accept(socketfd, (sockaddr *)&req_addr, &req_len);
    if (requestfd == ERROR) {
      handle_error(ACCEPT_FAILURE);
      continue;
    }

    fprintf(stdout, "Length: %d\n, Address: %d\n Port: %d\n", req_len,
            ntohl(req_addr.sin_addr.s_addr), ntohs(req_addr.sin_port));

    if (read(requestfd, request, MAX_REQ_SIZE) == ERROR) {
      handle_error(REQUEST_FAILURE);
      continue;
    }

    fprintf(stdout, "%s\n", request);
    char *response = "HTTP/1.1 200 OK\r\n\r\nHello World!\n";
    write(requestfd, response, strlen(response));
    close(requestfd);
  }

  free(request);
  close(socketfd);

  return OK;
}
