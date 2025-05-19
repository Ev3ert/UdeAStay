#include "DataStructure/list.h"
#include "DataStructure/string.h"
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
    // create a string empty
    std::cout << "---Creando string vacio---\n";
    String emptyStr;
    std::cout << "Tamano del string vacio: " << emptyStr.size() << "\n";
    std::cout << "Contenido del string vacio: \"" << emptyStr.getRawData() << "\"\n\n";

    // create a string with a initial value
    std::cout << "---Inicializacion con valor de string---\n";
    String hello("Hello, World!");
    std::cout << "Contenido del string: \"" << hello.getRawData() << "\"\n";
    std::cout << "Tamano del string: " << hello.size() << "\n\n";

    // create a string with a copy constructor
    std::cout << "---Creando string con constructor de copia---\n";
    String copyStr(hello);
    std::cout << "Contenido del string original: \"" << hello.getRawData() << "\"\n";
    std::cout << "Contenido del string copiado: \"" << copyStr.getRawData() << "\"\n";

    // copy with assignment operator
    std::cout << "---Creando string con operador de asignacion---\n";
    String assigned;
    assigned = hello;
    std::cout << "Contenido del string original: \"" << hello.getRawData() << "\"\n";
    std::cout << "Contenido del string asignado: \"" << assigned.getRawData() << "\"\n\n";    

    // compare strings
    std::cout << "---Operador de igualdad---\n";
    String str1("Test");
    String str2("Test");
    String str3("Different");
    
    std::cout << "str1: \"" << str1.getRawData() << "\"\n";
    std::cout << "str2: \"" << str2.getRawData() << "\"\n";
    std::cout << "str3: \"" << str3.getRawData() << "\"\n";
    
    std::cout << "str1 == str2: " << (str1 == str2 ? "true" : "false") << "\n";
    std::cout << "str1 == str3: " << (str1 == str3 ? "true" : "false") << "\n";
    std::cout << "str2 == str3: " << (str2 == str3 ? "true" : "false") << "\n\n";
    
}


int main()
{
    stringTesting();

    return 0;
}
