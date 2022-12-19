/*
 * This header file provides almost everything regarding drawing the desired text to the console.
*/

#include <iostream>
#include "ConsoleAPIs.h"

// Constants about centering text, should be changed if length of the text changes
const int LOGO_WIDTH_CHARS = 43;
const int OPTIONS_WIDTH_CHARS = 29;
const int INSTRUCTIONS_WIDTH_CHARS = 42;
const int ERROR_WIDTH_CHARS = 45;

// Function for printing blank lines to get the cursor down to the bottom of the console
void printBlankLines(const int height, int &printedLines, const int delta) {
    for(int i = 0; i < height - printedLines - 1 - delta; i++) {
        std::cout << "\n";
    }
}

void printLogo(const int width, int &printedLines) {

    char **logoParts = new char*[5];
    logoParts[0] = new char[] {R"(   _____ __  _____        ___   ___________)"};
    logoParts[1] = new char[] {R"(  / ___// / / /   |      |__ \ / ____/ ___/)"};
    logoParts[2] = new char[] {R"(  \__ \/ /_/ / /| |________/ //___ \/ __ \)"};
    logoParts[3] = new char[] {R"( ___/ / __  / ___ /_____/ __/____/ / /_/ /  by Georgi Iliev)"};
    logoParts[4] = new char[] {R"(/____/_/ /_/_/  |_|    /____/_____/\____/     8MI0600255)"};

    for(int i = 0; i < 5; i++) {
        // Logo is centered
        for(int j = 0; j < (width - LOGO_WIDTH_CHARS) / 2; j++) {
            std::cout << " ";
        }
        std::cout << logoParts[i] << "\n";
        printedLines++;
    }

}

void printHeader(const int width, int &printedLines) {
    printLogo(width, printedLines);
    std::cout << "\n\n\n\n"; printedLines += 4;
}

void printInstructions(const int width, int &printedLines) {
    for(int i = 0; i < (width - INSTRUCTIONS_WIDTH_CHARS) / 2; i++) std::cout << " ";
    std::cout << "Select from options [0-3] and press ENTER.\n";
    printedLines++;
}

void printOptions(const int width, int &printedLines) {
    for(int i = 0; i < (width - OPTIONS_WIDTH_CHARS) / 2; i++) std::cout << " ";
    std::cout << "1. Hash from console" << std::endl;
    for(int i = 0; i < (width - OPTIONS_WIDTH_CHARS) / 2; i++) std::cout << " ";
    std::cout << "2. Hash from file" << std::endl;
    for(int i = 0; i < (width - OPTIONS_WIDTH_CHARS) / 2; i++) std::cout << " ";
    std::cout << "3. Print hash from file" << std::endl;
    for(int i = 0; i < (width - OPTIONS_WIDTH_CHARS) / 2; i++) std::cout << " ";
    std::cout << "0. Exit from this application" << std::endl;
    printedLines += 4;
}

void printInitialScreen() {
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);
    clearConsole();

    printHeader(width, printedLines);

    printInstructions(width, printedLines);
    for(int i = 0; i < (height - printedLines) / 2; i++) {
        std::cout << '\n';
        printedLines++;
    }
    printOptions(width, printedLines);
    std::cout << "\n\n"; printedLines += 2;

    printBlankLines(height, printedLines, 0);
    std::cin.clear();
}

void printOptionA() {
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);
    clearConsole();

    printHeader(width, printedLines);

    std::cout << "You have chosen: hashing from console input.\n\n";
    std::cout << "Instructions:\n\nEnter the text you want to hash on a single line and press ENTER.\n"
                 "To return to the main menu press CTRL+Z and then press ENTER \n\n";
    printedLines += 6;
    //printBlankLines(height, printedLines, 0);
}

void printOptionB() {
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);
    clearConsole();

    printHeader(width, printedLines);

    std::cout << "You have chosen: hashing from file input.\n\n";
    std::cout << "Instructions:\n\nEnter the absolute path of the file you want to hash and press ENTER.\n"
                 "Afterwards you can choose to save the generated hash by providing absolute path for the new file.\n"
                 "When the process is complete everything will start all over again. To exit type 0 and press Enter.\n\n";
    printedLines += 8;
    //printBlankLines(height, printedLines, 0);
}

void printOptionC() {
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);
    clearConsole();

    printHeader(width, printedLines);

    std::cout << "You have chosen: print hash from file.\n\n";
    std::cout << "Instructions:\n\nEnter the absolute path of the file you want to read then press ENTER.\n"
                 "When the process is complete everything will start all over again. To exit type 0 and press Enter.\n\n";
    printedLines += 7;
    //printBlankLines(height, printedLines, 0);
}

void printDefaultOption() {
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);
    clearConsole();

    printHeader(width, printedLines);
    for(int i = 0; i < (height - printedLines) / 2; i++) {
        std::cout << "\n";
        printedLines++;
    }

    for(int i = 0; i < (width - ERROR_WIDTH_CHARS) / 2; i++) std::cout << " ";
    std::cout << "Error. Unknown input! Press enter to go back.\n";
    printedLines++;

    printBlankLines(height, printedLines, 0);
}

void printExitMessage() {
    clearConsole();
    std::cout << "Have a nice day!" << std::endl;
}