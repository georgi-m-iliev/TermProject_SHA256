#include <iostream>
#include "SHA256.h"
#include "ConsoleTools.h"
#include "FileTools.h"

const int TEXT_LENGTH = 2000;

void optionA() {
    int length = 0;
    char *text = new char[TEXT_LENGTH];
    std::cin >> std::ws;
    while(true) {
        std::cin.getline(text, TEXT_LENGTH);
        text[length-2] = '\0';
        std::cout << "Result: ";
        char *result = getSHA(text);
        std::cout << result << '\n';
        delete[] result;
        std::cout << "\n";
        if(std::cin.eof()) {
            break;
        }
    }
    delete[] text;
}

void optionB() {
    char text[TEXT_LENGTH], temp[TEXT_LENGTH];
    while(true) {
        std::cout << "Enter the absolute path of the file or type 0 and press ENTER to exit.\n";
        std::cin.getline(temp, TEXT_LENGTH);
        if(temp[0] == '0') {
            break;
        }
        int status = readFileToCharArr(temp, text);
        if(status == 0) {
            char *result = getSHA(text);
            std::cout << "\nResult: ";
            std::cout << result << '\n';
            std::cout << "\nWould you like to save this hash to file?\nIf yes, then enter absolute path. If no, then type 0 and press ENTER to exit.\n\n";
            std::cin.getline(temp, TEXT_LENGTH);
            if(temp[0] != '0') {
                status = writeToFile(temp, result);
                if(status == 0) {
                    std::cout << "File has been written successfully!\n\n";
                }
            }
            delete[] result;
        }
        if(status == -1) {
            std::cout << "Error, file cannot be opened, try again!\n\n";
        }
        if(status != 0 && status != -1) {
            std::cout << "Unknown error :(\n\n";
        }
    }
}

void optionC() {
    char text[TEXT_LENGTH], path[TEXT_LENGTH];
    std::cin >> std::ws;
    while(true) {
        std::cout << "Enter the absolute path of the file or type 0 and press ENTER to exit.\n";
        std::cin.getline(path, TEXT_LENGTH);
        if(path[0] == '0') {
            break;
        }
        int status = readFileToCharArr(path, text);
        if(status == 0) {
            std::cout << text << "\n\n";
        }
        else {
            std::cout << "Error, try again!\n\n";
        }
    }
}

void defaultOption() {
    std::cin.get();
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

