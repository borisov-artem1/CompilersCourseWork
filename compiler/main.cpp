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

    std::string path = "../compiler/oberonPrograms/2.txt";
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
    auto* module = new llvm::Module("main", llvmContext);
    oberonBaseVisitor visitor(llvmContext, builder, module);

    visitor.visit(tree);

    visitor.module->print(llvm::outs(), nullptr);



    return 0;
}
