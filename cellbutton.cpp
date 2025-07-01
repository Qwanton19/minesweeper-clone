/*
 * Author: Quinton McCrory
 * Description: File for CellButton class, representing an individual cell in the Minesweeper grid.
 *              Handles cell states, right-click behavior, and mine display.
 * Date: 2/6/2025
 */

#include "cellbutton.h"
#include <QPixmap>

/*
 * Constructor: CellButton
 * Initializes a cell button with default settings.
 *
 * Parameters:
 *  - r: Row index of the cell.
 *  - c: Column index of the cell.
 *  - parent: Pointer to the parent widget (default is nullptr).
 */
CellButton::CellButton(int r, int c, QWidget *parent)
    : QPushButton(parent), row(r), col(c), isMine(false), rightClickState(0) {
    setFixedSize(20, 20);  // Set button size
    reset();  // Initialize the button
    setContextMenuPolicy(Qt::CustomContextMenu);  // Enable custom right-click behavior
    connect(this, &QPushButton::customContextMenuRequested, this, &CellButton::cycleRightClick);
}

/*
 * Function: reset
 * Resets the button to its initial state (hidden, no mine, default tile).
 */
void CellButton::reset() {
    isMine = false;  // Clear mine status
    rightClickState = 0;  // Reset right-click state
    setEnabled(true);  // Enable button interactions
    setIcon(QIcon(QPixmap(":/images/images/tile.png")));  // Set default tile icon
}

/*
 * Function: reveal
 * Reveals the button by displaying a number if it has adjacent mines, or an empty space.
 * If the cell contains a mine, it triggers the loss condition.
 *
 * Parameters:
 *  - count: Number of mines adjacent to this cell.
 */
void CellButton::reveal(int count) {
    setEnabled(false);  // Disable further interactions

    if (isMine) {
        setRevealedMine();  // Show mine if this is a mine cell
    } else {
        QString imgPath;
        switch (count) {
        case 1: imgPath = ":/images/images/one.png"; break;
        case 2: imgPath = ":/images/images/two.png"; break;
        case 3: imgPath = ":/images/images/three.png"; break;
        case 4: imgPath = ":/images/images/four.png"; break;
        case 5: imgPath = ":/images/images/five.png"; break;
        case 6: imgPath = ":/images/images/six.png"; break;
        case 7: imgPath = ":/images/images/seven.png"; break;
        case 8: imgPath = ":/images/images/eight.png"; break;
        default: imgPath = ""; break;
        }

        if (!imgPath.isEmpty()) {
            setIcon(QIcon(QPixmap(imgPath).scaled(20, 20, Qt::KeepAspectRatio, Qt::SmoothTransformation)));
        } else {
            setIcon(QIcon());  // Keep it blank if count is 0 (no adjacent mines)
        }
    }
}

/*
 * Function: setMine
 * Marks this cell as a mine.
 */
void CellButton::setMine() {
    isMine = true;
}

/*
 * Function: setFlag
 * Marks the cell with a flag icon to indicate a suspected mine.
 */
void CellButton::setFlag() {
    setIcon(QIcon(QPixmap(":/images/images/flag.png")));
}

/*
 * Function: setRevealedMine
 * Displays the revealed mine icon when a mine is clicked.
 */
void CellButton::setRevealedMine() {
    setIcon(QIcon(QPixmap(":/images/images/redbomb.png")));
}

/*
 * Function: cycleRightClick
 * Cycles through right-click states: flag, question mark, and back to default.
 * Prevents changes on already revealed cells.
 */
void CellButton::cycleRightClick() {
    if (!isEnabled()) return;  // Do not allow right-clicking on revealed cells

    rightClickState = (rightClickState + 1) % 3;  // Cycle through 0 (default), 1 (flag), 2 (question mark)

    switch (rightClickState) {
    case 0: setIcon(QIcon(QPixmap(":/images/images/tile.png"))); break;  // Default tile
    case 1: setIcon(QIcon(QPixmap(":/images/images/flag.png"))); break;  // Flagged cell
    case 2: setIcon(QIcon(QPixmap(":/images/images/question.png"))); break;  // Question mark
    }
}

/*
 * Function: isHidden
 * Returns whether the cell is still hidden (not revealed).
 *
 * Returns:
 *  - true if the cell has not been revealed, false otherwise.
 */
bool CellButton::isHidden() const {
    return !isEnabled();
}
