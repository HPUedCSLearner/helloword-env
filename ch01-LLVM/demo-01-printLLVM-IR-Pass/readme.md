# 这是一个LLVM的环境搭建的Dmeo
使用CMAKE构建工程  


## 环境安装
参考链接：
1. LLVM系列第一章：编译LLVM源码 —— https://blog.csdn.net/Zhanglin_Wu/article/details/124942823

需要注意的点，NOTE：
1. 注意设置LLVM的Package的路径；  

## 使用PASS
```bash
clang -O1 -emit-llvm -S test.cpp -o test.ll
```


```bash
opt -load-pass-plugin ./build/libPrintIRPass.so -passes="print-func-names" -o output.ll < test.ll
```


## 当前遇到问题，遇到的问题
### 1、使用opt后，会出现段错误。。。
```bash
feng@feng-X99M-D3:~/github/helloword-env/ch01-LLVM/demo-01-printLLVM-IR-Pass$ opt -load-pass-plugin ./build/libPrintIRPass.so -passes="print-func-names" -o output.ll < test.ll
opt: CommandLine Error: Option 'use-dereferenceable-at-point-semantics' registered more than once!
LLVM ERROR: inconsistency in registered CommandLine options
PLEASE submit a bug report to https://github.com/llvm/llvm-project/issues/ and include the crash backtrace.
Stack dump:
0.      Program arguments: opt -load-pass-plugin ./build/libPrintIRPass.so -passes=print-func-names -o output.ll
 #0 0x000000000256c113 llvm::sys::PrintStackTrace(llvm::raw_ostream&, int) (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x256c113)
 #1 0x000000000256a06e llvm::sys::RunSignalHandlers() (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x256a06e)
 #2 0x000000000256c49f SignalHandler(int) Signals.cpp:0:0
 #3 0x00007ef674a42520 (/lib/x86_64-linux-gnu/libc.so.6+0x42520)
 #4 0x00007ef674a969fc pthread_kill (/lib/x86_64-linux-gnu/libc.so.6+0x969fc)
 #5 0x00007ef674a42476 gsignal (/lib/x86_64-linux-gnu/libc.so.6+0x42476)
 #6 0x00007ef674a287f3 abort (/lib/x86_64-linux-gnu/libc.so.6+0x287f3)
 #7 0x00000000024e34b8 (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x24e34b8)
 #8 0x00000000024e32d6 (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x24e32d6)
 #9 0x00000000024db2a0 (anonymous namespace)::CommandLineParser::removeOption(llvm::cl::Option*, llvm::cl::SubCommand*) CommandLine.cpp:0:0
#10 0x00000000024cdc0b llvm::cl::Option::addArgument() (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x24cdc0b)
#11 0x00007ef6746dba96 _GLOBAL__sub_I_Value.cpp Value.cpp:0:0
#12 0x00007ef67520c47e (/lib64/ld-linux-x86-64.so.2+0x647e)
#13 0x00007ef67520c568 (/lib64/ld-linux-x86-64.so.2+0x6568)
#14 0x00007ef674b74af5 _dl_catch_exception (/lib/x86_64-linux-gnu/libc.so.6+0x174af5)
#15 0x00007ef675213ff6 (/lib64/ld-linux-x86-64.so.2+0xdff6)
#16 0x00007ef674b74a98 _dl_catch_exception (/lib/x86_64-linux-gnu/libc.so.6+0x174a98)
#17 0x00007ef67521434e (/lib64/ld-linux-x86-64.so.2+0xe34e)
#18 0x00007ef674a9063c (/lib/x86_64-linux-gnu/libc.so.6+0x9063c)
#19 0x00007ef674b74a98 _dl_catch_exception (/lib/x86_64-linux-gnu/libc.so.6+0x174a98)
#20 0x00007ef674b74b63 _dl_catch_error (/lib/x86_64-linux-gnu/libc.so.6+0x174b63)
#21 0x00007ef674a9012e (/lib/x86_64-linux-gnu/libc.so.6+0x9012e)
#22 0x00007ef674a906c8 dlopen (/lib/x86_64-linux-gnu/libc.so.6+0x906c8)
#23 0x0000000002558769 llvm::sys::DynamicLibrary::getPermanentLibrary(char const*, std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> >*) (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x2558769)
#24 0x00000000028317ae llvm::PassPlugin::Load(std::__cxx11::basic_string<char, std::char_traits<char>, std::allocator<char> > const&) (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x28317ae)
#25 0x000000000078b968 llvm::runPassPipeline(llvm::StringRef, llvm::Module&, llvm::TargetMachine*, llvm::TargetLibraryInfoImpl*, llvm::ToolOutputFile*, llvm::ToolOutputFile*, llvm::ToolOutputFile*, llvm::StringRef, llvm::ArrayRef<llvm::StringRef>, llvm::opt_tool::OutputKind, llvm::opt_tool::VerifierKind, bool, bool, bool, bool, bool) (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x78b968)
#26 0x00000000007a138b main (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x7a138b)
#27 0x00007ef674a29d90 (/lib/x86_64-linux-gnu/libc.so.6+0x29d90)
#28 0x00007ef674a29e40 __libc_start_main (/lib/x86_64-linux-gnu/libc.so.6+0x29e40)
#29 0x000000000078700a _start (/home/feng/llvm-compiled-tools/clang+llvm-14.0.0-x86_64-linux-gnu-ubuntu-18.04/bin/opt+0x78700a)
已放弃 (核心已转储)
```