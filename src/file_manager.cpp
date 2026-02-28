#include "file_manager.h"
#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

FileManager::FileManager() {
    currentPath = fs::current_path();
    loadDirectory();
}

void FileManager::loadDirectory() {
    items.clear();
    for (auto &entry : fs::directory_iterator(currentPath)) {
        items.push_back(entry);
    }
    selectedIndex = 0;
}

std::vector<fs::directory_entry> FileManager::getItems() {
    return items;
}

fs::path FileManager::getCurrentPath() {
    return currentPath;
}

bool FileManager::isDirectory(int index) {
    return items[index].is_directory();
}

void FileManager::goToSelected() {
    if (isDirectory(selectedIndex)) {
        currentPath /= items[selectedIndex].path().filename();
        loadDirectory();
    }
}

void FileManager::goBack() {
    if (currentPath.has_parent_path()) {
        currentPath = currentPath.parent_path();
        loadDirectory();
    }
}
