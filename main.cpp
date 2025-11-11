#include <iostream>
#include <filesystem>
#include <fstream>
#include <map>
#include <string>
#include <iomanip>
#include <regex>
#include <chrono>
#include <algorithm>

namespace fs = std::filesystem;
// only adding this comment to keep my github streak <3
struct Stats {
    int files = 0;
    int blank = 0;
    int comment = 0;
    int code = 0;
};

bool startsWith(const std::string& str, const std::string& prefix) {
    return str.rfind(prefix, 0) == 0;
}

std::string detectLanguage(const fs::path& path) {
    static const std::map<std::string, std::string> extMap = {
        {".cpp", "C++"}, {".cc", "C++"}, {".cxx", "C++"},
        {".h", "C/C++ Header"}, {".hpp", "C/C++ Header"},
        {".json", "JSON"}, {".xml", "XML"},
        {".py", "Python"}, {".md", "Markdown"},
        {".sln", "Visual Studio Solution"}
    };

    auto ext = path.extension().string();
    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
    auto it = extMap.find(ext);
    return (it != extMap.end()) ? it->second : "Unknown";
}

void countFileLines(const fs::path& file, Stats& stats, const std::string& lang) {
    std::ifstream in(file);
    if (!in.is_open()) return;

    std::string line;
    bool inBlockComment = false;

    while (std::getline(in, line)) {
        std::string trimmed = std::regex_replace(line, std::regex("^\\s+|\\s+$"), "");

        if (trimmed.empty()) {
            stats.blank++;
        } else if (lang == "C++" || lang == "C/C++ Header") {
            if (inBlockComment) {
                stats.comment++;
                if (trimmed.find("*/") != std::string::npos)
                    inBlockComment = false;
            } else if (startsWith(trimmed, "//")) {
                stats.comment++;
            } else if (trimmed.find("/*") != std::string::npos) {
                stats.comment++;
                if (trimmed.find("*/") == std::string::npos)
                    inBlockComment = true;
            } else {
                stats.code++;
            }
        } else if (lang == "Python") {
            if (startsWith(trimmed, "#")) stats.comment++;
            else stats.code++;
        } else {
            stats.code++;
        }
    }
}

int main(int argc, char* argv[]) {
    fs::path root = (argc > 1) ? fs::path(argv[1]) : fs::current_path();
    std::map<std::string, Stats> langStats;
    int totalFiles = 0;
    int ignored = 0;
    auto start = std::chrono::high_resolution_clock::now();

    for (auto& p : fs::recursive_directory_iterator(root)) {
        if (!fs::is_regular_file(p.path())) continue;
        totalFiles++;

        std::string lang = detectLanguage(p.path());
        if (lang == "Unknown") {
            ignored++;
            continue;
        }

        Stats& s = langStats[lang];
        s.files++;
        countFileLines(p.path(), s, lang);
    }

    int uniqueFiles = 0, totalBlank = 0, totalComment = 0, totalCode = 0;
    for (auto& [lang, s] : langStats) {
        uniqueFiles += s.files;
        totalBlank += s.blank;
        totalComment += s.comment;
        totalCode += s.code;
    }

    auto end = std::chrono::high_resolution_clock::now();
    double seconds = std::chrono::duration<double>(end - start).count();

    std::cout << std::fixed;
    std::cout << std::setw(8) << totalFiles << " text files.\n";
    std::cout << std::setw(8) << uniqueFiles << " unique files.\n";
    std::cout << std::setw(8) << ignored << " files ignored.\n\n";

    std::cout << "cloc | created by ellii <3  "
              << "T=" << std::setprecision(2) << seconds << " s ("
              << std::setprecision(1) << (uniqueFiles / seconds)
              << " files/s, "
              << std::setprecision(1) << (totalCode / seconds)
              << " lines/s)\n";

    std::cout << "------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(35) << "Language"
              << std::right << std::setw(15) << "files"
              << std::setw(15) << "blank"
              << std::setw(15) << "comment"
              << std::setw(15) << "code" << "\n";
    std::cout << "------------------------------------------------------------------------------------\n";

    for (auto& [lang, s] : langStats) {
        std::cout << std::left << std::setw(35) << lang
                  << std::right << std::setw(15) << s.files
                  << std::setw(15) << s.blank
                  << std::setw(15) << s.comment
                  << std::setw(15) << s.code << "\n";
    }

    std::cout << "------------------------------------------------------------------------------------\n";
    std::cout << std::left << std::setw(35) << "SUM:"
              << std::right << std::setw(15) << uniqueFiles
              << std::setw(15) << totalBlank
              << std::setw(15) << totalComment
              << std::setw(15) << totalCode << "\n";
    std::cout << "------------------------------------------------------------------------------------\n";
}
