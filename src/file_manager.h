#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class FileManager {
public:
    
enum class OpenResult{
  OpenedDirectory,
  OpenedFile,
  Nothing,
};

    FileManager();
    void loadDirectory();
    OpenResult goToSelected();
    void goBack();
    void openFileWithEditor(const std::string& filePath);

    std::vector<fs::directory_entry> getItems();
    fs::path getCurrentPath();
    bool isDirectory(int index);

    int selectedIndex = 0;
    int offset = 0;

private:
    fs::path currentPath;
    std::vector<fs::directory_entry> items;
    bool commandExists(const std::string& command);
    int showEditorPrompt();
};

#endif
