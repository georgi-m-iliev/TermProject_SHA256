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
* <Header file providing functions for controlling the console>
*
*/

#if defined(_WIN32)

#include <Windows.h>

#elif defined(__linux__)
#include <sys/ioctl.h>
#endif // Windows/Linux

void getConsoleBoundaries(int &width, int &height) {
#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    width = (int) (csbi.srWindow.Right - csbi.srWindow.Left + 1);
    height = (int) (csbi.srWindow.Bottom - csbi.srWindow.Top + 1);
#elif defined(__linux__)
    struct winsize w;
    ioctl(fileno(stdout), TIOCGWINSZ, &w);
    width = (int)(w.ws_col);
    height = (int)(w.ws_row);
#endif // Windows/Linux
}

void clearConsole() {
#if defined(_WIN32)
    system("cls");
    //clrscr(); // including header file : conio.h
#elif defined(__linux__)
    system("clear");
    //std::cout<< u8"\033[2J\033[1;1H"; //Using ANSI Escape Sequences
#elif defined (__APPLE__)
    system("clear");
#endif
}