#include "llvm/IR/PassManager.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Passes/PassPlugin.h" // 添加这一行
#include "llvm/Passes/PassBuilder.h"


using namespace llvm;

namespace {

class PrintFunctionNamesPass : public PassInfoMixin<PrintFunctionNamesPass> {
public:
    // 实现 run 方法
    PreservedAnalyses run(Module &M, ModuleAnalysisManager &) {
        for (Function &F : M) {
            // 如果函数不是声明 (即有函数体)
            if (!F.isDeclaration()) {
                // 打印函数名称
                errs() << "Function Name: " << F.getName() << "\n";
            }
        }
        // 保持所有分析不变
        return PreservedAnalyses::all();
    }
};

} // end anonymous namespace

// Pass 插件的注册
llvm::PassPluginLibraryInfo getPrintFunctionNamesPassPluginInfo() {
    return {LLVM_PLUGIN_API_VERSION, "PrintFunctionNamesPass", LLVM_VERSION_STRING,
            [](PassBuilder &PB) {
                PB.registerPipelineParsingCallback(
                    [](StringRef Name, ModulePassManager &MPM,
                       ArrayRef<PassBuilder::PipelineElement>) {
                        if (Name == "print-func-names") {
                            MPM.addPass(PrintFunctionNamesPass());
                            return true;
                        }
                        return false;
                    });
            }};
}

// 注册插件
extern "C" LLVM_ATTRIBUTE_WEAK ::llvm::PassPluginLibraryInfo llvmGetPassPluginInfo() {
    return getPrintFunctionNamesPassPluginInfo();
}
