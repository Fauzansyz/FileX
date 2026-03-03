#ifndef UI_H
#define UI_H

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

class UI {
public:
  void init();
  void showHelp();
  void draw(const std::vector<fs::directory_entry> &items, int selected,
            int offset, const std::string &path);
  void drawStatusBar(const std::vector<fs::directory_entry> &items,
                     int selected);
  int handleInput();
  void close();
};

#endif
