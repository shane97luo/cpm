#ifndef _CMD_STRATEGY_H
#define _CMD_STRATEGY_H

#include "cmd_receiver.h"
#include <iostream>
#include <string>
#include <vector>

// 接收者类
// class Receiver {
// public:
//   void createRepository(const std::string &repo_name);

//   void addModule(const std::string &module_name);
// };

// 命令抽象类
class Command {
public:
  virtual void execute() = 0;
  virtual ~Command() = default;
};

// 新建仓库具体命令类
class CreateRepositoryCommand : public Command {
private:
  Receiver *_receiver;
  std::string _repo_name;

public:
  CreateRepositoryCommand(Receiver *r, const std::string &name);

  void execute() override;
};

// 增加模块具体命令类
class AddModuleCommand : public Command {
private:
  Receiver *receiver;
  std::string _module_name;

public:
  AddModuleCommand(Receiver *r, const std::string &name);

  void execute() override;
};

// 调用者类
class Invoker {
private:
  std::vector<Command *> _commands;

public:
  void addCommand(Command *command) { _commands.push_back(command); }

  void executeCommands() {
    for (Command *command : _commands) {
      command->execute();
    }
    for (Command *command : _commands) {
      delete command;
    }
    _commands.clear();
  }
};

#endif // _CMD_STRATEGY_H