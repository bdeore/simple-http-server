#ifndef _SERVER_H_
#define _SERVER_H_

#include <iostream>
#include <unistd.h>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <cstring>
#include <map>
#include <thread>
#include <vector>

#include "response.hpp"

class server {
 public:
  int socket_fd, new_socket;
  socklen_t c_len, s_len;
  struct sockaddr_in server_address, client_address;

  server();
  ~server();
  int initialize_server();
  //void run_server(int);
  void send_data(std::string file_name, int socket);
  static std::string check_mime_type(std::string);
  std::string request_parser(char buffer[]);
  void create_map();
};

#endif
