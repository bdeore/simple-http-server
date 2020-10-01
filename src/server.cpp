#include "server.h"
#include "logger.h"
#include <iostream>

int main() {
  std::cout << "Hello, World!" << std::endl;
  Server server;
  Logger logger;
  return 0;
}

Server::Server() {
 std::cout << "inside server constructor" << std::endl;
}

Server::~Server() {
  std::cout << "inside server destructor" << std::endl;
}

void Server::initialize_server() {

}

