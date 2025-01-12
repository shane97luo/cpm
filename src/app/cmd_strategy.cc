#include "cmd_strategy.h"

#include <filesystem>
#include <fstream>

#include <cmrc/cmrc.hpp>
CMRC_DECLARE(cpm);

void Receiver::createRepository(const std::string &repo_name) {
  // std::cout << "Creating repository: " << repo_name << std::endl;

  std::filesystem::path repo_path = repo_name;

  if (!std::filesystem::exists(repo_path)) {
    std::cout << "dir exists, fail to create " << repo_path << std::endl;
  }

  std::filesystem::create_directory(repo_name);
  std::cout << "Created repository: " << repo_path << std::endl;

  std::filesystem::path file_cmake = repo_path / "./CMakeLists.txt";

  std::ofstream file(file_cmake);
  if (file.is_open()) {
    file << R"(cmake_minimum_required(VERSION 3.15))";
    file << "\n\n";

    file << R"(project( )" << repo_name;
    file << R"( LANGUAGES C CXX))";
    file << "\n\n";

    file << R"(add_executable(${PROJECT_NAME}))";
    file << "\n\n";

    file << R"(target_sources(${PROJECT_NAME} PRIVATE)";
    file << R"(    main.cc)";
    file << R"())";

    file << "\n\n";

    file.close();
    std::cout << "文件创建成功" << std::endl;
  } else {
    std::cout << "无法创建文件" << std::endl;
  }

  auto rc_tidy = cmrc::cpm::get_filesystem().open("style/.clang-tidy");
  std::istringstream src_tidy(std::string(rc_tidy.begin(), rc_tidy.end()));

  std::filesystem::path file_tidy = repo_path / "./.clang-tidy";
  std::ofstream stream_tidy(file_tidy);

  stream_tidy << src_tidy.rdbuf();
  stream_tidy.close();

  auto rc_format = cmrc::cpm::get_filesystem().open("style/.clang-format");
  std::istringstream src_format(
      std::string(rc_format.begin(), rc_format.end()));

  std::filesystem::path file_format = repo_path / "./.clang-format";
  std::ofstream stream_format(file_format);

  stream_format << src_format.rdbuf();
  stream_format.close();

  auto rc_main = cmrc::cpm::get_filesystem().open("style/main.cc");
  std::istringstream src_main(std::string(rc_main.begin(), rc_main.end()));

  std::filesystem::path file_main = repo_path / "./main.cc";
  std::ofstream stream_main(file_main);

  stream_main << src_main.rdbuf();
  stream_main.close();
}

void Receiver::addModule(const std::string &module_name) {
  std::cout << "Adding module: " << module_name << std::endl;
}

// 新建仓库具体命令类

CreateRepositoryCommand::CreateRepositoryCommand(Receiver *r,
                                                 const std::string &name)
    : _receiver(r), _repo_name(name) {}

void CreateRepositoryCommand::execute() {
  _receiver->createRepository(_repo_name);
}

// 增加模块具体命令类

AddModuleCommand::AddModuleCommand(Receiver *r, const std::string &name)
    : receiver(r), _module_name(name) {}

void AddModuleCommand::execute() { receiver->addModule(_module_name); }
