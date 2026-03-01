#ifndef UI_H
#define UI_H

#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

class UI {
public:
    void init();
    void showHelp();
    void draw(const std::vector<fs::directory_entry>& items,
              int selected,
              int offset,
              const std::string& path);
    int handleInput();
    void close();
};

#endif
