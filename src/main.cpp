#include "file_manager.h"
#include "ui.h"
#include <ncurses.h>

void openFileWithEditor(const std::string &filePath) {
    clear();
    mvprintw(0, 0, "Open with:");
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

int main() {
    FileManager fm;
    UI ui;

    ui.init();

    while (true) {
        ui.draw(fm.getItems(), fm.selectedIndex,fm.offset, fm.getCurrentPath().string());
        int ch = ui.handleInput();

        if (ch == 'q' || ch == 'Q') break;

        if (ch == KEY_RESIZE) {
              clear();
        ui.draw(fm.getItems(), fm.selectedIndex,fm.offset, fm.getCurrentPath().string());
              continue;
        }

        if (ch == KEY_UP && fm.selectedIndex > 0)
            fm.selectedIndex--;

        if (ch == KEY_DOWN && fm.selectedIndex < fm.getItems().size() - 1)
            fm.selectedIndex++;

        if (ch == 10){
            auto result = fm.goToSelected();
            if(result == FileManager::OpenResult::OpenedFile){
              std::string file_path = fm.getItems()[fm.selectedIndex].path().string();
              openFileWithEditor(file_path);
              fm.loadDirectory();
            }

        }


        if (ch == KEY_BACKSPACE || ch == 127)
            fm.goBack();
    }

    ui.close();
    return 0;
}
