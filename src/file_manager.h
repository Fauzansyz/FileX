#ifdef FILE_MANAGER_H
#define FILE_MANAGER_H

#include <filesystem>
#include <vector>

namespace fs = std::filesystem;

class FileManager
{
public:
  FileManager();
  void loadDirectory();
  void goToSelected();
  void goBack();

  std::vector<fs::directory_entry> getItems();
  fs::path getCurrentPath();

  bool isDirectory(int index);

  int selectedIndex = 0;
  private:
     std::path currentPath;
     std::vector<fs::directory_entry> items;
};

#endif // 
