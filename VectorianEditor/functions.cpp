#include "definition.h"

bool firstTime = true;
bool specialKey = false;
bool running = true;
bool press = true;
bool firsttime = true;
bool SelectmodePressed = false;
bool mainRun = true;
bool firstLoad = true;
bool crtlA = false;
bool openCorrectly = false;
int width = 0;
int height = 0;
int x = 0;
int y = 0;
int yStartPos;
int XStartPos;
int yEndPos;
int xEndPos;
int key;
int pastemode;

string selected = "";
string searchString;
string address;
string enteredLineText;
string savedSelect;
string cuttext;
string startMode;
vector<string> linesVector;
vector<string> cutVector;


// Function to open a file and read its contents into the linesVector
void Open(string address)
{
	// Clear the existing content of linesVector by filling it with zeros
	fill(linesVector.begin(), linesVector.end(), 0);

	fstream myfile;  // Declare a file stream object
	string line;     // Temporary string to hold each line from the file

	// Open the file with the provided address
	myfile.open(address);

	// Check if the file opened successfully
	if (!myfile)
	{
		// If the file could not be opened, display an error message
		cout << "Error opening file!" << endl;
		cout << "WRONG FILE NAME";  // Additional error message
		Sleep(1400);  // Wait for 1.4 seconds before continuing
		openCorrectly = false;  // Set the flag to false as the file did not open correctly
		return;  // Exit the function as the file could not be opened
	}

	// Read the file line by line and store each line in the linesVector
	while (getline(myfile, line))
	{
		linesVector.push_back(line);  // Add the line to the vector
	}

	openCorrectly = true;  // Set the flag to true as the file opened and lines were read successfully

	// Close the file after reading all lines
	myfile.close();
}

// Function to display the contents of linesVector on the console
void displayBoard()
{
	// Iterate over each string (line) in linesVector
	for (const auto& str : linesVector)
	{
		// Iterate over each character in the current string (line)
		for (const auto& ch : str)
		{
			cout << ch;  // Print each character to the console
		}

		// After printing the characters of a line, move to the next line
		cout << endl;
	}


	Help();		// Display the help menu and set the default console color
}

// Function to move the cursor to a specific position (x, y) on the console screen
void gotoxy(int x, int y)
{
	COORD coord;  // Declare a COORD structure to hold the cursor position
	coord.X = x;  // Set the X-coordinate (horizontal position)
	coord.Y = y;  // Set the Y-coordinate (vertical position)

	// Move the console cursor to the specified (x, y) position
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

	return;  // Exit the function (no return value needed)
}


// Function to prompt the user to enter the file address and clear the previous content
void GetAdress()
{
	// Clear the contents of linesVector to ensure no previous data remains
	linesVector.clear();

	// Clear the console screen
	system("cls");

	address = "";  // Reset the address string to an empty string


	// Ask the user to input the file address
	cout << "Enter the file address: ";

	// Read the file address entered by the user
	cin >> address;

	// Append ".txt" to the file address to ensure the correct file extension is used
	address = address + ".txt";
}

// Function to initialize settings based on the selected mode ("openfile" or "newfile")
void InitialSetting() {
	// Check if the program is in the running state
	if (running == true) {

		// If the start mode is "openfile", prompt the user to select a file and open it
		if (startMode == "openfile") {
			// Keep asking for a valid file address until the file is opened correctly
			while (!openCorrectly) {
				GetAdress();  // Prompt the user for the file address
				system("cls");  // Clear the console

				Open(address);  // Attempt to open the file at the given address
			}

		}
		// If the start mode is "newfile", create a new file at the specified address
		else if (startMode == "newfile") {
			x = 0;  // Initialize the x-coordinate for text positioning
			y = 0;  // Initialize the y-coordinate for text positioning
			GetAdress();  // Prompt the user for the file address

			// Create the new file and write an empty space to initialize it
			ofstream file(address);
			file << ' ';
			file.close();

			system("cls");  // Clear the console
			Open(address);  // Open the newly created file
		}

		firstLoad = true;  // Set the firstLoad flag to true, indicating the initialization is complete
		displayBoard();  // Display the contents of the file or the newly created file
		width = linesVector.size();  // Set the width based on the number of lines in the file
		gotoxy(0, 0);  // Move the cursor to the top-left corner of the screen
	}
}

// Function to update the contents of a file with the current data in linesVector
void Update(string address)
{
	// Output the address to the console (for debugging purposes)
	cout << address;

	// Open the input file in read mode (not used in this function)
	fstream myfile;
	myfile.open(address);
	myfile.close();  // Immediately close the file (no further reading is done)

	// Open the file in write mode (to overwrite its contents)
	fstream outFile(address, ios::out);
	if (outFile.is_open())  // Check if the file is successfully opened
	{
		// Iterate over each string (line) in linesVector
		for (const auto& str : linesVector)
		{
			// Iterate over each character in the current string (line)
			for (const auto& ch : str)
			{
				outFile << ch;  // Write each character to the output file
			}
			outFile << endl;  // Add a newline after writing each line
		}
	}

	// Close the output file after writing the contents of linesVector
	outFile.close();
}




// Function to set the text and background color of the console
void SetConsoleColor(int textColor, int bgColor) {
	// Get the handle to the console's output
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set the console text and background color by combining the text and background colors
	// The background color is shifted left by 4 bits to make space for the text color
	SetConsoleTextAttribute(hConsole, (bgColor << 4) | textColor);
}


// Function to refresh the display by clearing the console and redrawing the board
void DisplayRefresh() {
	// Set the console text color to white (7) and background color to black (0)
	SetConsoleColor(7, 0);

	// Clear the console screen
	system("cls");

	// Call the function to display the contents of the board (linesVector)
	displayBoard();

	// Reset the cursor position to the top-left corner of the screen
	x = 0;  // Reset the x-coordinate
	y = 0;  // Reset the y-coordinate

	// Move the cursor to the position (0, 3) on the console screen (3rd row)
	gotoxy(0, 3);
}


// Function to write a character at the current cursor position (x, y) in linesVector
void Write(char key)
{
	// Get the current size of linesVector (number of lines) and the current line length
	int Lsize = linesVector.size();  // Number of lines in the vector
	int LXsize = linesVector[y].size();  // Length of the current line

	// Check if the current line exists within the linesVector
	if (y < Lsize)
	{
		// If the cursor is within the bounds of the current line (x < LXsize)
		if (x < LXsize)
		{
			// Insert the character at the current cursor position (x) in the line
			linesVector[y].insert(linesVector[y].begin() + x, key);
			cout << key;  // Print the character to the console
			x++;  // Move the cursor forward (increment x)
		}
		// If the cursor is at the end of the current line (x >= LXsize)
		else if (x >= LXsize)
		{
			// Add the character to the end of the line
			linesVector[y].push_back(key);
			cout << key;  // Print the character to the console
			x++;  // Move the cursor forward (increment x)
		}
	}
	else
	{
		// If the current line does not exist (y >= Lsize), create a new line
		linesVector.resize(y + 1);  // Resize linesVector to accommodate the new line
		linesVector[y].resize(x, ' ');  // Fill the new line with spaces up to the cursor position (x)
		linesVector[y].insert(linesVector[y].begin() + x, key);  // Insert the character at the current cursor position
		cout << linesVector[y][x];  // Print the character to the console
	}

	// After inserting the character, print the rest of the line from the cursor position onwards
	for (int i = x; i < linesVector[y].size(); i++) {
		cout << linesVector[y][i];  // Print each character in the line after the cursor
	}

	// Move the cursor to the current (x, y) position after the writing is done
	gotoxy(x, y);
}




// Function to cut a selected portion of text from the linesVector and save it in cutVector
void Cut() {
	// Clear any previous cut text stored in cutVector and shrink the capacity to fit the size
	cutVector.clear();
	cutVector.shrink_to_fit();

	// Variable to temporarily store the text that is being cut
	string cuttext = "";

	// If the selected text spans multiple lines (yStartPos < yEndPos)
	if (yStartPos < yEndPos) {
		// Cut the part of the first line starting from XStartPos to the end of the line
		for (int i = XStartPos; i < linesVector[yStartPos].size(); i++) {
			cuttext += linesVector[yStartPos][i];
		}
		cutVector.push_back(cuttext);  // Save the cut text in cutVector
		cuttext = "";  // Reset cuttext for the next part

		// Cut the entire lines between yStartPos and yEndPos
		for (int i = yStartPos + 1; i < yEndPos; i++) {
			for (int j = 0; j < linesVector[i].size(); j++) {
				cuttext += linesVector[i][j];
			}
			cutVector.push_back(cuttext);  // Add the cut text to cutVector
			cuttext = "";  // Reset cuttext for the next part
		}

		// Cut the part of the last line up to XEndPos
		for (int i = 0; i <= xEndPos; i++) {
			cuttext += linesVector[yEndPos][i];
		}
		cutVector.push_back(cuttext);  // Add the last part to cutVector
		cuttext = "";  // Reset cuttext

	}
	// If the selected text is within a single line (yStartPos == yEndPos)
	else if (yStartPos == yEndPos) {
		if (XStartPos < xEndPos) {
			// Cut the part of the current line between XStartPos and xEndPos
			for (int i = XStartPos; i < xEndPos; i++) {
				cuttext += linesVector[yStartPos][i];
			}
			cutVector.push_back(cuttext);  // Add the cut text to cutVector
			cuttext = "";  // Reset cuttext
		}
		else {
			// If XEndPos is before XStartPos, reverse the cut
			for (int i = xEndPos; i < XStartPos; i++) {
				cuttext += linesVector[yStartPos][i];
			}
			cutVector.push_back(cuttext);  // Add the cut text to cutVector
			cuttext = "";  // Reset cuttext
		}
	}
	// If the selected text spans across multiple lines in reverse order (yStartPos > yEndPos)
	else if (yStartPos > yEndPos) {
		// Cut the part of the last line starting from xEndPos to the end of the line
		for (int i = xEndPos; i < linesVector[yEndPos].size(); i++) {
			cuttext += linesVector[yEndPos][i];
		}
		cutVector.push_back(cuttext);  // Add the cut text to cutVector
		cuttext = "";  // Reset cuttext

		// Cut all the lines between yEndPos and yStartPos in reverse order
		for (int i = yEndPos + 1; i < yStartPos; i++) {
			for (int j = 0; j < linesVector[i].size(); j++) {
				cuttext += linesVector[i][j];
			}
			cutVector.push_back(cuttext);  // Add the cut text to cutVector
			cuttext = "";  // Reset cuttext
		}

		// Cut the part of the first line up to XStartPos
		for (int i = 0; i <= XStartPos; i++) {
			cuttext += linesVector[yStartPos][i];
		}
		cutVector.push_back(cuttext);  // Add the cut text to cutVector
		cuttext = "";  // Reset cuttext
	}

	// Remove the cut text from the linesVector (display)
	if (yStartPos < yEndPos) {
		// Remove characters from the start line from XStartPos to the end of the line
		linesVector[yStartPos].erase(linesVector[yStartPos].begin() + XStartPos, linesVector[yStartPos].end());

		// Remove characters from the end line from the beginning of the line to xEndPos
		linesVector[yEndPos].erase(linesVector[yEndPos].begin(), linesVector[yEndPos].begin() + xEndPos);

		// Remove all the lines between yStartPos and yEndPos
		linesVector.erase(linesVector.begin() + yStartPos + 1, linesVector.begin() + yEndPos);
	}
	else if (yStartPos == yEndPos) {
		if (XStartPos < xEndPos) {
			// Remove the characters between XStartPos and xEndPos in the same line
			linesVector[yStartPos].erase(linesVector[yStartPos].begin() + XStartPos, linesVector[yStartPos].begin() + xEndPos);
		}
		else {
			// If xEndPos is before XStartPos, remove the characters in reverse order
			linesVector[yStartPos].erase(linesVector[yStartPos].begin() + xEndPos, linesVector[yStartPos].begin() + XStartPos);
		}
	}
	else if (yStartPos > yEndPos) {
		// Remove characters from the last line from xEndPos to the end of the line
		linesVector[yEndPos].erase(linesVector[yEndPos].begin() + xEndPos, linesVector[yEndPos].end());

		// Remove characters from the start line from the beginning of the line to XStartPos
		linesVector[yStartPos].erase(linesVector[yStartPos].begin(), linesVector[yStartPos].begin() + XStartPos);

		// Remove all the lines in reverse order between yEndPos and yStartPos
		linesVector.erase(linesVector.begin() + yEndPos + 1, linesVector.begin() + yStartPos);
	}
}

// Function to handle text selection mode
void SelectMode() {


	selected = "";
	yStartPos = y;
	XStartPos = x;

	while (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
	{

		height = linesVector[y].size();

		if (_kbhit())
		{
			char ch = _getch();


			// Check if the right arrow key (ASCII code 77) is pressed
			if (ch == 77)//right
			{
				if (linesVector[y].size() == 0) { 
					selected.push_back(linesVector[y][x]);
					y++;
					gotoxy(x, y);
					height = linesVector[y].size();
				}
				else {
					if (y > yStartPos) {
						if (x < height)
						{
							selected.push_back(linesVector[y][x]);
							SetConsoleColor(15, 1);
							cout << linesVector[y][x];
							x++;
							cout << "";
							continue;
						}
						else if (x == height && y != linesVector.size() - 1) {
							y++;
							x = 0;
							gotoxy(x, y);
							selected.push_back(linesVector[y][x]);
							SetConsoleColor(15, 1);
							cout << linesVector[y][x];
							x++;

							cout << "";
							continue;
						}

					}
					if (yStartPos == y && XStartPos <= x) {
						if (x != height)
						{
							SetConsoleColor(15, 1);
							cout << linesVector[y][x];
							selected.push_back(linesVector[y][x]);
							x++;

							continue;
						}
						else if (x == height && y != width) {
							y++;
							x = 0;
							gotoxy(x, y);
							SetConsoleColor(15, 1);
							cout << linesVector[y][x];
							selected.push_back(linesVector[y][x]);
							x++;

							continue;
						}
					}
					if (yStartPos == y && XStartPos > x || yStartPos > y) {
						if (x != linesVector[y].size()) {
							SetConsoleColor(7, 0);
							selected.erase(0, 1);
							cout << linesVector[y][x];
							x++;



							cout << "";
							continue;
						}
						else {
							y++;
							x = 0;
							gotoxy(x, y);
						}

					}

				}
			}


			// Check if the left arrow key (ASCII code 75) is pressed
			if (ch == 75) {
				if (yStartPos < y) {
					if (x != 0)
					{
						SetConsoleColor(7, 0);
						x--; gotoxy(x, y);
						cout << linesVector[y][x];
						gotoxy(x, y);


						selected.pop_back();
						cout << "";
						continue;
					}
					else if (x == 0 && y != 0) {
						SetConsoleColor(7, 0);
						y--; x = linesVector[y].size();
						gotoxy(x, y);
						cout << linesVector[y][x];
						gotoxy(x, y);




						selected.pop_back();
						cout << "";
						continue;
					}
				}
				if (yStartPos == y && XStartPos < x) {
					if (x != 0)
					{
						SetConsoleColor(7, 0);
						x--;
						gotoxy(x, y);

						cout << linesVector[y][x];


						gotoxy(x, y);
						selected.pop_back();
						cout << "";
						continue;
					}
					else if (x == 0 && y != 0) {
						SetConsoleColor(7, 0);

						cout << linesVector[y][x];
						y--;
						x = linesVector[y].size();

						gotoxy(x, y);
						selected.pop_back();
						cout << "";
						continue;
					}
				}
				else {
					if (x != 0)
					{
						SetConsoleColor(15, 1);

						x--; gotoxy(x, y);

						cout << linesVector[y][x];
						gotoxy(x, y);


						selected = linesVector[y][x] + selected;
						cout << "";
						continue;
					}
					else if (x == 0 && y != 0) {
						SetConsoleColor(15, 1);

						cout << linesVector[y][x];
						y--;
						x = linesVector[y].size();

						gotoxy(x, y);
						cout << "";
						continue;
					}
				}
			}

			// Check if the down arrow key (ASCII code 80) is pressed
			if (ch == 80) { // Down arrow
				if (((x >= XStartPos && y == yStartPos) || (y > yStartPos))) {
					for (int i = x; i < linesVector[y].length(); i++) {
						SetConsoleColor(15, 1);
						selected += linesVector[y][i];
						cout << linesVector[y][i];

					}
					if (y != linesVector.size() - 1) {
						y++;
						gotoxy(0, y);
						if (linesVector[y].size() >= x) {

							for (int i = 0; i < x; i++) {
								SetConsoleColor(15, 1);
								selected += linesVector[y][i];
								cout << linesVector[y][i];

							}
						}
						else { //baraye zaminike tol khat badi kamtare va cursur bayad bere tah khat
							for (int i = 0; i < linesVector[y].size(); i++) {
								SetConsoleColor(15, 1);
								selected += linesVector[y][i];
								cout << linesVector[y][i];

							}
							x = linesVector[y].size();

						}
					}
					else
					{
						x = linesVector[y].size();
					}
					gotoxy(x, y);
				}
				else if (x <= XStartPos && y == yStartPos && yStartPos) {
					selected = "";
					for (int i = x; i < linesVector[y].length(); i++) {
						SetConsoleColor(15, 1);
						selected += linesVector[y][i];
						cout << linesVector[y][i];

					}
					if (y != width) {
						y++;
						gotoxy(0, y);
						if (linesVector[y].size() >= x) {

							for (int i = 0; i < x; i++) {
								SetConsoleColor(15, 1);
								selected += linesVector[y][i];
								cout << linesVector[y][i];

							}
						}
						else { //baraye zaminike tol khat badi kamtare va cursur bayad bere tah khat
							for (int i = 0; i < linesVector[y].size(); i++) {
								SetConsoleColor(15, 1);
								selected += linesVector[y][i];
								cout << linesVector[y][i];

							}
							x = linesVector[y].size();

						}
					}
					else
					{
						x = linesVector[y].size();
					}
					gotoxy(x, y);
				}
				else if (yStartPos) {
					if (y + 1 != yStartPos) {
						for (int i = x; i < linesVector[y].length(); i++) {
							SetConsoleColor(7, 0);
							selected.erase(0, 1);
							cout << linesVector[y][i];

						}

						y++;
						gotoxy(0, y);
						if (linesVector[y].size() >= x) {

							for (int i = 0; i < x; i++) {
								SetConsoleColor(7, 0);
								selected.erase(0, 1);
								cout << linesVector[y][i];

							}
						}
						else { //baraye zaminike tol khat badi kamtare va cursur bayad bere tah khat
							for (int i = 0; i < linesVector[y].size(); i++) {
								SetConsoleColor(7, 0);
								selected.erase(0, 1);
								cout << linesVector[y][i];

							}
							x = linesVector[y].size();

						}


						gotoxy(x, y);
					}
					else {
						if (x <= XStartPos) {
							for (int i = x; i < linesVector[y].length(); i++) {
								SetConsoleColor(7, 0);
								selected.erase(0, 1);
								cout << linesVector[y][i];

							}

							y++;
							gotoxy(0, y);
							if (linesVector[y].size() >= x) {

								for (int i = 0; i < x; i++) {
									SetConsoleColor(7, 0);
									selected.erase(0, 1);
									cout << linesVector[y][i];

								}
							}
							else { //baraye zaminike tol khat badi kamtare va cursur bayad bere tah khat
								for (int i = 0; i < linesVector[y].size(); i++) {
									SetConsoleColor(7, 0);
									selected.erase(0, 1);
									cout << linesVector[y][i];

								}
								x = linesVector[y].size();

							}


							gotoxy(x, y);
						}
						else {
							for (int i = x; i < linesVector[y].length(); i++) {
								SetConsoleColor(7, 0);
								selected.erase(0, 1);
								cout << linesVector[y][i];

							}

							y++;
							gotoxy(0, y);
							if (linesVector[y].size() >= x) {

								for (int i = 0; i < XStartPos; i++) {
									SetConsoleColor(7, 0);
									selected.erase(0, 1);
									cout << linesVector[y][i];

								}
								for (int i = XStartPos; i < x; i++) {
									SetConsoleColor(15, 1);
									selected += linesVector[y][i];
									cout << linesVector[y][i];

								}
							}
							else { //baraye zaminike tol khat badi kamtare va cursur bayad bere tah khat


								for (int i = 0; i < XStartPos; i++) {
									SetConsoleColor(7, 0);
									selected.erase(0, 1);
									cout << linesVector[y][i];

								}
								x = linesVector[y].size();
								for (int i = XStartPos; i < x; i++) {
									SetConsoleColor(15, 1);
									selected += linesVector[y][i];
									cout << linesVector[y][i];

								}




							}


							gotoxy(x, y);
						}
					}


				}

			}


			// Check if the up arrow key (ASCII code 72) is pressed
			if (ch == 72) {//Up arrow

				if (x <= XStartPos && y <= yStartPos) {
					string selected2 = "";
					SetConsoleColor(15, 1);


					if (y != 0) {
						y--;
						gotoxy(x, y);
						if (linesVector[y].size() >= x) {
							for (int i = x; i <= linesVector[y].size(); i++) {
								selected2 += linesVector[y][i];
								cout << linesVector[y][i];
							}
						}
						else {//vaghti khat balayee kotah tare
							x = linesVector[y].size();
							gotoxy(x, y);

						}

						gotoxy(0, y + 1);
						for (int i = 0; i < x; i++) {

							selected2 += linesVector[y + 1][i];
							cout << linesVector[y + 1][i];
						}


					}
					else {
						gotoxy(0, y);
						for (int i = 0; i < x; i++) {
							selected2 += linesVector[y][i];
							cout << linesVector[y][i];

						}
						x = 0;

					}
					gotoxy(x, y);
					selected = selected2 + selected;
				}
				else if (y > yStartPos) {
					if (x >= XStartPos) {
						SetConsoleColor(7, 0);


						if (y != 0) {
							y--;
							gotoxy(x, y);

							for (int i = x; i <= linesVector[y].size(); i++) {

								selected.erase(0, 1);
								cout << linesVector[y][i];
							}

							gotoxy(0, y + 1);
							for (int i = 0; i < x; i++) {

								selected.erase(0, 1);
								cout << linesVector[y + 1][i];
							}

							if (x > linesVector[y].size()) {
								//vaghti khat balayee kotah tare
								x = linesVector[y].size();
							}
							gotoxy(x, y);

						}
						else {
							gotoxy(0, y);
							for (int i = 0; i < x; i++) {
								selected.erase(0, 1);

								cout << linesVector[y][i];

							}
							x = 0;

						}
						gotoxy(x, y);
					}
					else {
						if (y - 1 == yStartPos) {
							SetConsoleColor(7, 0);
							y--;
							gotoxy(x, y);

							SetConsoleColor(15, 1);
							for (int i = x; i < XStartPos; i++) {

								selected = selected + linesVector[y][i];
								cout << linesVector[y][i];

							}
							SetConsoleColor(7, 0);

							for (int i = XStartPos; i < linesVector[y].size(); i++) {

								selected.erase(0, 1);
								cout << linesVector[y][i];
							}

							gotoxy(0, y + 1);
							for (int i = 0; i < x; i++) {

								selected.erase(0, 1);
								cout << linesVector[y + 1][i];
							}

							gotoxy(x, y);
						}
						else {
							SetConsoleColor(7, 0);


							if (y != 0) {
								y--;
								gotoxy(x, y);
								if (linesVector[y].size() >= x) {
									for (int i = x; i <= linesVector[y].size(); i++) {

										selected.erase(0, 1);
										cout << linesVector[y][i];
									}
								}
								else {//vaghti khat balayee kotah tare
									x = linesVector[y].size();
									gotoxy(x, y);

								}

								gotoxy(0, y + 1);
								for (int i = 0; i < x; i++) {

									selected.erase(0, 1);
									cout << linesVector[y + 1][i];
								}


							}
							else {
								gotoxy(0, y);
								for (int i = 0; i < x; i++) {
									selected.erase(0, 1);

									cout << linesVector[y][i];

								}
								x = 0;

							}
							gotoxy(x, y);
						}
					}
				}
				else if (x > XStartPos && y == yStartPos) {
					SetConsoleColor(15, 1);
					selected = "";

					if (y - 1 != 0) {
						y--;
						gotoxy(x, y);
						if (linesVector[y].size() >= x) {
							for (int i = x; i <= linesVector[y].size(); i++) {
								selected += linesVector[y][i];
								cout << linesVector[y][i];
							}
						}
						else {//vaghti khat balayee kotah tare
							x = linesVector[y].size();
							gotoxy(x, y);

						}

						gotoxy(0, y + 1);
						for (int i = 0; i < XStartPos; i++) {

							selected += linesVector[y + 1][i];
							cout << linesVector[y + 1][i];
						}
						SetConsoleColor(7, 0);
						for (int i = XStartPos; i < x; i++) {
							cout << linesVector[y + 1][i];

						}



					}
					else {
						gotoxy(0, y);
						for (int i = 0; i < x; i++) {
							selected = linesVector[y][i] + selected;
							cout << linesVector[y][i];

						}
						x = 0;

					}
					gotoxy(x, y);

				}
			}


		}
	}

	yEndPos = y;
	xEndPos = x;
	savedSelect = selected;

}




// Function to set the visibility of the console cursor
void setCursorVisibility(bool visible) {
	// Retrieve the handle to the standard output device (console)
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Declare a structure to hold information about the cursor
	CONSOLE_CURSOR_INFO cursorInfo;

	// Get the current cursor information
	GetConsoleCursorInfo(hConsole, &cursorInfo);

	// Set the cursor visibility based on the 'visible' parameter
	cursorInfo.bVisible = visible;


}


// Function to display the main menu and handle user input for navigation
void menu() {
	running = true;  // Set the running flag to true (indicating the program is running)
	int choice = 0;  // Variable to track the user's menu choice
	const char* options[] = { "New File", "Open a File", "Exit" };  // Menu options
	int numOptions = sizeof(options) / sizeof(options[0]);  // Calculate the number of options
	setCursorVisibility(false);  // Hide the cursor while the menu is displayed
	bool runfirstmenu = true;  // Flag to control the menu loop

	while (runfirstmenu) {
		system("cls");  // Clear the console screen
		cout << "Console TextEditor : HOME MENU" << endl << endl;  // Display the title of the menu

		// Display the menu options with highlighting for the selected option
		for (int i = 0; i < numOptions; i++) {
			if (i == choice) {
				// If the option is selected, highlight it
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 240);  // Highlighted text
				cout << "> " << options[i] << endl;
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);  // Normal text
			}
			else {
				cout << "  " << options[i] << endl;  // Display the non-selected options
			}
		}

		// Wait for a key press to navigate the menu
		switch (_getch()) {
		case 72:  // Up arrow key
			// Move the selection up, wrapping around if necessary
			choice = (choice - 1 + numOptions) % numOptions;
			break;
		case 80:  // Down arrow key
			// Move the selection down, wrapping around if necessary
			choice = (choice + 1) % numOptions;
			break;
		case 13:  // Enter key
			// Handle the action based on the selected choice
			if (choice == 0) {
				cout << "You selected: " << options[choice] << endl;
				runfirstmenu = false;
				running = true;
				startMode = "newfile";  // Set mode for new file creation
				(void)_getch();  // Wait for user input before proceeding
			}
			if (choice == 1) {
				cout << "You selected: " << options[choice] << endl;
				runfirstmenu = false;
				running = true;
				startMode = "openfile";  // Set mode for opening an existing file
				(void)_getch();  // Wait for user input before proceeding
			}
			else if (choice == 2) {
				cout << "You selected: " << options[choice] << endl;
				runfirstmenu = false;
				running = false;
				mainRun = false;  // Set mainRun to false to exit the program
				(void)_getch();  // Wait for user input before exiting
			}
			break;
		}

		setCursorVisibility(true);  // Show the cursor after the menu interaction
	}
}

// Function to clear a specific line in the console at position 'y'
void ClearLine(int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);  // Get the handle for the console output
	// Set the cursor position to the beginning of the specified line (y)
	COORD coord = { 0, static_cast<SHORT>(y) };  // Create a coordinate structure with x = 0 and y = specified line
	SetConsoleCursorPosition(hConsole, coord);  // Move the cursor to the desired position

	// Clear the line by writing spaces
	DWORD charsWritten;  // Number of characters written (not used directly)
	CONSOLE_SCREEN_BUFFER_INFO csbi;  // Structure to store console screen buffer information
	GetConsoleScreenBufferInfo(hConsole, &csbi);  // Get the current console screen buffer info
	FillConsoleOutputCharacter(hConsole, ' ', csbi.dwSize.X, coord, &charsWritten);  // Fill the line with spaces (' ')

	// Reset the cursor position to the beginning of the cleared line
	SetConsoleCursorPosition(hConsole, coord);  // Place the cursor back at the start of the cleared line
}

// Function to search for a specific string in the text and highlight its occurrences
void Search(string searchString) {
	bool found = false;

	// Loop through each line in the linesVector (which holds the lines of text)
	for (int i = 0; i < linesVector.size(); i++) {

		// Find the position of the search string in the current line
		size_t pos = linesVector[i].find(searchString);

		// If the string is found in the current line
		if (pos != string::npos) {
			found = true;

			// Move the cursor to the found position
			gotoxy(pos, i);

			// Set the text color to highlight the found string
			SetConsoleColor(15, 1);

			// Print each character of the found string to highlight it
			for (int j = 0; j < searchString.length(); j++) {
				cout << searchString[j];
			}

			// Reset the text color to the default
			SetConsoleColor(7, 0);
		}
	}

	// If no occurrence of the search string was found
	if (found == false) {
		// Move the cursor to a specific position to show a "String not found" message
		gotoxy(40, linesVector.size());
		cout << "String not found!" << endl;
	}
}


// Function to initiate a search in the text
void Searching() {
	bool searchMode = true;  // Variable to control the search loop
	while (searchMode) {

		// Set the cursor at the end of the text (displayed lines)
		gotoxy(0, linesVector.size());
		cout << "Enter string to search: ";  // Prompt the user for input
		int key = _getch();  // Get a key press from the user (non-blocking)

		if (key == 27) {  // If the 'Esc' key is pressed
			searchMode = false;  // Exit the search mode
			DisplayRefresh();  // Refresh the display to show the original text
		}
		else {
			// If any other key is pressed, treat it as part of the search string
			cout << char(key);  // Display the typed character
			getline(cin, searchString);  // Get the rest of the input after the first character
			searchString = char(key) + searchString;  // Prepend the first character to the search string
			DisplayRefresh();  // Refresh the display after typing the search string
			Search(searchString);  // Call the 'Search' function to find the search string in the text
		}
	}
}



// Function to select all text in the editor (similar to Ctrl+A functionality)
void CrtlA() {
	selected = "";  // Clear the selected text string (reset it)

	// Move the cursor to the top-left corner (0, 0)
	gotoxy(0, 0);

	// Set console text color to white text on blue background for highlighting
	SetConsoleColor(15, 1);

	// Loop through each line in the linesVector (representing the text)
	for (int i = 0; i < linesVector.size(); i++) {

		// Loop through each character in the current line
		for (int j = 0; j < linesVector[i].size(); j++) {
			selected += linesVector[i][j];  // Append the character to the selected text
			cout << linesVector[i][j];  // Print the character to the console
		}

		// Add a newline character after each line except the last one
		if (i != linesVector.size()) {
			cout << endl;
		}
	}

	// Reset the console text color to default (white on black)
	SetConsoleColor(7, 0);
}



void Help() {
	SetConsoleColor(7, 0);
	gotoxy(90, 0);
	cout << "|" << "File Name : " << address;
	gotoxy(90, 1);
	cout << "|" << "press esc to save and close";
	gotoxy(90, 2);
	cout << "|" << "Crtl+F for search";
	gotoxy(90, 3);
	cout << "|" << "Hold shift to select";
	gotoxy(90, 4);
	cout << "|" << "Crtl+C/V/X/A are enable";
	gotoxy(90, 5);
	cout << "------------------------------";

	SetConsoleColor(15, 1);
	gotoxy(x, y);

}

// Function to handle the first unwanted key press during the first load
void DelFirstUnwanted() {
	// Check if this is the first time the function is being called
	if (firstLoad) {
		key = 8;  // Set the key to 8, which corresponds to the backspace key
		firstLoad = false;  // Set the firstLoad flag to false to prevent this block from running again
	}
}


// valriabels reset to the default (for restarting the program)
void Resetprogram() {
	// Reset all program variables, clear buffers, and reinitialize if needed

	firstTime = true;
	specialKey = false;
	running = true;
	press = true;
	firsttime = true;
	SelectmodePressed = false;
	firstLoad = true;
	crtlA = false;
	openCorrectly = false;
	width = 0;
	height = 0;
	x = 0;
	y = 0;



	selected = "";
	searchString = "";
	address = "";
	enteredLineText = "";
	savedSelect = "";
	cuttext = "";
	startMode = "";
	linesVector.clear();
	cutVector.clear();

}
//wrote by AMIRHOSEIN...