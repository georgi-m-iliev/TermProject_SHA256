#include <iostream>
#include "ConsoleTools.h"
#include "SHA256.h"

const int TEXT_LENGTH = 2000;

void optionA() {
    int length = 0;
    char *text = new char[TEXT_LENGTH];
    std::cin >> std::ws;
    while(true) {
        std::cin.getline(text, TEXT_LENGTH);
        text[length-2] = '\0';
        std::cout << "Result: ";
        printSHA(text);
        std::cout << "\n\n";
        if(std::cin.eof()) {
            break;
        }
    }
    delete[] text;
}

void optionB() {

    std::cout << "Option B";
}

void optionC() {

    std::cout << "Option c";
}

void defaultOption() {

    std::cout << "Option D";
}

int main() {
    int choice = -1;
    while(choice != 0) {
        clearConsole();
        printInitialScreen();
        std::cin >> choice;
        switch(choice) {
            case 0: printExitMessage(); break;
            case 1:
                printOptionA();
                optionA();
            break;
            case 2:
                printOptionB();
                optionB();
            break;
            case 3:
                printOptionC();
                optionC();
            break;
            default:
                printDefaultOption();
                defaultOption();
            break;
        }
    }

    return 0;
}

