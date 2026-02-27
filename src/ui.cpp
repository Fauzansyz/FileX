#include "ui.h"
#include <ncurses.h>

void UI::init() {
      initscr();
      noecho();
      cbreak();
      keypad(stdscr, TRUE);
}

voud UI::draw(const std::vector<fs::directory_entry> items, int selected, const std::string& path) {
  clear();
  mvprintw(0, 2 "NeoFM - %s", path.c_str());
   mvprintw(1, 2, "[Enter] Open  [Backspace] Back  [Q] Quit");

   for(int i = 0; i < items.size(); i++){
      std::string name = items[i].path().filename().string();
      if(i == selected) attron(A_REVERSE);
      if(items[i].is_directory()) mvprintw i + 2, 2, "[ DIR ] %s", name.c_str();
     else {
       mvprintw(i + 2, 2, " %s", name.c_str());
       attroff(A_REVERSE);
     }
     if(i == selected){
       attroff(A_REVERSE);
     }
     refresh(); 
   }

}

int UI::handleInput() {
  return getch();
}

void UI::close() {
  endwin();
}
