#include "cmd_factory.h"
#include "cmd_strategy.h"
#include "cmdline/cmdline.h"
#include <ctime>
#include <fstream>
#include <iomanip>
#include <memory>
#include <ostream>
#include <set>
#include <string>
#include <thread>

#include "ccpm_config.h"

#include "3rdparty/toml11/single_include/toml.hpp"

struct AwakeProgram {
  AwakeProgram(const toml::value &v)
      : program(toml::find_or<std::string>(v, "program", "")),
        path(toml::find_or<std::string>(v, "path", "")),
        parameter(toml::find_or<std::string>(v, "parameter", "")) {}
  std::string program;
  std::string path;
  std::string parameter;
};

void parseToml(const std::string &path) {

  try {
    // 从文件中读取 TOML 数据
    std::ifstream ifs(path);
    auto root = toml::parse(ifs);

    // 获取 file 属性
    const auto &file = toml::find<std::string>(root, "file");
    std::cout << "File: " << file << std::endl;

    const auto awake_programs =
        toml::find<std::vector<AwakeProgram>>(root, "awake");

    std::cout << "awake size:" << awake_programs.size() << std::endl;

    for (auto &prog : awake_programs) {
      std::cout << "awake size:" << prog.program << prog.path << prog.parameter
                << std::endl;
    }

    // 获取 awake 数组
  } catch (const toml::syntax_error &e) {
    std::cerr << "Syntax error: " << e.what() << std::endl;
  } catch (const toml::type_error &e) {
    std::cerr << "Type error: " << e.what() << std::endl;
  }
}

int main(int argc, char *argv[]) {

  std::cout << "version:" << PROJECT_VERSION << std::endl;
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
