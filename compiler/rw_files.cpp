#include <iostream>
#include <fstream>
#include <memory>
#include <antlr4-runtime.h>

#include "oberonBaseVisitor.h"
#include "oberonLexer.h"
#include "oberonParser.h"
#include "oberonVisitor.h"

#include "json.hpp"
using json = nlohmann::json;

int nodeCounter = 0;
std::string escape(const std::string& s)
{
    std::string escaped;
    for (char c : s)
    {
        if (c == '"')
        {
            escaped += "\\\"";
        } else
        {
            escaped += c;
        }
    }
    return escaped;
}

int jsonToDot(const json& node, std::ostream& out, int parentId = -1)
{
    int current = nodeCounter++;
    auto label = node["name"].get<std::string>();

    out << " node" << current << " [label=\"" << escape(label) << "\"];\n";

    if (parentId != -1)
    {
        out << " node" << parentId << "-> node" << current << ";\n";
    }

    for (const auto& child : node["children"])
    {
        jsonToDot(child, out, current);
    }

    return current;
}

void generateDotFile(const json& node, const std::string& filename)
{
    std::ofstream out(filename);
    out << "digraph ParseTree {\n";
    out << " node [shape=box, fontname=\"Courier\"];\n";
    jsonToDot(node, out);
    out << "}\n";
    out.close();
}

json parseTreeToJson(antlr4::tree::ParseTree* tree, antlr4::Parser* parser) {
    json node;

    std::string nodeName = tree->getText();
    auto ruleIndex = dynamic_cast<antlr4::ParserRuleContext*>(tree);
    if (ruleIndex) {
        nodeName = parser->getRuleNames()[ruleIndex->getRuleIndex()];
    }

    node["name"] = nodeName;
    // написать типы узлов, так как дерево типизированное

    if (tree->children.empty()) {
        node["children"] = json::array();
    } else {
        for (auto child : tree->children) {
            node["children"].push_back(parseTreeToJson(child, parser));
        }
    }

    return node;
}

void processing_files(std::ifstream& ifs)
{

    antlr4::ANTLRInputStream input(ifs);

    oberonLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);

    oberonParser parser(&tokens);

    antlr4::tree::ParseTree* tree = parser.module();

    json treeJson = parseTreeToJson(tree, &parser);

    std::ofstream out("parse_tree.json");
    generateDotFile(treeJson, "tree.dot");
    system("dot -Tpng tree.dot -o tree.png");
    out << treeJson.dump(2);
    out.close();

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
