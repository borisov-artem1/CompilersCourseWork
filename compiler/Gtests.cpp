#include <gtest/gtest.h>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

std::string readFile(const fs::path& path) {
    std::ifstream file(path);
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}


class FileComparisonTest : public ::testing::TestWithParam<std::string> {};

TEST_P(FileComparisonTest, MatchesExpectedOutput) {
    std::string filename = GetParam();

    fs::path expectedPath = fs::path("../compiler/expected") / filename;
    fs::path outPath = fs::path("../compiler/out") / filename;

    ASSERT_TRUE(fs::exists(expectedPath)) << "Expected file missing: " << expectedPath;
    ASSERT_TRUE(fs::exists(outPath)) << "Output file missing: " << outPath;

    std::string expectedContent = readFile(expectedPath);
    std::string actualContent = readFile(outPath);

    EXPECT_EQ(expectedContent, actualContent);
}


INSTANTIATE_TEST_SUITE_P(AllFiles, FileComparisonTest, ::testing::Values(
    "1.txt", "2.txt", "3.txt", "4.txt", "5.txt", "6.txt", "7.txt"
));
