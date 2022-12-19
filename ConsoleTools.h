#include <iostream>
#include "ConsoleAPIs.h"

void printBlankLines(const int height, int &printedLines, const int delta) {
    for(int i = 0; i < height - printedLines - 1 - delta; i++) {
        std::cout << "\n";
    }
}

void printLogo(const int width, int &printedLines) {

    char**  logoParts = new char*[5];
    logoParts[0] = new char[] {R"(   _____ __  _____        ___   ___________)"};
    logoParts[1] = new char[] {R"(  / ___// / / /   |      |__ \ / ____/ ___/)"};
    logoParts[2] = new char[] {R"(  \__ \/ /_/ / /| |________/ //___ \/ __ \)"};
    logoParts[3] = new char[] {R"( ___/ / __  / ___ /_____/ __/____/ / /_/ /)"};
    logoParts[4] = new char[] {R"(/____/_/ /_/_/  |_|    /____/_____/\____/)"};

    for(int i = 0; i < 5; i++) {
        // logo is 43 chars wide
        for(int j = 0; j < (width - 43) / 2; j++) {
            std::cout << " ";
        }
        std::cout << logoParts[i] << "\n";
        printedLines++;
    }

}

void printHeader(const int width, int &printedLines) {
    printLogo(width, printedLines);
    std::cout << "\n\n"; printedLines += 2;
}

void printOptions(int &printedLines) {
    std::cout << "1. Hash from console" << std::endl;
    std::cout << "2. Hash from file" << std::endl;
    std::cout << "3. Print hash from file" << std::endl;
    std::cout << "0. Exit from this application" << std::endl;
    printedLines += 4;
}

void printExitMessage() {
    clearConsole();
    std::cout << "Have a nice day!" << std::endl;
}


void printInitialScreen() {
    clearConsole();
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);

    printHeader(width, printedLines);

    printOptions(printedLines);
    std::cout << "\n\n"; printedLines += 2;

    printBlankLines(height, printedLines, 0);
    std::cin.clear();
}

void printOptionA() {
    clearConsole();
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);

    printHeader(width, printedLines);

    std::cout << "You have chosen: hashing from console input.\n\n";
    std::cout << "Instructions:\nEnter the text you want to hash on a single line and press ENTER.\n"
                 "When you are done press CTRL+Z and then ENTER to return to the main menu.\n\n";
    printedLines += 6;
    //printBlankLines(height, printedLines, 0);
}

void printOptionB() {
    clearConsole();
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);

    printHeader(width, printedLines);

    std::cout << "You have chosen: hashing from file input.\n\n";
    std::cout << "Instructions:\nEnter the text you want to hash on a single line and press ENTER.\n"
                 "When you are done press CTRL+Z and then ENTER to return to the main menu.\n\n";
    printedLines += 6;
    //printBlankLines(height, printedLines, 0);
}

void printOptionC() {
    clearConsole();
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);

    printHeader(width, printedLines);

    std::cout << "You have chosen: print hash from file.\n\n";
    std::cout << "Instructions:\nEnter the text you want to hash on a single line and press ENTER.\n"
                 "When you are done press CTRL+Z and then ENTER to return to the main menu.\n\n";
    printedLines += 6;
    //printBlankLines(height, printedLines, 0);
}

void printDefaultOption() {
    clearConsole();
    int width=0, height=0, printedLines = 0;
    getConsoleBoundaries(width, height);

    printHeader(width, printedLines);
    std::cout << "\n\nError. Unknown input";
    //TODO: Error
    //printBlankLines(height, printedLines, 0);
}