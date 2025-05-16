#include <iostream>
#include <fstream>
#include <memory>
#include <antlr4-runtime.h>
#include <filesystem>
#include <gtest/gtest.h>

#include "oberonBaseVisitor.h"
#include "oberonLexer.h"
#include "oberonParser.h"
#include "oberonVisitor.h"

void processing_files(std::ifstream& ifs);


int main(int argc, char** argv)
{

    std::string path = "../compiler/oberonPrograms";
    std::vector<std::filesystem::directory_entry> files;

    for (const auto& entry : std::filesystem::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            files.push_back(entry);
        }
    }

    std::ranges::sort(files,
                      [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
                      {
                          return a.path().filename() < b.path().filename();
                      });

    for (const auto& entry : files)
    {
        std::ifstream ifs(entry.path());
        if (!ifs.is_open())
        {
            std::cerr << "Failed to open file " << path << std::endl;
            return 1;
        }
        processing_files(ifs);
    }

    std::vector<std::filesystem::directory_entry> llFiles;
    std::string pathToLLFiles = "../compiler/llvmIR";
    for (const auto& entry : std::filesystem::directory_iterator(pathToLLFiles))
    {
        if (entry.is_regular_file())
        {
            llFiles.push_back(entry);
        }
    }

    std::ranges::sort(llFiles,
        [](const std::filesystem::directory_entry& a, const std::filesystem::directory_entry& b)
    {
       return a.path().filename() < b.path().filename();
    });

    int counter = 1;
    for (const auto& entry : llFiles)
    {
        std::string pathToLLVMFiles = entry.path().string();
        system(("lli " + pathToLLVMFiles + "> ../compiler/out/" + std::to_string(counter++) + ".txt").c_str());
    }

    // ::testing::InitGoogleTest(&argc, argv);
    // return RUN_ALL_TESTS();


    //return 0;
}
