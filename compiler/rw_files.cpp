#include <iostream>
#include <fstream>
#include <memory>
#include <antlr4-runtime.h>

#include "oberonBaseVisitor.h"
#include "oberonLexer.h"
#include "oberonParser.h"
#include "oberonVisitor.h"

void processing_files(std::ifstream& ifs)
{

    antlr4::ANTLRInputStream input(ifs);

    oberonLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    oberonParser parser(&tokens);

    antlr4::tree::ParseTree* tree = parser.module();

    llvm::LLVMContext llvmContext;
    llvm::IRBuilder<> builder(llvmContext);

    auto module = std::make_shared<llvm::Module>("main", llvmContext);
    oberonBaseVisitor visitor(llvmContext, builder, module.get());

    visitor.visit(tree);


    std::error_code ec;
    static int counter = 1;
    std::string outputPath = "../compiler/llvmIR/" + std::to_string(counter++) + "output.ll";
    llvm::raw_fd_ostream dest(outputPath, ec);
    if (ec)
    {
        std::cerr << ec.value() << std::endl;
        throw std::runtime_error("Error writing output file" + ec.message());
    }
    visitor.module->print(dest, nullptr);
    dest.close();
}
