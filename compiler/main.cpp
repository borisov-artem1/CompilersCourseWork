#include <iostream>
#include <fstream>
#include <memory>
#include <antlr4-runtime.h>

#include "oberonBaseVisitor.h"
#include "oberonLexer.h"
#include "oberonParser.h"
#include "oberonVisitor.h"

int main()
{

    std::string path = "../compiler/oberonPrograms/6.txt";
    std::ifstream file(path);
    if (!file.is_open())
    {
        std::cerr << "Failed to open file " << path << std::endl;
        return 1;
    }

    antlr4::ANTLRInputStream input(file);

    oberonLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    oberonParser parser(&tokens);

    antlr4::tree::ParseTree* tree = parser.module();

    llvm::LLVMContext llvmContext;
    llvm::IRBuilder<> builder(llvmContext);

    // auto* module = new llvm::Module("main", llvmContext);
    auto module = std::make_shared<llvm::Module>("main", llvmContext);
    oberonBaseVisitor visitor(llvmContext, builder, module.get());

    visitor.visit(tree);


    std::error_code ec;
    llvm::raw_fd_ostream dest("output.ll", ec);
    if (ec)
    {
        std::cerr << ec.value() << std::endl;
        return 1;
    }
    visitor.module->print(dest, nullptr);
    dest.close();
    // visitor.module->print(llvm::outs(), nullptr);



    return 0;
}
