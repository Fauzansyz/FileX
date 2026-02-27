#include "file_manager.h"

FileManager::FileManager() {
  currentPath = fs.current_path();
  loadDirectory();
}

void FileManager::loadDirectory() {
  items.clear();
  for(auto &entry : fs::entry_iterator(currentPath)) {
    items.push_back(entry);
  }
  selectedIndex = 0;
}

voud FileManager::goToSelected() {
  currentPath = items[selectedIndex].path();
  loadDirectory();
}
