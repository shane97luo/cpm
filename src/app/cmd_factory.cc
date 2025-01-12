#include "cmd_factory.h"

static Receiver sReceiver;

Command *CommandFactory::CreateCommand(const std::string &cmd_type,
                                       const std::string &param) {
  Command *cmd{nullptr};
  if (cmd_type == "new") {
    cmd = new CreateRepositoryCommand(&sReceiver, param);
  } else if (cmd_type == "mod") {
    cmd = new AddModuleCommand(&sReceiver, param);
  }

  return cmd;
}
