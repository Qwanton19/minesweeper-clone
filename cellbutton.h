/*
 * Author: Quinton McCrory
 * Description: Header file for the CellButton class, representing an individual cell in the Minesweeper grid.
 * Date: 6/2/2025
 */

#ifndef CELLBUTTON_H
#define CELLBUTTON_H

#include <QPushButton>
#include <QIcon>

/*
 * Class: CellButton
 * Description: Represents an individual cell button in the Minesweeper game.
 */
class CellButton : public QPushButton {
    Q_OBJECT
public:
    /* Constructor */
    CellButton(int row, int col, QWidget *parent = nullptr);

    /* Resets the button to its initial state */
    void reset();

    /* Reveals the button, displaying either a mine or a number */
    void reveal(int count);

    /* Marks the button as containing a mine */
    void setMine();

    /* Sets the button to display a flag icon */
    void setFlag();

    /* Cycles through right-click states: flag, question mark, and blank */
    void cycleRightClick();

    /* Sets the button as a revealed mine (when the player loses) */
    void setRevealedMine();

    /* Returns whether the button is still hidden */
    bool isHidden() const;

private:
    int row, col;      // Cell coordinates
    bool isMine;       // Indicates if the cell contains a mine
    int rightClickState; // 0 = normal, 1 = flagged, 2 = question mark
};

#endif // CELLBUTTON_H
