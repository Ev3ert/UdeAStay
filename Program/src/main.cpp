#include "DataStructure/list.h"
#include "DataStructure/string.h"
#include "Utils/ConUtils.h"
#include <iostream>


void listTesting()
{
    List<int> list;

    // add elements to the start of the list
    list.insertStart(10);
    list.insertStart(25);
    list.insertStart(30);

    // add elements to the end of the list
    list.insertEnd(50);
    list.insertEnd(60);

    std::cout << "Tamaño de la lista: " << list.size() << std::endl;

    // Show the elements in the list
    std::cout << "Elementos en la lista: ";
    for (unsigned int i = 0; i < list.size(); i++)
    {
        int *value = list.get(i);
        if (value)
        {
            std::cout << *value << " ";
        }
    }
    std::cout << std::endl;

    // delete a element by their position
    if (list.deleteByPosition(1))
    {
        std::cout << "Elemento en posición 1 eliminado." << std::endl;
    }

    // show the elemente in the list after deleting
    std::cout << "Lista después de eliminar posición 2: ";
    for (unsigned int i = 0; i < list.size(); ++i)
    {
        int *val = list.get(i);
        if (val)
        {
            std::cout << *val << " ";
        }
    }
    std::cout << std::endl;

    // clear the list
    list.clear();

    std::cout << "La lista esta vacia? : ";
    if (list.isEmpty())
    {
        std::cout << "Si" << '\n';
    }
    else
    {
        std::cout << "No" << '\n';
    }
}

void stringTesting()
{
    printTitle(" TESTING STRINGS ", '=', 50);
    printDivider('=', 50);

    // create a string empty
    printCentered("---Creando string vacio---", 50);
    String emptyStr;
    printInfo("Tamano del string vacio: ", emptyStr.size());
    printInfo("Contenido del string vacio: ", emptyStr.getRawData());

    space();

    // create a string with a initial value
    printCentered("---Creando string con valor inicial---", 50);
    String hello("Hello, World!");
    printInfo("Contenido del string: ", hello.getRawData());
    printInfo("Tamano del string: ", hello.size());

    space();

    // create a string with a copy constructor
    printCentered("---Creando string con constructor de copia---", 50);
    String copyStr(hello);
    printInfo("Contenido del string original: ", hello.getRawData());
    printInfo("Contenido del string copiado: ", copyStr.getRawData());

    space();

    // copy with assignment operator
    printCentered("---Creando string con operador de asignacion---", 50);
    String assigned;
    assigned = hello;
    printInfo("Contenido del string original: ", hello.getRawData());
    printInfo("Contenido del string asignado: ", assigned.getRawData());  
    
    space();

    // compare strings
    printCentered("---Comparando strings---", 50);
    String str1("Test");
    String str2("Test");
    String str3("Different");
    
    printInfo("Contenido del string 1: ", str1.getRawData());
    printInfo("Contenido del string 2: ", str2.getRawData());
    printInfo("Contenido del string 3: ", str3.getRawData());
    
    printInfo("str1 == str2: ", 
            (str1 == str2 ? "\033[1;32mtrue\033[0m" : "\033[1;31mfalse\033[0m"));
    printInfo("str1 == str3: ", 
            (str1 == str3 ? "\033[1;32mtrue\033[0m" : "\033[1;31mfalse\033[0m"));
    printInfo("str2 == str3: ", 
            (str2 == str3 ? "\033[1;32mtrue\033[0m" : "\033[1;31mfalse\033[0m"));

}


int main()
{
    stringTesting();

    pause();

    clearConsole();

    float floatValue;
    std::cout << "Ingrese un numero decimal: ";
    floatValue = readFloat();

    int intValue;
    std::cout << "Ingrese un numero entero: ";
    intValue = readInt();

    std::cout << "El numero decimal es: " << floatValue << "\n";
    std::cout << "El numero entero es: " << intValue << "\n";

    return 0;

}
