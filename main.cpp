#include <iostream>
#include "SHA256.h"
#include "ConsoleTools.h"
#include "FileTools.h"

// Constraint for string of char array
const int TEXT_LENGTH = 2000;

// Function implementing hashing by input from console
void optionA() {
    char *text = new char[TEXT_LENGTH];
//    std::cin >> std::ws;
    while(!std::cin.eof()) {
        std::cout << "Input: ";
        if(!std::cin.getline(text, TEXT_LENGTH)) {
            clearerr(stdin);
            break;
        }
        std::cout << "Result: ";
        char *result = getSHA(text);
        std::cout << result << '\n';
        std::cout << "\n";
        delete[] result;
    }
    delete[] text;
}

// Function implementing hashing by input from file
void optionB() {
    char text[TEXT_LENGTH], temp[TEXT_LENGTH];
    while(!std::cin.eof()) {
        std::cout << "Enter the absolute path of the file or type 0 and press ENTER to exit.\n";
        std::cout << "Input Path: ";
        if(!std::cin.getline(temp, TEXT_LENGTH) || temp[0] == '0') {
            clearerr(stdin);
            break;
        }
        int status = readFileToCharArr(temp, text);
        if(status == 0) {
            char *result = getSHA(text);
            std::cout << "\nResult: ";
            std::cout << result << '\n';
            std::cout << "\nWould you like to save this hash to file?\nIf yes, then enter absolute path. If no, then type 0 and press ENTER to exit.\n\n";
            std::cout << "Output Path / exit: ";
            if(!std::cin.getline(temp, TEXT_LENGTH) || temp[0] == '0') {
                clearerr(stdin);
                break;
            }
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
        std::cout << "\n";
    }
}

//Function implementing reading from file
void optionC() {
    char text[TEXT_LENGTH], path[TEXT_LENGTH];
    while(!std::cin.eof()) {
        std::cout << "Enter the absolute path of the file or type 0 and press ENTER to exit.\n";
        std::cout << "Input Path: ";
        if(!std::cin.getline(path, TEXT_LENGTH) || path[0] == '0') {
            clearerr(stdin);
            break;
        }
        int status = readFileToCharArr(path, text);
        if(status == 0) {
            std::cout << "\nOutput:\n" << text;
        }
        else {
            std::cout << "Error, try again!\n\n";
        }
        std::cout << "\n";
    }
}


//Function for default behaviour, when chosen option does not exist
void defaultOption() {
    std::cin.sync();
    std::cin.get();
}

int main() {
    char choice[TEXT_LENGTH];
    do {
        clearConsole();
        printInitialScreen();

        if(!std::cin.getline(choice, TEXT_LENGTH)) {
            printExitMessage();
            break;
        };
        switch(choice[0] - '0') {
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
    } while(choice[0] != '0' || !std::cin.eof());

    return 0;
}