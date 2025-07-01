/*
 * Author: Quinton McCrory
 * Description: Actual application for the Minesweeper project.
 * Date: 2/6/2025
 */

#include <QApplication>
#include "mainwindow.h"

/*
 * Function: main
 * Entry point of the application. Initializes the QApplication and the MainWindow.
 *
 * Parameters:
 *  - argc: Number of command-line arguments.
 *  - argv: Array of command-line arguments.
 *
 * Returns:
 *  - Application exit status.
 */
int main(int argc, char *argv[]) {
    QApplication app(argc, argv); // Create QApplication instance
    MainWindow window;            // Create the main window
    window.show();                // Display the main window
    return app.exec();             // Start the event loop
}
