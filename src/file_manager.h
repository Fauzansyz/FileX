#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class FileManager {
public:
    FileManager();
    void loadDirectory();
    void goToSelected();
    void goBack();

    std::vector<fs::directory_entry> getItems();
    fs::path getCurrentPath();
    bool isDirectory(int index);

    int selectedIndex = 0;
    int offset = 0;

private:
    fs::path currentPath;
    std::vector<fs::directory_entry> items;
};

#endif
