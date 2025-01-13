#include "cmd_strategy.h"

#include <filesystem>
#include <fstream>

// 新建仓库具体命令类
CreateRepositoryCommand::CreateRepositoryCommand(Receiver *receiver,
                                                 const std::string &name)
    : _receiver(receiver), _repo_name(name) {}

void CreateRepositoryCommand::execute() {
  _receiver->createRepository(_repo_name);
}

// 增加模块具体命令类
AddModuleCommand::AddModuleCommand(Receiver *receiver, const std::string &name)
    : _receiver(receiver), _module_name(name) {}

void AddModuleCommand::execute() { _receiver->addModule(_module_name); }
