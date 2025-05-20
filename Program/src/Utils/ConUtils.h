#ifndef CONUTILS_H
#define CONUTILS_H

#include <iostream>


/// * ------ Print format functions ------

// Funtion to print normal text
void print(const char *text);

// Funtion to print text with a value
template<typename T>// The template function must be defined in the header file
void printInfo(const char *text, const T &value)
{
    std::cout << "\033[1;1m" << text << "\033[0m" << value << '\n';
}                        

// Function to print a title with a fill character
void printTitle(const char *title, char fill = '-', unsigned int width = 40);

// Funtion to print a divider with a fill character
void printDivider(char fill = '-', unsigned int width = 40);

// Funtion to print a text centered in the console
void printCentered(const char *text, unsigned int width = 40);

// Function for printing green success text 
void printSuccess(const char *text);

// Function for printing red error text
void printError(const char *text);

// Funtion to print line break
void space();

/// * ------ reading functions ------

// Funtion to read a line from the console whit spaces 
void readLine(char *buffer, unsigned int size);

// Function to read an integer from the console and handle errors
int readInt();

// Funtion to read an float from the console and handle errors
float readFloat();

/// * ------ auxiliary functions ------

// Funtion to pause the program until the user press ENTER
void pause();

void clearConsole();

// Funtion to clear the error and the buffer
void clearFail();

// funtion to clear the input buffer
void flushInput();


#endif // CONUTILS_H
