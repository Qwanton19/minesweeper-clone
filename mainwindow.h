/*
 * Author: Quinton McCrory
 * Description: Header file for the MainWindow class, which manages the Minesweeper UI.
 * Date: 6/2/2025
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "minefield.h"

/*
 * Class: MainWindow
 * Description: Represents the main application window for the Minesweeper game.
 */
class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    /* Constructor */
    MainWindow(QWidget *parent = nullptr);

    /* Restarts the game by resetting the minefield */
    void restartGame();

private:
    MineField *mineField; // Pointer to the MineField widget
};

#endif // MAINWINDOW_H
