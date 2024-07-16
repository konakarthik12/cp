#include <caideInliner.hpp>
#include <iostream>
#include <string>

using namespace std;


int main() {
    string outputFile = "output/merged.cpp";
    string tmpDirectory = "build/caide/";

    caide::CppInliner inliner(tmpDirectory);

    vector<string> sourceFiles = {"template.cpp"};

    int maxConsecutiveEmptyLines = 1;
    vector<string> isystemDirs = {
            "/opt/homebrew/opt/llvm/include/c++/v1/",
            "/opt/homebrew/opt/llvm/lib/clang/18/include/",
            "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include/"};

    inliner.clangCompilationOptions = {"-std=c++17",
                                       "-iquote", ".",
                                       "-iquote", "template/",
                                       "-iquote", "build/preprocess/",
//                                       "-include-pch", "build/wrapper.h.pch"
    };

    for (const auto &item: isystemDirs) {
        inliner.clangCompilationOptions.emplace_back("-isystem");
        inliner.clangCompilationOptions.emplace_back(item);
    }

    inliner.clangCompilationOptions.emplace_back("-DINLINER");
    inliner.clangCompilationOptions.emplace_back("-DPREPROCESS");

    inliner.clangCompilationOptions.emplace_back("-fparse-all-comments");
    inliner.maxConsequentEmptyLines = maxConsecutiveEmptyLines;
    auto t1 = std::chrono::high_resolution_clock::now();
    try {
        inliner.inlineCode(sourceFiles, outputFile);
        auto t2 = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> ms_double = t2 - t1;
        std::cout << "Merged in " << ms_double.count() << " ms" << endl;
    } catch (...) {
        std::cout << "Failed to merge" << endl;
        return -1;
    }

    return 0;
}
