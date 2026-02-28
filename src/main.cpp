#include "file_manager.h"
#include "ui.h"
#include <ncurses.h>

int main() {
  bool inEditorPrompt = false;
    FileManager fm;
    UI ui;

    ui.init();

    while (true) {
       
        if (!inEditorPrompt) {
        clear();
        ui.draw(fm.getItems(), fm.selectedIndex,fm.offset, fm.getCurrentPath().string());
        refresh();
        }
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
          inEditorPrompt = true;
            auto result = fm.goToSelected();
            if(result == FileManager::OpenResult::OpenedFile){
              fm.openFileWithEditor(fm.getItems()[fm.selectedIndex].path().string());
              inEditorPrompt = false;
              std::string file_path = fm.getItems()[fm.selectedIndex].path().string();
              fm.loadDirectory();
            }

        }


        if (ch == KEY_BACKSPACE || ch == 127)
            fm.goBack();
    }

    ui.close();
    return 0;
}
