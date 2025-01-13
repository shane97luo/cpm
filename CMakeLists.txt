cmake_minimum_required(VERSION 3.20)

set(PROJECT_VERSION_MAJOR 0)
set(PROJECT_VERSION_MINOR 0)
set(PROJECT_VERSION_PATCH 1)
set(PROJECT_VERSION "${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}.${PROJECT_VERSION_PATCH}")

project(ccpm LANGUAGES C CXX VERSION ${PROJECT_VERSION})


include(cmake/build.cmake)
include(cmake/cmrc.cmake)


configure_file(
  "${PROJECT_SOURCE_DIR}/setup/ccpm_config.h.in"
  "${PROJECT_BINARY_DIR}/ccpm_config.h"
)


cmrc_add_resource_library(cpm-rc
  ALIAS cpm::rc
  NAMESPACE cpm
  WHENCE ${SETUP_RESOURCE_PATH}/style
  PREFIX style
  ${SETUP_RESOURCE_PATH}/style/.clang-format
  ${SETUP_RESOURCE_PATH}/style/.clang-tidy
  ${SETUP_RESOURCE_PATH}/style/main.cc
)


add_executable(${PROJECT_NAME})


target_include_directories(${PROJECT_NAME} PRIVATE
  ${PROJECT_BINARY_DIR}
)


target_sources(${PROJECT_NAME} PRIVATE
  src/main.cc
  src/cmd_receiver.h
  src/cmd_receiver.cc
  src/cmd_strategy.h
  src/cmd_strategy.cc
  src/cmd_factory.h
  src/cmd_factory.cc
  src/cmdline/cmdline.h
)


target_link_libraries(${PROJECT_NAME} PRIVATE
  cpm-rc
)


# 设置安装规则
install(TARGETS ccpm
  DESTINATION /usr/local/bin
)



# 设置 CPACK 信息
set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "MyProject - A simple project")
set(CPACK_PACKAGE_VENDOR "Your Company")
set(CPACK_PACKAGE_CONTACT "your.email@example.com")
set(CPACK_PACKAGE_FILE_NAME "${CPACK_PACKAGE_NAME}-${CPACK_PACKAGE_VERSION}-${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_PROCESSOR}")

# # 设置不同类型的包生成器
set(CPACK_GENERATOR "DEB;RPM;ZIP")

# 设置 DEB 包信息
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Your Name <your.email@example.com>")
set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.3.1)")

# 设置 RPM 包信息
set(CPACK_RPM_PACKAGE_LICENSE "MIT")
set(CPACK_RPM_PACKAGE_GROUP "Development/Tools")
set(CPACK_RPM_PACKAGE_REQUIRES "glibc >= 2.3.1")

# 包含 CPACK 模块
# include(CPACK)