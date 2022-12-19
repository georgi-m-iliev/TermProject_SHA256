#include <iostream>
#include <fstream>

int readFileToCharArr(const char absPath[], char text[]) {
    int ind = 0;
    std::ifstream inputFile (absPath);
    if (inputFile.is_open()) {
        while (!inputFile.eof()) {
            inputFile.get(text[ind++]);
        }
        text[ind-1] = '\0';
        inputFile.close();
    }
    else {
        return -1;
    }
    return 0;
}

int writeHashToFile(const char absPath[], const char text[]) {
    std::ofstream outputFile (absPath);
    if (outputFile.is_open()) {
        for(int i = 0; text[i] != '\0'; i++) {
            outputFile << text[i];
        }
        outputFile.close();
    }
    else {
        return -1;
    }
    return 0;
}