
# cloc – Simple C++ Line Counter

[![cloc](https://img.shields.io/badge/cloc-ellii_%3C3-ff69b4?style=for-the-badge)](https://github.com/advantagewtf/cloc)

A lightweight, fast, and cute **C++-written** alternative to the classic `cloc` (Count Lines of Code) tool.

Inspired by the original `cloc` by Al Danial, this version is lovingly crafted by **ellii** with a focus on simplicity, readability, and a touch of personality. 💖

## Features

- Counts **code**, **comment**, and **blank** lines
- Supports:
  - **C++** (`.cpp`, `.cc`, `.cxx`, `.h`, `.hpp`)
  - **Python** (`.py`)
  - **JSON** (`.json`)
  - **XML** (`.xml`)
  - **Markdown** (`.md`)
  - **Visual Studio Solutions** (`.sln`)
- Handles `//` comments, `/* */` block comments (including multi-line)
- Python `#` comments
- Recursive directory scanning
- Pretty formatted output with performance stats
- Zero external dependencies beyond the C++17 standard library

## Example

```
      42 text files.
      38 unique files.
       4 files ignored.

cloc | created by ellii <3 T=0.12 s (316.7 files/s, 2483.3 lines/s)
------------------------------------------------------------------------------------
Language                               files          blank        comment           code
------------------------------------------------------------------------------------
C++                                       25             87            142           1823
Python                                     8             23             45            312
Markdown                                   5             12              0            156
------------------------------------------------------------------------------------
SUM:                                      38            122            187           2291
------------------------------------------------------------------------------------
```

## Build

```bash
# Requires a C++17-compliant compiler (g++, clang++, MSVC)
g++ -std=c++17 -O2 cloc.cpp -o cloc
```

Or with clang:
```bash
clang++ -std=c++17 -O2 cloc.cpp -o cloc
```

On Windows with MSVC:
```cmd
cl /EHsc /std:c++17 cloc.cpp
```

## Usage

```bash
# Count lines in current directory
./cloc

# Count lines in a specific path
./cloc /path/to/project

# Example
./cloc ../my-awesome-cpp-project
```

## Performance

Built for speed using `std::filesystem` and minimal regex overhead.  
Typical speed: **300–1000+ files/sec** on modern hardware.

## Why another cloc?

- Learning project with clean, educational C++17 code
- No Perl/Python dependency
- Tiny binary (~50 KB stripped)
- Cute output because why not? <3

## License

MIT License – feel free to use, modify, and share!





Enjoy counting lines with love! 💕
```
