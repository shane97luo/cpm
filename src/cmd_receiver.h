#ifndef _CMD_RECEIVER_H
#define _CMD_RECEIVER_H

#include <string>

// 接收者类
class Receiver {
public:
  void createRepository(const std::string &repo_name);

  void addModule(const std::string &module_name);
};

#endif // _CMD_RECEIVER_H