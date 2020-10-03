#include "logger.hpp"
std::map<std::string, int> logs;
std::map<std::string, int>::iterator it;

void logger::write(std::string file_name, std::string client_ip, unsigned short port_number) {
  std::mutex mx;

  mx.lock();

  it = logs.find(file_name);
  if (it == logs.end()) {
    logs.insert(std::pair<std::string, int>(file_name, 1));
    printf("    /%s | %s | %d | 1", file_name.c_str(), client_ip.c_str(), port_number);
    std::cout << std::endl;
  } else {
    it->second += 1;
    printf("    /%s | %s | %d | %d", file_name.c_str(), client_ip.c_str(), port_number, it->second);
    std::cout << std::endl;
  }

  mx.unlock();
}