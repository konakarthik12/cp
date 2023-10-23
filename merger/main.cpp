#include <caideInliner.hpp>
#include <filesystem>
#include <iostream>
#include <string>

using namespace std;

void try_remove(const std::filesystem::path& p) {
  try {
    std::filesystem::remove(p);

  } catch (const std::filesystem::filesystem_error& err) {
    std::cout << "filesystem error: " << err.what() << '\n';
  }
}
int main() {
  string outputFile = "output/merged.cpp";
  try_remove(outputFile);
  string tmpDirectory = "build/.caide-tmp";

  caide::CppInliner inliner(tmpDirectory);

  vector<string> sourceFiles = {"main.cpp"};

  int maxConsecutiveEmptyLines = 1;
  vector<string> isystemDirs = {"/opt/homebrew/opt/llvm/include/c++/v1/",
                                "/opt/homebrew/opt/llvm/lib/clang/17/include/",
                                "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/"};

  inliner.clangCompilationOptions = {"-std=c++20", "-I", ".", "-target", "arm64-apple-darwin22.4.0", "-include-pch", "build/wrapper.h.gch"};

  for (const auto& item: isystemDirs) {
    inliner.clangCompilationOptions.emplace_back("-isystem");
    inliner.clangCompilationOptions.emplace_back(item);
  }
  inliner.maxConsequentEmptyLines = maxConsecutiveEmptyLines;
  auto t1 = std::chrono::high_resolution_clock::now();
  try {
    inliner.inlineCode(sourceFiles, outputFile);
    auto t2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> ms_double = t2 - t1;
    std::cout << "Completed in " << ms_double.count() << " ms" << endl;
  } catch (...) {
    try_remove(outputFile);
  }

  return 0;
}
