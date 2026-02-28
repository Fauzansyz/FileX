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

void UI::draw(const std::vector<fs::directory_entry>& items,
              int selected,
              const std::string& path) {

    clear();
    box(stdscr, 0, 0);
    attron(COLOR_PAIR(1));
    mvprintw(1, 2, "FileX - File manager");
    attroff(COLOR_PAIR(1));

    mvprintw(2, 2, "Path: %s", path.c_str());
    mvprintw(3, 2, "------------------");

    for (int i = 0; i < items.size(); i++) {
        std::string name = items[i].path().filename().string();

        if (i == selected) attron(A_REVERSE);
        if (items[i].is_directory()){

            attron(COLOR_PAIR(2));
            mvprintw(i + 3, 4, "[DIR] %s", name.c_str());
            attron(COLOR_PAIR(2));
        } else{
          attron(COLOR_PAIR(3));
            mvprintw(i + 3, 4, "      %s", name.c_str());
            attron(COLOR_PAIR(3));
        }

        if (i == selected) attroff(A_REVERSE);
    }
    int h, w;
    getmaxyx(stdscr, h, w);
    attron(A_REVERSE);
    mvprintw(h-1, 0, " ↑↓ Navigate | Enter Open | Q Quit ");
attroff(A_REVERSE);
    refresh();
}

int UI::handleInput() {
    return getch();
}

void UI::close() {
    endwin();
}
