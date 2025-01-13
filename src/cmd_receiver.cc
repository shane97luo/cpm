#include "cmd_receiver.h"

#include <filesystem>
#include <fstream>
#include <iostream>

#include <cmrc/cmrc.hpp>
CMRC_DECLARE(cpm);

static void init_clang(const std::filesystem::path path) {

  auto rc_tidy = cmrc::cpm::get_filesystem().open("style/.clang-tidy");
  std::istringstream src_tidy(std::string(rc_tidy.begin(), rc_tidy.end()));

  std::filesystem::path file_tidy = path / "./.clang-tidy";
  std::ofstream stream_tidy(file_tidy);

  stream_tidy << src_tidy.rdbuf();
  stream_tidy.close();

  auto rc_format = cmrc::cpm::get_filesystem().open("style/.clang-format");
  std::istringstream src_format(
      std::string(rc_format.begin(), rc_format.end()));

  std::filesystem::path file_format = path / "./.clang-format";
  std::ofstream stream_format(file_format);

  stream_format << src_format.rdbuf();
  stream_format.close();

  auto rc_main = cmrc::cpm::get_filesystem().open("style/main.cc");
  std::istringstream src_main(std::string(rc_main.begin(), rc_main.end()));

  std::filesystem::path file_main = path / "./main.cc";
  std::ofstream stream_main(file_main);

  stream_main << src_main.rdbuf();
  stream_main.close();
}

void Receiver::createRepository(const std::string &repo_name) {
  // std::cout << "Creating repository: " << repo_name << std::endl;

  std::filesystem::path repo_path = repo_name;

  if (std::filesystem::exists(repo_path)) {
    std::cout << "dir exists, fail to create " << repo_path << std::endl;
    return;
  }

  std::filesystem::create_directory(repo_name);
  std::cout << "Created repository: " << repo_path << std::endl;

  std::filesystem::path file_cmake = repo_path / "./CMakeLists.txt";

  std::ofstream file(file_cmake);
  if (file.is_open()) {
    file << R"(cmake_minimum_required(VERSION 3.20))";
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

  init_clang(repo_path);
}

void Receiver::addModule(const std::string &module_name) {
  std::cout << "Adding module: " << module_name << std::endl;

  std::filesystem::path mod_path = module_name;

  if (std::filesystem::exists(mod_path)) {
    std::cout << "dir exists, fail to create " << mod_path << std::endl;
    return;
  }

  std::filesystem::create_directory(module_name);
  std::cout << "Created repository: " << mod_path << std::endl;

  std::filesystem::path file_cmake = mod_path / "CMakeLists.txt";

  std::ofstream file(file_cmake);
  if (file.is_open()) {
    file << R"(cmake_minimum_required(VERSION 3.20))";
    file << "\n\n";
    file << R"(project( )" << module_name;
    file << R"( LANGUAGES C CXX))";
    file << "\n\n";
    file << R"(add_library(${PROJECT_NAME}))";
    file << "\n\n";
    file << R"(target_sources(${PROJECT_NAME} PRIVATE)";
    file << R"(    export.cc)";
    file << R"())";
  }
}
