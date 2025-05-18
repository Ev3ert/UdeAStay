#include "DataStructure/list.h"
#include <iostream>

int main()
{
    List<int> list;

    // * add elements to the start of the list
    list.insertStart(10);
    list.insertStart(25);
    list.insertStart(30);

    // * add elements to the end of the list
    list.insertEnd(50);
    list.insertEnd(60);

    std::cout << "Tamaño de la lista: " << list.size() << std::endl;

    // Show the elements in the list
    std::cout << "Elementos en la lista: ";
    for (unsigned int i = 0; i < list.size(); i++) {
        int* value = list.get(i);
        if(value) 
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
    for (unsigned int i = 0; i < list.size(); ++i) {
        int* val = list.get(i);
        if (val) {
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
