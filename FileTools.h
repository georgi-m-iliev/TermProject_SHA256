/*
* Solution to course project # 6
* Introduction to programming course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2022/2023
*
* @author Georgi Iliev
* @idnumber 8MI0600255 
* @compiler gcc
*
* <Header file providing functions for reading and writing files>
*
*/

#include <fstream>

// The function needs absolute path to access the file and an array of chars for string
int readFileToCharArr(const char absPath[], char text[]) {
    int ind = 0;
    std::ifstream inputFile (absPath);
    if (inputFile.is_open()) {
        while (!inputFile.eof()) {
            // Because we are hashing the contents by characters and not by binary representation,
            // we need every symbol on one line, hence getline() is not appropriate
            inputFile.get(text[ind++]);
        }
        // Must not forget the termination character
        text[ind-1] = '\0';
        // Closing the stream is very important too
        inputFile.close();
    }
    else {
        return -1;
    }
    return 0;
}

// The function writes the character string, containing the hash, to the file
int writeToFile(const char absPath[], const char text[]) {
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