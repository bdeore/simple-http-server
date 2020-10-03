#include <iostream>
#include <vector>
#include <string>
#ifndef _LOGGER_H_
#define _LOGGER_H_

class Logger {
 public:
  Logger();
  ~Logger();
  std::vector<std::string> logs;
};

#endif
