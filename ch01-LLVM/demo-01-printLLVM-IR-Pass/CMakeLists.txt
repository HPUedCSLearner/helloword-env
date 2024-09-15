cmake_minimum_required(VERSION 3.5.0)
project(printLLVMIR VERSION 0.1.0 LANGUAGES C CXX)


# # 设置 C++ 标准
# set(CMAKE_CXX_STANDARD 17)
# set(CMAKE_CXX_STANDARD_REQUIRED YES)

# 设置LLVM包路径
# set(LLVM_DIR /home/feng/llvm-src/llvm-project-llvmorg-14.0.6/llvm/build-rel/lib/cmake/llvm)
set(LLVM_DIR /home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/lib/cmake/llvm)

find_package(LLVM REQUIRED CONFIG)
message(STATUS "==find llvm ${LLVM_PACKAGE_VERSION}")
message(STATUS "==using LLVMConfig.cmake in:${LLVM_DIR}")

# 包含 LLVM 的头文件和库
include_directories(${LLVM_INCLUDE_DIRS})
link_directories(${LLVM_LIBRARY_DIRS})
message(STATUS "==LLVM_INCLUDE_DIRS: ${LLVM_INCLUDE_DIRS}")
message(STATUS "==LLVM_LIBRARY_DIRS: ${LLVM_LIBRARY_DIRS}")

# 定义 Pass 插件的目标
add_library(PrintIRPass SHARED printLLVMIR.cpp)
 
# 链接 LLVM 库
llvm_map_components_to_libnames(LLVM_LIBS
  Core
  Support
  Passes
)
# llvm_map_components_to_libnames: 这是一个 LLVM 的 CMake 宏，它会根据你提供的 LLVM 组件名称列表，生成相应的库列表，并将它们存储在指定的变量中（在这个例子中是 LLVM_LIBS）。


target_link_libraries(PrintIRPass PRIVATE ${LLVM_LIBS})

# 安装 Pass 插件
install(TARGETS PrintIRPass
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
)
# install 命令的作用是将构建输出的库文件（无论是共享库还是静态库）安装到指定的目录中。在你的例子中，LIBRARY 和 ARCHIVE 的目标路径都是 lib，表示将生成的插件库文件存放在工程目录的 lib/ 子目录下

