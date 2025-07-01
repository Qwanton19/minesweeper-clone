/*
 * Author: Quinton McCrory
 * Description: File for MineField class. Handles game logic, mine placement,
 *              cell revealing, win condition checks, and game-over logic.
 * Date: 2/6/2025
 */

#include "minefield.h"
#include <QRandomGenerator>
#include <QMessageBox>
#include <QApplication>

/*
 * Constructor: MineField
 * Initializes the Minesweeper game grid by setting up a grid layout and connecting each cell button.
 *
 * Parameters:
 *  - parent: Pointer to the parent widget (default is null).
 */
MineField::MineField(QWidget *parent) : QWidget(parent) {
    gridLayout = new QGridLayout(this);
    gridLayout->setSpacing(0);
    setLayout(gridLayout);

    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 30; col++) {
            cells[row][col] = new CellButton(row, col, this);
            gridLayout->addWidget(cells[row][col], row, col);
            connect(cells[row][col], &CellButton::clicked, [=]() { revealEmptyCells(row, col); });
        }
    }
    resetField();
}

/*
 * Function: resetField
 * Resets the game board by generating new mines and resetting all cells.
 */
void MineField::resetField() {
    generateMines();
    calculateCounts();
    for (int row = 0; row < 16; row++) {
        for (int col = 0; col < 30; col++) {
            cells[row][col]->reset();
            if (mines[row][col])
                cells[row][col]->setMine();
        }
    }
}

/*
 * Function: generateMines
 * Randomly places mines in the game grid. Ensures that there are exactly 99 mines.
 */
void MineField::generateMines() {
    memset(mines, 0, sizeof(mines)); // Initialize mine locations to false
    int count = 0;
    while (count < 99) {
        int r = QRandomGenerator::global()->bounded(16);
        int c = QRandomGenerator::global()->bounded(30);
        if (!mines[r][c]) {
            mines[r][c] = true;
            count++;
        }
    }
}

/*
 * Function: calculateCounts
 * Calculates the number of adjacent mines for each cell that is not a mine.
 */
void MineField::calculateCounts() {
    memset(counts, 0, sizeof(counts)); // Initialize mine counts to 0
    for (int r = 0; r < 16; r++) {
        for (int c = 0; c < 30; c++) {
            if (mines[r][c]) continue;
            for (int dr = -1; dr <= 1; dr++) {
                for (int dc = -1; dc <= 1; dc++) {
                    int nr = r + dr, nc = c + dc;
                    if (nr >= 0 && nr < 16 && nc >= 0 && nc < 30 && mines[nr][nc])
                        counts[r][c]++;
                }
            }
        }
    }
}

/*
 * Function: revealEmptyCells
 * Handles clicking logic; reveals an empty cell and starts flood fill if necessary.
 * If a mine is clicked, displays Game Over dialog with options to restart or exit.
 *
 * Parameters:
 *  - row: Row index of the clicked cell.
 *  - col: Column index of the clicked cell.
 */
void MineField::revealEmptyCells(int row, int col) {
    if (mines[row][col]) {
        cells[row][col]->setRevealedMine();
        int response = QMessageBox::critical(this, "Game Over", "You hit a mine!", QMessageBox::Retry | QMessageBox::Close);
        if (response == QMessageBox::Retry) {
            resetField();
        } else {
            QApplication::quit();
        }
        return;
    }

    QSet<QPair<int, int>> visited; // Keeps track of visited cells
    floodFill(row, col, visited);

    if (checkWin()) {
        int response = QMessageBox::information(this, "Congratulations!", "You won the game!", QMessageBox::Retry | QMessageBox::Close);
        if (response == QMessageBox::Retry) {
            resetField();
        } else {
            QApplication::quit();
        }
    }
}

/*
 * Function: floodFill
 * Uses recursion to reveal all adjacent empty spaces when an empty cell is clicked.
 *
 * Parameters:
 *  - row: Row index of the cell being processed.
 *  - col: Column index of the cell being processed.
 *  - visited: Set of visited cells to prevent infinite recursion.
 */
void MineField::floodFill(int row, int col, QSet<QPair<int, int>> &visited) {
    if (row < 0 || row >= 16 || col < 0 || col >= 30 || visited.contains({row, col}) || !cells[row][col]->isEnabled())
        return;

    visited.insert({row, col});
    cells[row][col]->reveal(counts[row][col]);

    if (counts[row][col] == 0) { // If the cell has no adjacent mines, continue revealing neighbors
        for (int dr = -1; dr <= 1; dr++) {
            for (int dc = -1; dc <= 1; dc++) {
                if (dr != 0 || dc != 0)
                    floodFill(row + dr, col + dc, visited);
            }
        }
    }
}

/*
 * Function: checkWin
 * Checks if all non-mine cells have been revealed, indicating the player has won.
 *
 * Returns:
 *  - true if all non-mine cells are revealed, false otherwise.
 */
bool MineField::checkWin() {
    for (int r = 0; r < 16; r++) {
        for (int c = 0; c < 30; c++) {
            if (!mines[r][c] && cells[r][c]->isEnabled()) {
                return false;
            }
        }
    }
    return true;
}
