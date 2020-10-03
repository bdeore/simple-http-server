#ifndef _RESPONSE_H_
#define _RESPONSE_H_

#include <string>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>

class response {
 private:
  std::string status;
  std::string date;
  std::string server_name;
  std::string last_modified;
  std::string content_type;
  std::string content_length;

  std::string get_status(std::string file_name);
  std::string &get_date();
  static std::string get_server_name();
  static std::string get_last_modified(std::string file_name);
  std::string &get_content_type();
  std::string &get_content_length();

 public:
  static char *header_response(std::string &file_name);
};

#endif
