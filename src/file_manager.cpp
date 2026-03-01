#include "file_manager.h"
#include <filesystem>
#include <vector>
#include <ncurses.h>
#include <iostream>

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
    offset = 0;
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

bool FileManager::commandExists(const std::string& cmd) {
      std::string check = "command -v " + cmd + " > /dev/null 2>&1";
      return system(check.c_str()) == 0;
}

bool FileManager::deleteSelected(){
  if(items.empty()) return false;

  fs::path target = items[selectedIndex].path();
  int confirm = showDeleteConfirm();

  if(confirm == 0) return false;
  if(target == "/" || target == fs::path(getenv("HOME")))
        return false;
  
  try {
    if(fs::is_directory(target)){
      fs::remove_all(target);
    }
    else {
      fs::remove(target);
    return true;
    }
    loadDirectory();
    return true;
  }
  catch(const std::exception& e) {
    return false;
  }
}

int FileManager::showDeleteConfirm() {
    clear();
    mvprintw(5,5,"Delete this item?");
    mvprintw(7,7,"y = Yes");
    mvprintw(8,7,"n = No");
    refresh();

  int ch;
    while(true) {
       ch = getch();
   if(ch == 'y' || ch == 'Y') return 1;
                                                        if(ch == 'n' || ch == 'N') return 0;
                                                            }
}


void FileManager::openFileWithEditor(const std::string& filePath) {
clear();
    mvprintw(0, 0, "Open with:");
    mvprintw(2, 2, "1. nano");
    mvprintw(3, 2, "2. nvim");
    mvprintw(5, 2, "Press 1 / 2 or q to cancel");
    refresh();

    int ch = getch();

    endwin(); // stop ncurses before launching editor

    std::string cmd;
    if (ch == '1'){
     cmd = "nano \"" + filePath + "\"";
      if(!commandExists("nano")){
        std::cout << "No editor found! Install nano or neovim.\n";
        std::cout << "Press Enter to return...";
         std::cin.get();
      };

    }else if (ch == '2'){
     cmd = "nvim \"" + filePath + "\"";
     if(!commandExists("nvim")){
       std::cout << "No editor found! Install nano or neovim.\n";
       std::cout << "Press Enter to return...";
       std::cin.get();
     };

    } else{ return; }

    system(cmd.c_str());

    // back to ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);
}


FileManager::OpenResult FileManager::goToSelected() {
  if (items.empty()) return OpenResult::Nothing;

  if (isDirectory(selectedIndex)) {
    currentPath /= items[selectedIndex].path().filename();
      loadDirectory();
      return OpenResult::OpenedDirectory;
      } else {
      return OpenResult::OpenedFile;
    }
  }

void FileManager::goBack() {
    if (currentPath.has_parent_path()) {
        currentPath = currentPath.parent_path();
        loadDirectory();
    }
}
