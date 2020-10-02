#ifndef _SERVER_H_
#define _SERVER_H_

#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>

class Server {
 public:
  int socket_fd, new_socket;
  socklen_t c_len, s_len;
  struct sockaddr_in server_address, client_address;

  Server();
  ~Server();
  void initialize_server();
  void run_server();
};

#endif
