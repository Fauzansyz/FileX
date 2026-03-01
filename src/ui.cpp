#include "ui.h"
#include <ncurses.h>

void UI::init() {
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);
    init_pair(4, COLOR_BLACK, COLOR_WHITE);
    init_pair(5, COLOR_BLACK, COLOR_CYAN);

}


void UI::draw(const std::vector<fs::directory_entry>& items,int selected, int offset,const std::string& path) {

    clear();
    int height, width;
    getmaxyx(stdscr, height, width);

    int headerHeight = 4;
    int footerHeight = 2;

    int visibleRows = height - headerHeight - footerHeight;
    if (visibleRows < 1) visibleRows = 1;

    box(stdscr, 0, 0);
    attron(COLOR_PAIR(1));
    mvprintw(1, 2, "FileX - File manager");
    mvprintw(1, width - 6, "v1.0");
   // mvprintw(2, width - 11, "----------------");
    attroff(COLOR_PAIR(1));

    mvprintw(2, 2, "Path: %s", path.c_str());
    mvprintw(3, 2, "------------------");

    if (selected < offset){
      offset = selected;
    }

    if (selected >= offset + visibleRows){
      offset = selected - visibleRows + 1;
    }

    for (int i = 0; i < visibleRows; i++) {
          move(i + headerHeight, 0);
              clrtoeol();
    }

    for (int i = 0; i < visibleRows; i++) {
      int index = i + offset;
       if (index >= items.size()) break;
              
        std::string name = items[index].path().filename().string();

        if (index == selected) attron(A_REVERSE);
        if (items[index].is_directory()){

            attron(COLOR_PAIR(2));
            mvprintw(i + headerHeight, 2, "[DIR] %s", name.c_str());
            attron(COLOR_PAIR(2));
        } else{
          attron(COLOR_PAIR(3));
            mvprintw(i + headerHeight, 2, "      %s", name.c_str());
            attron(COLOR_PAIR(3));
        }

        if (index == selected) attroff(A_REVERSE);
    }
    int h, w;
    getmaxyx(stdscr, h, w);
    attron(A_REVERSE);
    mvprintw(height - 2, 2, "[ Up/Down ] Navigate | [ Enter ] Open | [ Q ] Quit ");
attroff(A_REVERSE);
    refresh();
}

void UI::showHelp() {
    clear();

    mvprintw(1, 2, "NeoFM - Help");
    mvprintw(2, 2, "-----------------------------");

    mvprintw(4, 2, "Navigation:");
    mvprintw(5, 4, "Up / Down     : Move selection");
    mvprintw(6, 4, "Enter         : Open folder / file");
    mvprintw(7, 4, "Backspace     : Go back");

    mvprintw(9, 2, "File Actions:");
    mvprintw(10, 4, "d             : Delete file/folder");
    mvprintw(11, 4, "h or ?        : Show help");
    mvprintw(12, 4, "q             : Quit");

    mvprintw(14, 2, "Editors:");
    mvprintw(15, 4, "1             : Open with Neovim");
    mvprintw(16, 4, "2             : Open with Nano");

    mvprintw(18, 2, "Press any key to return...");
    refresh();

    getch(); // pause sampai user tekan tombol
}



int UI::handleInput() {
    return getch();
}

void UI::close() {
    endwin();
}
