#include "response.h"
#include <filesystem>

char *response::header_response(std::string &file_name) {
  response response;

  response.status = response.get_status(file_name);
  response.server_name = get_server_name();
  response.last_modified = get_last_modified(file_name);

  std::cout << response.status << std::endl;
  std::cout << response.last_modified << std::endl;
}

std::string response::get_status(std::string file_name) {
  file_name = "../www/" + file_name;
  std::ifstream exists(file_name.c_str());
  if (exists.good()) return "200 OK"; else return "404";
}

std::string &response::get_date() {

}

std::string response::get_server_name() {
  return "CS557_Server";
}

std::string response::get_last_modified(std::string file_name) {
  char formatted_time[256];
  file_name = "www/" + file_name;
  std::filesystem::path p = std::filesystem::current_path() / file_name;
  auto last_modified = std::filesystem::last_write_time(p);
  std::time_t last_modified_t = decltype(last_modified)::clock::to_time_t(last_modified);
  strftime(formatted_time, sizeof(formatted_time), "%a, %d %b %Y %H:%M:%S GMT", std::gmtime(&last_modified_t));

  return std::string(formatted_time);
}

std::string &response::get_content_type() {

}

std::string &response::get_content_length() {

}
