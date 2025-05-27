#include "ConUtils.h"
#include <iostream>



/// * ------ Print format functions ------

void print(const char *text)
{
    std::cout << text;
}

void printTitle(const char *title, char fill, unsigned int width)
{
    // for caculate the length of center title
    unsigned int titleLength {0}; 
    while(title[titleLength] != '\0') 
    {
        titleLength++;
    }

    // if the tittle is greater than the width, print the title
    if(titleLength >= width)
    {
        std::cout << "\033[1;1m" << title << "\033[0m" << '\n';
        return;
    }

    // caculate the space to center the title
    unsigned int totalPadding = width - titleLength;
    unsigned int leftPadding = totalPadding / 2;
    unsigned int rightPadding = totalPadding - leftPadding;

    // print the title with padding
    for (unsigned int i = 0; i < leftPadding; i++) std::cout << fill;

    std::cout << "\033[1;1m" << title << "\033[0m";

    for (unsigned int i = 0; i < rightPadding; i++) std::cout << fill;

    std::cout << '\n';
}

void printDivider(char fill, unsigned int width)
{
    for(unsigned int i = 0; i < width; i++) std::cout << fill;
    std::cout << '\n';
}

void printCentered(const char *text, unsigned int width)
{
    // for caculate the length of center title
    unsigned int textLength {0}; 
    while(text[textLength] != '\0') 
    {
        textLength++;
    }

    // if the tittle is greater than the width, print the title
    if(textLength > width)
    {
        std::cout << text << '\n';
        return;
    }

    // caculate the space to center the title
    unsigned int totalPadding = width - textLength;
    unsigned int leftPadding = totalPadding / 2;
    unsigned int rightPadding = totalPadding - leftPadding;

    // print the title with padding
    for (unsigned int i = 0; i < leftPadding; i++) std::cout << ' ';
    std::cout << text;
    for (unsigned int i = 0; i < rightPadding; i++) std::cout << ' ';
    std::cout << '\n';
}


void printSuccess(const char *text)
{
    std::cout << "\033[1;32m" << text << "\033[0m";
}

void printError(const char *text)
{
    std::cout << "\033[1;31m" << text << "\033[0m";
}

void space()
{
    std::cout << '\n';
}



/// * ------ reading functions ------

bool readLine(char *buffer, unsigned int size)
{
    std::cin.clear();
    
    std::cin.getline(buffer, size, '\n');

    if(std::cin.fail())
    {
        clearFail();
        return false;   
    }
    
    return true;        
}


int readInt()
{
    int value {};

    while (!(std::cin >> value))
    {
        printError("Error: Ingrese un numero entero valido: ");
        clearFail();
    }

    flushInput();

    return value;
}


float readFloat()
{
    float value {};

    while (!(std::cin >> value))
    {
        printError("Error: Ingrese un numero decimal valido: ");
        clearFail();
    }

    flushInput(); // clear garbage from the new input

    return value;
}


/// * ------ auxiliary functions ------

void pause()
{
    std::cout << "Presione ENTER para continuar...";
    std::cin.ignore(10000, '\n'); 
}

void clearConsole()
{
    #ifdef _WIN32
        system("cls");
    #else // UNIX-like systems macOS, Linux, etc.
        system("clear");
    #endif
}

void clearFail()
{
    std::cin.clear(); 
    std::cin.ignore(10000, '\n');  // this ignores up to 10000 characters or up to one new line
}

void flushInput()
{
    std::cin.ignore(10000, '\n'); // Not is possible to include limits libraries in this proyect
}






