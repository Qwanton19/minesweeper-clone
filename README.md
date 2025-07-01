# 💣 minesweeper-clone

A classic Minesweeper game with a 16x30 grid and 99 mines, developed for **CS3377** using C++ and the Qt Framework.

This project is a fully functional implementation of the classic puzzle game. The objective is to clear a rectangular board containing hidden "mines" without detonating any of them.


## 🎮 Gameplay & Features

This is a classic Minesweeper challenge on a **16x30 grid** with **99 mines**. The goal is to clear the board without hitting a bomb.

*   **`Left-click`**: Reveals a cell. If it's a number, it's a clue to how many mines are adjacent. If it's empty, it will auto-clear surrounding empty cells. If it's a bomb, the game is lost.
*   **`Right-click`**: Cycles through marking a cell with a flag (`🚩`), a question mark (`❓`), or clearing the mark.
*   **Win the Game 🏆**: You win by revealing every cell on the board that does **not** contain a mine.

## 🛠️ Installation & Compilation

### Prerequisites
*   **Qt Framework:** [Qt 5 or Qt 6](https://www.qt.io/download) (Qt Creator is recommended).
*   **C++ Compiler:** A compiler that supports C++11 or newer (e.g., GCC, Clang, MSVC).

1.  Open **Qt Creator** and use `File > Open File or Project...` to load the `Minesweeper.pro` file.
2.  Click the **Build** button, then the **Run** button.
