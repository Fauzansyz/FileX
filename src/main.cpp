#include "file_manager.h"
#include "ui.h"
#include <ncurses.h>

int main() {
    FileManager fm;
    UI ui;

    ui.init();

    while (true) {
        ui.draw(fm.getItems(), fm.selectedIndex,fm.offset, fm.getCurrentPath().string());
        int ch = ui.handleInput();

        if (ch == 'q' || ch == 'Q') break;

        if (ch == KEY_UP && fm.selectedIndex > 0)
            fm.selectedIndex--;

        if (ch == KEY_DOWN && fm.selectedIndex < fm.getItems().size() - 1)
            fm.selectedIndex++;

        if (ch == 10)
            fm.goToSelected();

        if (ch == KEY_BACKSPACE || ch == 127)
            fm.goBack();
    }

    ui.close();
    return 0;
}
