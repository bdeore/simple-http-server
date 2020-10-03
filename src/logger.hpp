#ifndef _LOGGER_H_
#define _LOGGER_H_

#include <iostream>
#include <map>
#include <string>
#include <mutex>

class logger {
 public:
  void write(std::string file_name, std::string client_ip, unsigned short port_number);
};

#endif
