#include "response.hpp"

std::string response::header_response(const std::string &file_name) {
  response res;
  std::string response;
  res.status = res.get_status(file_name);

  if (res.status == "200 OK") {
    res.server_name = get_server_name();
    res.date = get_date();
    res.last_modified = get_last_modified(file_name);
    res.content_length = res.get_content_length(file_name);
    res.content_type = get_content_type(file_name);

    response = "HTTP/1.1 " + res.status + "\n" + "Date: " + res.date + "\n" + "Server: " + res.server_name
        + "\n" + "Last-Modified: " + res.last_modified + "\n" + "Content-Length: " + res.content_length + "\n" +
        "Content-Type: " + res.content_type + "\n\n";
  } else {
    response = "HTTP/1.1 " + res.status + "\n" + "Date: " + res.date + "\n" + "Server: " + res.server_name
        + "\n\n";
  }

  return response;
}

std::string response::get_status(std::string file_name) {
  file_name = "www/" + file_name;
  std::ifstream exists(file_name.c_str());
  if (exists.good() && file_name != "www/") return "200 OK"; else return "404 NOT FOUND";
}

std::string response::get_date() {
  char formatted_time[256];
  std::time_t date_time = std::time(0);
  strftime(formatted_time, sizeof(formatted_time), "%a, %d %b %Y %H:%M:%S GMT", std::gmtime(&date_time));

  return std::string(formatted_time);
}

std::string response::get_server_name() {
  return "CS557_Server";
}

std::string response::get_last_modified(std::string file_name) {
  char formatted_time[256];
  file_name = "www/" + file_name;
  std::filesystem::path path = std::filesystem::current_path() / file_name;
  auto last_modified = std::filesystem::last_write_time(path);
  std::time_t last_modified_t = decltype(last_modified)::clock::to_time_t(last_modified);
  strftime(formatted_time, sizeof(formatted_time), "%a, %d %b %Y %H:%M:%S GMT", std::gmtime(&last_modified_t));

  return std::string(formatted_time);
}

std::string response::get_content_length(std::string file_name) {
  if (response::get_status(file_name) == "200 OK") {
    file_name = "www/" + file_name;
    std::filesystem::path path = std::filesystem::current_path() / file_name;
    return std::to_string(std::filesystem::file_size(path));
  }

  return "0";
}

std::string response::get_content_type(const std::string &file_name) {
  char file_arr[file_name.size()];
  std::string extension;
  std::strcpy(file_arr, file_name.c_str());
  char *current_token, *string_left = file_arr;
  current_token = strtok_r(string_left, ".", &string_left);

  while (current_token) {
    extension = std::string(current_token);
    current_token = strtok_r(string_left, ".", &string_left);
  }

  return server::check_mime_type(extension);
}