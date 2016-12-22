cmake_minimum_required(VERSION 3.6)
project(TaskManager)

set(CMAKE_CXX_STANDARD 11)

#set(SANITIZE_FLAGS "${SANITIZE_FLAGS} -fsanitize=leak")
#set(CMAKE_C_FLAGS   "${CMAKE_C_FLAGS} ${SANITIZE_FLAGS}")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${SANITIZE_FLAGS}")

set(SOURCE_FILES main.c millis.c millis.h task.c task.h task_manager.c task_manager.h)
add_executable(TaskManager ${SOURCE_FILES})