# cmake_minimum_required(VERSION 3.5)

project(ccpm LANGUAGES C CXX  VERSION 0.0.1)


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


target_sources(${PROJECT_NAME} PRIVATE
  main.cc
  cmd_receiver.h
  cmd_receiver.cc
  cmd_strategy.h
  cmd_strategy.cc
  cmd_factory.h
  cmd_factory.cc
  cmdline/cmdline.h
)


target_link_libraries(${PROJECT_NAME} PRIVATE
 cpm-rc   
)