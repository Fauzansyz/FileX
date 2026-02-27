#include "file_manager.h"

FileManager::FileManager() {
  currentPath = fs.current_path();
  loadDirectory();
}

void FileManager::loadDirectory() {
  items.clear();
  for(auto &entry : fs::directory_entry(currentPath)) {
    items.push_back(entry);
  }
  selectedIndex = 0;
}

std::vector<fs::directory_entry> FileManager::getItems() {
  return items;
}

std::path FileManager::getCurrentPath() {
  return currentPath;
}

bool FileManager::isDirectory(int index) {
  return items[index].is_directory();
}

void FileManager::goToSelected(){
  if(isDirectory(selectedIndex)) currentPath /= items[selectedIndex].path().filename();
  loadDirectory();
}

void FileManager::goBack(){
  if(currentPath.has_parent_path()) currentPath = currentPath.parent_path();
  loadDirectory();
}
