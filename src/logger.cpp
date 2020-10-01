#include <iostream>
#include "logger.h"

Logger::Logger() {
  std::cout << "inside Logger constructor" << std::endl;
}

Logger::~Logger() {
  std::cout << "inside Logger destructor" << std::endl;
}
