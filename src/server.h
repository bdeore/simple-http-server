#ifndef _SERVER_H_
#define _SERVER_H_

#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include "response.h"

class Server {
 public:
  int socket_fd, new_socket;
  socklen_t c_len, s_len;
  struct sockaddr_in server_address, client_address;

  Server();
  ~Server();
  void initialize_server();
  void run_server();
  char *generate_headers();
};

#endif
