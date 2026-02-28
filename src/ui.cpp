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

void UI::openFileWithEditor(const std::string& filePath) {
    clear();
    mvprintw(1, 2, "Open with:");
    mvprintw(2, 2, "1. nano");
    mvprintw(3, 2, "2. nvim");
    mvprintw(5, 2, "Press 1 / 2 or q to cancel");
    refresh();

    int ch = getch();

    endwin(); // stop ncurses before launching editor

    std::string cmd;
    if (ch == '1') cmd = "nano \"" + filePath + "\"";
    else if (ch == '2') cmd = "nvim \"" + filePath + "\"";
    else return;

    system(cmd.c_str());

    // back to ncurses
    initscr();
    noecho();
    cbreak();
    keypad(stdscr, true);
    curs_set(0);
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
          move(i + 2, 0);
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
    mvprintw(height - 2, 2, "[ ↑↓ ] Navigate | [ Enter ] Open | [ Q ] Quit ");
attroff(A_REVERSE);
    refresh();
}

int UI::handleInput() {
    return getch();
}

void UI::close() {
    endwin();
}
