#include "server.h"
#include "response.h"
#include "logger.h"
#include <vector>

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
  char buffer[1024] = {0};

  std::string file_name = "syllabus.pdf";
  response::header_response(file_name);
  while (1) {
    if (listen(socket_fd, 5) < 0) {
      exit(EXIT_FAILURE);
    }

    c_len = sizeof(client_address);
    if ((new_socket = accept(socket_fd, (struct sockaddr *) &client_address, (socklen_t *) &c_len)) < 0) {
      exit(EXIT_FAILURE);
    }

    printf("connection from host:[ %s ] + port:[ %d ]\n", inet_ntoa(client_address.sin_addr),
           ntohs(client_address.sin_port));

    char *test = "HTTP/1.1 200 OK";
    //send(new_socket, test, 1200, 0);
    read(new_socket, buffer, 1024);
    send(new_socket, test, strlen(test), 0);
    close(new_socket);
  }
}

char *Server::generate_headers() {
  //std::vector<char> response{"HTTP/1.0 200 OK\n\n", "there"};
  //return response[0] + response[1];
  char *response = "HTTP/1.0 \\r\\n200 OK\\r\\n\\r\\n";
  return response;
}

Server::~Server() {
  close(new_socket);
  close(socket_fd);
  std::cout << "shutting down server..." << std::endl;
  exit(0);
}

