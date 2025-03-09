
#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>

using namespace std;



extern bool firstTime;  // Used to check if it's the first time the program is run
extern bool specialKey;  // Indicates if a special key (like Shift or Control) is pressed
extern bool running;  // Indicates if the program is still running
extern bool press;  // Indicates if a key is being pressed
extern bool firsttime;  // A flag to simulate the behavior during the initial setup or configuration
extern bool SelectmodePressed;  // Indicates if selection mode has been activated
extern bool mainRun;  // Indicates if the program is in its main running state
extern bool firstLoad;  // Used to check if it's the first time loading a file or data
extern bool crtlA;  // Flag for simulating the behavior of Ctrl+A (select all)
extern bool openCorrectly; //check if the file opened correctly
extern int width;  // Width of the console or screen (could refer to number of lines or console size)
extern int height;  // Height of the console or screen
extern int x;  // Horizontal position of the cursor
extern int y;  // Vertical position of the cursor
extern int yStartPos;  // Starting position of the selection (vertical)
extern int XStartPos;  // Starting position of the selection (horizontal)
extern int yEndPos;  // Ending position of the selection (vertical)
extern int xEndPos;  // Ending position of the selection (horizontal)
extern int key;  // Stores the keycode of the pressed key for processing
extern int pastemode;  // Stores the state of cut/paste mode (copy/cut)


extern string selected;  // Text selected by the user in selection mode
extern string searchString;  // The string entered by the user to search for
extern string address;  // The path and name of the currently edited file
extern string enteredLineText;  // The text being typed or entered on a line
extern string savedSelect;  // Stores the selected text for copy or cut operations
extern string cuttext;  // The text to be used for cutting or copying
extern string startMode;  // The starting mode of the program (like open file or new file)
extern vector<string> linesVector;  // Stores the content of the file as a list of lines
extern vector<string> cutVector;  // Stores the cut text for later pasting operations



extern void Open(string address);  // Opens a file and loads its contents into `linesVector`
extern void displayBoard();  // Displays the content of the file or current edits on the console
extern void gotoxy(int x, int y);  // Sets the cursor position at (x, y) in the console
extern void GetAdress();  // Prompts the user to input the file path for opening or saving
extern void InitialSetting();  // Performs the initial setup of the program like opening or creating a new file
extern void Update(string address);  // Saves changes to the file and updates its contents
extern void SetConsoleColor(int textColor, int bgColor);  // Changes the text and background color of the console
extern void DisplayRefresh();  // Refreshes the screen to display the updated content or changes
extern void Write(char key);  // Writes a character at the current cursor position on the console
extern void Cut();  // Cuts or deletes the selected text
extern void SelectMode();  // Activates the selection mode to allow text selection
extern void Search(string searchString);  // Searches for the given string in the content
extern void setCursorVisibility(bool visible);  // Sets whether the cursor is visible or not
extern void menu();  // Displays the main menu of the program and handles user input
extern void ClearLine(int y);  // Clears the line at the specified vertical position (y) on the console
extern void Searching();  // Handles the search operation and displays the search results
extern void CrtlA();  // Selects all text on the screen or in the file (simulates Ctrl+A)
extern void Help();  // Displays the help and instructions for using keyboard shortcuts
extern void DelFirstUnwanted();  // Deletes the first unwanted input (perhaps for initial setup or cleanup)
extern void Keycontrol();  // Manages user keypress inputs for various operations like typing, selecting, cutting, copying, etc.
extern void Resetprogram(); // valriabels reset to the default (for restarting the program)