#include "server.h"
#include "logger.h"

int main() {
  Server cs557;
  Logger logger;

  cs557.initialize_server();
  cs557.run_server();

  return 0;
}

Server::Server() {
  socket_fd = 0;
  new_socket = 0;

  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = INADDR_ANY;
  server_address.sin_port = 0;
}

void Server::initialize_server() {
  socket_fd = socket(AF_INET, SOCK_STREAM, 0);
  int option = 1;

  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
  setsockopt(socket_fd, SOL_SOCKET, SO_REUSEPORT, &option, sizeof(option));

  if (bind(socket_fd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
    exit(EXIT_FAILURE);
  }

  s_len = sizeof(server_address);
  if (getsockname(socket_fd, (struct sockaddr *) &server_address, (socklen_t *) &s_len) < 0) {
    exit(EXIT_FAILURE);
  }

  std::cout << "\n ------------------------------------------------\n"
            << "   CS557_Server => listening on port [ "
            << ntohs(server_address.sin_port) << " ]\n"
            << " ------------------------------------------------\n" << std::endl;
}

void Server::run_server() {
  while (1) {
    if (listen(socket_fd, 5) < 0) {
      exit(EXIT_FAILURE);
    }

    c_len = sizeof(client_address);
    if ((new_socket = accept(socket_fd, (struct sockaddr *) &client_address, (socklen_t *) &c_len)) < 0) {
      exit(EXIT_FAILURE);
    }

    printf("connection from host:[ %s ] on port:[ %d ]\n", inet_ntoa(client_address.sin_addr),
           ntohs(client_address.sin_port));

    send(new_socket, "hello there", strlen("hello there"), 0);
    close(new_socket);
  }
}

Server::~Server() {
  close(new_socket);
  close(socket_fd);
  std::cout << "shutting down server..." << std::endl;
  exit(0);
}

