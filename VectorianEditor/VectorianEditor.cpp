#include "definition.h"

int main()
{

    // Main loop of the program that keeps running as long as the 'mainRun' flag is true
    while (mainRun) {

        // Display the main menu to the user
        menu();

        // Initialize the editor by performing necessary setups (e.g., opening or creating a file)
        InitialSetting();

        // Handle user input and perform actions like writing, selecting text, etc.
        Keycontrol();

        Resetprogram();  // Reset the program state if needed
    }


}
