#include "DataStructure/list.h"
#include "DataStructure/string.h"
#include "Utils/ConUtils.h"
#include "Utils/date.h"
#include "Actors/reservation.h"
#include "Actors/accommodations.h"
#include "Actors/host.h"
#include "Actors/guest.h"
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
            f.printDate();
        }
        else
        {
            printError("Fecha invalida: ");
            f.printDate();
        }
        space();
    }

    if(date4 < date1)
    {
        printSuccess("15/08/2023 es menor que 01/01/2024");
    }
    else
    {
        printError("15/08/2023 no es menor que 01/01/2024");
    }
    space();

    if(date1 > date4)
    {
        printSuccess("01/01/2024 es mayor que 15/08/2023");
    }
    else
    {
        printError("01/01/2024 no es mayor que 15/08/2023");
    }
    space();

    if(date1 == date4)
    {
        printSuccess("01/01/2024 es igual que 15/08/2023");
    }
    else
    {
        printError("01/01/2024 no es igual que 15/08/2023");
    }
    space();

    if(date1 >= date4)
    {
        printSuccess("01/01/2024 es mayor o igual que 15/08/2023");
    }
    else
    {
        printError("01/01/2024 no es mayor o igual que 15/08/2023");
    }
    space();

    if(date1 <= date4)
    {
        printSuccess("01/01/2024 es menor o igual que 15/08/2023");
    }
    else
    {
        printError("01/01/2024 no es menor o igual que 15/08/2023");
    }

    space();

    printCentered("---Sumando dias a la fecha---");

    Date date5 = date1.addDays(30);
    print("Fecha original: ");
    date1.printDate();
    space();

    print("Fecha sumando 30 dias: ");
    date5.printDate();
    space();

    date5 = date1.addDays(365);
    print("Fecha sumando 365 dias: ");
    date5.printDate();
    space();

    date5 = date1.addDays(40);
    print("Fecha sumando 40 dias: ");
    date5.printDate();
    space();

    space();

    printCentered("---Verificando si la fecha esta en el intervalo---");
    if(date1.isInterval(date4, Date(10, 11, 2023)))
    {
        printSuccess("La fecha 01/01/2024 esta en el intervalo de 15/08/2023 y 10/11/2023");
    }
    else
    {
        printError("La fecha 01/01/2024 no esta en el intervalo de 15/08/2023 y 10/11/2023");
    }

    space();

}


void reservationTesting()
{
    printTitle(" TESTING RESERVATION ", '=', 50);
    printDivider('=', 50);

    space();

    Host host(
        String("Carlos Gomez"),              
        String("123456789"),                 
        5,                                   
        40                                    
    );

    Accommodation accommodation
    (
        1,                                 
        String("Habitación Deluxe"),        
        host,                              
        String("Antioquia"),                
        String("Apartamento"),              
        String("Calle 123 #45-67"),         
        150000                             
    );

    Reservation reservation(
        1001,
        &accommodation,
        String("Juan Perez"),
        Date(10, 6, 2024),
        3,
        String("Tarjeta de crédito"),
        Date(5, 6, 2024),
        450000,
        String("Sin anotaciones")
    );

    reservation.GenerateVoucher();
    space();
}


int main()
{

    
    dateTesting();


    return 0;

}
