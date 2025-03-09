#include "definition.h"



void Keycontrol() {
    while (running) {

        SetConsoleColor(7, 0);

        // Get the length of the current line in the vector
        height = linesVector[y].length();

        // Capture the key pressed by the user
        key = _getch();

        // Handle unwanted initial inputs
        DelFirstUnwanted();

        // Handle the ESC key for saving and exiting
        if (key == 27) {
            SetConsoleColor(7, 0);
            // Display save confirmation dialog
            int choice = 0;
            const char* options[] = { "Yes", "No" };
            int numOptions = sizeof(options) / sizeof(options[0]);
            setCursorVisibility(false);
            bool run = true;

            while (run) {
                system("cls");
                cout << "Do you want to save changes?" << endl << endl;
                for (int i = 0; i < numOptions; i++) {
                    if (i == choice) {
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);
                        cout << "> " << options[i] << endl;
                        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
                    }
                    else {
                        cout << "  " << options[i] << endl;
                    }
                }
                switch (_getch()) {
                case 72:  // Up arrow
                    choice = (choice - 1 + numOptions) % numOptions;
                    break;
                case 80:  // Down arrow
                    choice = (choice + 1) % numOptions;
                    break;
                case 13:  // Enter key
                    if (choice == 0) {
                        Update(address);  // Save the file
                        system("cls");
                        cout << "FILE SAVED AND CLOSED SUCCESSFULLY. Press any key to return to the menu.";
                        run = false;
                        running = false;

                    }
                    if (choice == 1) {
                        run = false;
                        system("cls");
                        displayBoard();
                        gotoxy(x, y);
                       
                    }
                    break;
                }
                setCursorVisibility(true);
            }
            continue;
        }

        // Refresh the display if selection mode was pressed
        if (SelectmodePressed) {
            DisplayRefresh();
            SelectmodePressed = false;
        }


        if (GetAsyncKeyState(VK_F5)) //refresh
        {
            system("cls");
            displayBoard();

            continue;

        }
        // Check if Shift keys are pressed to activate selection mode
        if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT)) {
            SelectMode();  // Activate selection mode
            SelectmodePressed = true;
            continue;  // Skip further processing for this loop
        }

        // Check for Ctrl key combinations for various operations
        if (GetAsyncKeyState(VK_CONTROL)) {
            if (GetAsyncKeyState('V')) {  // Paste operation
                if (press) {
                    if (pastemode == 1) {  // Paste single-line text
                        SetConsoleColor(7, 0);
                        for (int i = 0; i < selected.length(); i++) {
                            linesVector[y].insert(linesVector[y].begin() + x, selected[i]);
                            x++;
                        }
                        ClearLine(y);  // Clear the current line on the console
                        gotoxy(0, y);  // Reset cursor position
                        for (int i = 0; i < linesVector[y].size(); i++) {
                            cout << linesVector[y][i];
                        }
                        gotoxy(x, y);

                    }
                    else if (pastemode == 2) {  // Paste multi-line text
                        if (!cutVector.empty()) {
                            for (int i = 0; i < cutVector.size(); i++) {
                                if (y + i < linesVector.size()) {
                                    linesVector[y + i].insert(x, cutVector[i]);
                                }
                                else {
                                    linesVector.push_back(cutVector[i]);
                                }
                                x = 0;
                            }
                        }
                        for (int i = 0; i < linesVector.size(); i++) {
                            ClearLine(i);
                            gotoxy(0, i);
                            cout << linesVector[i];
                        }
                        gotoxy(x + cutVector.back().size(), y + cutVector.size() - 1);
                    }
                }

            }


            if (GetAsyncKeyState('C')) {
                pastemode = 1;  // Copy mode

            }


           

            if (GetAsyncKeyState('X')) {
                if (press) {
                    if (crtlA) {

                        fill(linesVector.begin(), linesVector.end(), 0);
                        SetConsoleColor(7, 0);
                        system("cls");
                        displayBoard();

                        crtlA = false;
                        continue;
                    }


                    Cut();

                    DisplayRefresh();
                    pastemode = 2;




                }

            }


            if (GetAsyncKeyState('F')) {
                Searching();  // Activate search mode
            }

            if (GetAsyncKeyState('A')) {  // Select all text
                CrtlA();
                SetConsoleColor(7, 0);
                gotoxy(xEndPos, yEndPos);
                crtlA = true;
                SelectmodePressed = true;
            }

            continue;  // Skip further processing for this loop
            press = false;
        }


        // Handle navigation keys (e.g., arrow keys)
        if (key == 224) {
            int ch = _getch();
            if (ch == 75) {  // Left arrow
                if (x == 0 && y != 0) {
                    y--;
                    x = linesVector[y].size();
                    gotoxy(x, y);
                }
                else if (x != 0) {
                    x--;
                    gotoxy(x, y);
                }
            }
            else if (ch == 77) {  // Right arrow
                if (linesVector[y].size() == x && y != linesVector.size() - 1) {
                    x = 0;
                    y++;
                    gotoxy(0, y);
                }
                else if (linesVector[y].size() != x) {
                    x++;
                    gotoxy(x, y);
                }
            }
            else if (ch == 72) {  // Up arrow
                if (y != 0) {
                    y--;
                    x = min(x, (int)linesVector[y].size());
                    gotoxy(x, y);
                }
            }
            else if (ch == 80) {  // Down arrow
                if (y < linesVector.size() - 1) {
                    y++;
                    x = min(x, (int)linesVector[y].size());
                    gotoxy(x, y);
                }
            }
        }

        // Handle backspace key
        if (key == 8) {
            if (x > 0) {
                linesVector[y].erase(linesVector[y].begin() + (x - 1));
                x--;
                ClearLine(y);
                gotoxy(0, y);
                for (int i = 0; i < linesVector[y].size(); i++) {
                    cout << linesVector[y][i];
                }
            }
            else if (x == 0 && y != 0) {
                y--;
                x = linesVector[y].size();
                linesVector[y] += linesVector[y + 1];
                linesVector.erase(linesVector.begin() + y + 1);
                system("cls");
                displayBoard();
            }
            gotoxy(x, y);
        }

        // Handle Enter key for new line
        if (key == 13) {
            for (int i = x; i < linesVector[y].length(); i++) {
                enteredLineText += linesVector[y][i];
                linesVector[y][i] = ' ';
            }
            linesVector.insert(linesVector.begin() + y + 1, enteredLineText);
            enteredLineText.clear();
            system("cls");
            displayBoard();
            y++;
            x = 0;
            gotoxy(x, y);
        }

        // Handle regular character input
        if (key != 224 && key != 13 && key != 8 && !firsttime) {
            Write(key);
        }

        firsttime = false;
        press = true;
    }
}
