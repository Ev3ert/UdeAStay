#include "DataStructure/list.h"
#include "DataStructure/string.h"
#include "Utils/ConUtils.h"
#include "Utils/date.h"
#include "Actors/accommodation.h"
#include "Actors/reservation.h"
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

    space();

    // Add strings
    printCentered("---Sumando strings---", 50);
    String str4("Hello");
    String str5("World");

    String strSum {str4 + str5};
 
    printInfo("Contenido del string 4: ", str4.getRawData());
    printInfo("Contenido del string 5: ", str5.getRawData());
    printInfo("str4 + str5: ", strSum.getRawData());

    space();

    // Split string
    printCentered("---Dividiendo string---", 50);

    String line("2023-10-01:Ubicacion=Mi casa:50000");

    List<String> fields;
    fields = line.split(':');

    for(unsigned int i = 0; i < fields.size(); i++)
    {
        String *field = fields.get(i);
        printInfo("Campo: ", field->getRawData());
    }


}

void dateTesting()
{
    Date date1(1, 1, 2024);
    Date date2(29, 2, 2024);
    Date date3(31, 4, 2024);
    Date date4(15, 8, 2023);

    Date dates[] = {date1, date2, date3, date4};

    for(const Date& f : dates)
    {
        if(f.isValid())
        {
            printSuccess("Fecha valida: ");
            print(f.getFormatDate().getRawData());
        }
        else
        {
            printError("Fecha invalida: ");
            print(f.getFormatDate().getRawData());
        }
        space();
    }

    printInfo("1/1/2024 + 30 dias: ", date1.addDays(30).getFormatDate().getRawData());
    printInfo("1/1/2024 + 24 dias: ", date1.addDays(24).getFormatDate().getRawData());
    printInfo("1/1/2024 + 565 dias: ", date1.addDays(565).getFormatDate().getRawData());

}

void ActorsTesting() 
{
    printTitle(" TESTING ACTORS ", '=', 50);
    printDivider('=', 50);

    List<String> amenities;
    amenities.insertEnd(String("WiFi"));
    amenities.insertEnd(String("Piscina"));
    amenities.insertEnd(String("Parking"));

    Accommodation accommodation(
        1001,
        "Casa bonita",
        nullptr, // Host pointer
        "antioquia",
        "Casa",
        "Calle 123",
        50000,
        amenities
    );

    Date today(1, 6, 2024);
    Date tomorrow = today.addDays(1);
    Date nextWeek = today.addDays(6);
    Date nextMonth = today.addDays(30);

    Reservation res1(
        1001,
        &accommodation,
        "Pedro Gomez",
        nextWeek,
        3,
        "Efectivo",
        today,
        450000,
        "Sin anotaciones"
    );

    accommodation.SetReservation(&res1);

    printTitle("Pruebas de disponibilidad", '-');
    bool available1 = accommodation.isAvailable(today, 3);
    printInfo("Disponible del 1 al 3 de junio?: ", 
              available1 ? "\033[1;32mSí\033[0m" : "\033[1;31mNo\033[0m");
    
    bool available2 = accommodation.isAvailable(nextWeek, 1);
    printInfo("Disponible del 7 de junio?: ", 
              available2 ? "\033[1;32mSí\033[0m" : "\033[1;31mNo\033[0m");
    
    bool available3 = accommodation.isAvailable(nextMonth, 5);
    printInfo("Disponible del 1 al 5 de julio?: ", 
              available3 ? "\033[1;32mSí\033[0m" : "\033[1;31mNo\033[0m");

    space();

    res1.generateVoucher();
}



int main()
{

    ActorsTesting();

    return 0;

}
