cmake_minimum_required(VERSION 3.20)

project(hub LANGUAGES C CXX)

add_executable(${PROJECT_NAME})


# 查找 Poco 库
find_package(Poco REQUIRED COMPONENTS Foundation Util Net)
if (Poco_FOUND)
    
    include_directories(${Poco_INCLUDE_DIRS})
    
    target_link_libraries(${PROJECT_NAME} 
      Poco::Foundation
      Poco::Util
      Poco::Net
    )

else()
    message(FATAL_ERROR "Poco not found")
endif()

target_sources(${PROJECT_NAME} PRIVATE    
  src/main.cc
  src/ws_proxy.h
  src/ws_proxy.cc
  src/ws_client.h
  src/ws_client.cc
  src/server_application.h
  src/server_application.cc
  src/static_file_handler.h
  src/static_file_handler.cc
  src/queue_mgr.h
  src/queue_mgr.cc
)

set(CMAKE_TA)
