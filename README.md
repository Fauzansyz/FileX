# 📁 FileX — Terminal File Manager (C++ & ncurses)

FileX is a terminal-based file manager (TUI) built using **C++** and **ncurses**.  
It allows you to navigate directories directly from the terminal with an interactive UI (highlight + scroll).

> Simple. Fast. Powerful. 😎

---

## ✨ Features
- 📂 Directory navigation (Enter to open folder)
- 🔙 Go back to parent directory (Backspace)
- 🎯 Highlight cursor for selected file / folder
- 🖱️ Automatic scrolling when files exceed screen height
- 📍 Display current path
- 🧠 Responsive UI based on terminal size
- ⌨️ Full keyboard control

---

## 🕹️ Controls

| Key | Action |
|-----|--------|
| `↑` / `↓` | Move selection |
| `Enter` | Open directory |
| `Backspace` | Go back |
| `q` | Quit application |

---

## 🛠️ Requirements

- Linux / WSL / Termux
- g++
- ncurses library

Install ncurses (Linux):
```bash
sudo apt install libncurses-dev
```

### 🚀 Installation & Build

```bash
git clone https://github.com/Fauzansyz/fileX.git
cd fileX
g++ -o fileX fileX.cpp -lncurses
./fileX

```

### 📂 Project Structure

```bash
.
├── src 
├── README.md
└── filex
```

### 🧠 How It Works (simple)

- The program reads directory contents using std::filesystem

- UI is redrawn on every key input
- Highlight is implemented using A_REVERSE
- Scrolling is controlled with offset and selectedIndex

- Layout is divided into:
   - Header
   - File list (scrollable)
   - Footer (controls)

---

### ⚠️ Known Issues

- UI may shift when terminal size changes (e.g. mobile keyboard appears)
- File operations (delete/copy) are not fully implemented yet


### 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.


### 💬 Author

Made with ☕ by Fauzan adzma
