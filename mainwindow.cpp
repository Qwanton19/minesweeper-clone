/*
 * Author: Quinton McCrory
 * Description: File for MainWindow class, which serves as the main interface for the Minesweeper game.
 * Date: 2/7/2025
 */

#include "mainwindow.h"
#include <QVBoxLayout>
#include <QMessageBox>

/*
 * Constructor: MainWindow
 * Initializes the Minesweeper main window, setting up the game field.
 *
 * Parameters:
 *  - parent: Pointer to the parent widget (default is null).
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    mineField = new MineField(this);
    setCentralWidget(mineField);  // Set the minefield as the central widget of the main window
    setWindowTitle("Minesweeper"); // Set the window title
    setFixedSize(600, 400);       // Set fixed size of the window
}

/*
 * Function: restartGame
 * Resets the minefield, starting a new game.
 */
void MainWindow::restartGame() {
    mineField->resetField();
}
