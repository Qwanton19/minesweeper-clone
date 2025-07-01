/*
 * Author: Quinton McCrory
 * Description: Header file for the MineField class, which manages the Minesweeper game logic.
 * Date: 6/2/2025
 */

#ifndef MINEFIELD_H
#define MINEFIELD_H

#include <QWidget>
#include <QGridLayout>
#include <QSet>
#include "cellbutton.h"

/*
 * Class: MineField
 * Description: Represents the grid of Minesweeper, handles mine generation and gameplay mechanics.
 */
class MineField : public QWidget {
    Q_OBJECT
public:
    /* Constructor */
    MineField(QWidget *parent = nullptr);

    /* Resets the game field */
    void resetField();

    /* Reveals empty cells recursively */
    void revealEmptyCells(int row, int col);

    /* Checks if the player has won */
    bool checkWin();

private:
    QGridLayout *gridLayout; // Grid layout for the game field
    CellButton *cells[16][30]; // Grid of buttons representing the cells
    bool mines[16][30]; // Tracks mine locations
    int counts[16][30]; // Stores number of adjacent mines for each cell

    /* Generates mines randomly */
    void generateMines();

    /* Calculates the number of adjacent mines */
    void calculateCounts();

    /* Flood fill algorithm for revealing empty spaces */
    void floodFill(int row, int col, QSet<QPair<int, int>> &visited);
};

#endif // MINEFIELD_H
