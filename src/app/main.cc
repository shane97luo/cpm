#include "cmd_factory.h"
#include "cmd_strategy.h"
#include "cmdline/cmdline.h"
#include <ctime>
#include <iomanip>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <thread>

int main(int argc, char *argv[]) {
  cmdline::parser a;

  a.add("new", 'n', "new a program", false, std::string());
  a.add("build", '\0', "build program", false, std::string());
  a.add("mod", 'm', "add a mod", false, std::string());

  a.parse_check(argc, argv);

  std::string cmd_type;
  std::string cmd_param;

  std::set<std::string> cmd_map{"new", "mod"};
  bool contains{false};

  for (auto cmd : cmd_map) {
    if (a.exist(cmd)) {
      contains = true;

      cmd_type = cmd;
      cmd_param = a.get<std::string>(cmd);
      std::cout << "cmd type:" << cmd_type << "cmd param:" << cmd_param
                << std::endl;
      break;
    }
  }

  if (!contains) {
    return -1;
  }

  auto invoker = std::make_unique<Invoker>();

  auto cmd = CommandFactory::CreateCommand(cmd_type, cmd_param);
  invoker->addCommand(cmd);

  invoker->executeCommands();

  return 0;
}
