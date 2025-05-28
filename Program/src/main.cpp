#include "DataStructure/list.h"
#include "DataStructure/string.h"
#include "Utils/ConUtils.h"
#include "Utils/date.h"
#include "Actors/accommodation.h"
#include "Actors/reservation.h"
#include "Actors/guest.h"
#include "Actors/host.h"
#include "FileSystem/fileSystem.h"


List<Accommodation*> accommodations;
List<Reservation*> reservations;
List<Host*> hosts;
List<Guest*> guests;

Host* userHost {nullptr};
Guest* userGuest {nullptr};

bool userIsHost {false};


/// ID

int accommodationMaxID {};
int reservationMaxID {};

Host *searchHostByName(String name)
{
    for(int i = 0; i < hosts.size(); i++)
    {
        Host* host = *hosts.get(i);
        if(name == host->getName())
        {
            return host;
        }
    }

    return nullptr;
}

Guest *searchGuestByName(String name)
{
    for(int i = 0; i < guests.size(); i++)
    {
        Guest* guest = *guests.get(i);
        if(name == guest->getName())
        {
            return guest;
        }
    }

    return nullptr;
}

/// * ================ HOST ================

void hostProfile()
{
    int option {0};

    while (option != 4)
    {
        clearConsole();

        printTitle(String("Bienvenido ") + userHost->getName(), '=');
        printDivider();

        space();

        print("1. Ver reservaciones. \n");
        print("2. Actualizar historico. \n");
        print("3. Ver datos de ususario. \n");
        print("4. Salir.\n");

        space();

        int option {readInt()};

        switch (option)
        {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            case 4:
                return;
            default:
                printError("ERROR: Opcion invalida");
                break;
        }
    }

}
    

/// * ================ GUEST ================

/// ----- Search accommodations ------

Date askValidDate() 
{
    Date date = Date(1,1,2024);
    bool valid = false;
    do {
        print("Ingrese la fecha (DD MM YYYY):\n");

        print("Dia: ");
        int day = readInt();

        print("Mes: ");
        int month = readInt();

        print("Año: ");
        int year = readInt();

        date = Date(day, month, year);
        if (!date.isValid()) {
            printError("ERROR: fecha invalida.\n");
        } else {
            valid = true;
        }
    } while (!valid);

    return date;
}

int askValidNights() 
{
    int nights = 0;
    do {
        print("Ingrese el numero de noches: ");
        nights = readInt();
        if (nights <= 0) {
            printError("ERROR: Numero de noches invalido.\n");
        }
    } while (nights <= 0);

    return nights;
}


String askMunicipality() 
{

    char* municipality = new char[32];

    while (true) {
        print("Ingrese el municipio: ");
        if (readLine(municipality, 32)) {
            String dept(municipality);
            delete[] municipality;
            return dept;
        }
        printError("ERROR: El nombre del municipio es muy largo.\n");
    }
}

int askFilterOption() {

    print("\nDesea aplicar filtros adicionales?\n");
    print("1. Costo maximo por noche\n");
    print("2. Puntuación minima del anfitrion\n");
    print("3. Ambos filtros\n");
    print("4. Ningun filtro\n");

    int option;
    do {
        option = readInt();
        if (option < 1 || option > 4) {
            printError("ERROR: Invalid option.\n");
        }
    } while (option < 1 || option > 4);
    return option;
}

unsigned long askMaxPrice() {
    unsigned long price;
    do {
        print("Ingrese el precio maximo por noche: ");
        price = readInt();
        if (price <= 0) {
            printError("ERROR: El precio debe ser mayor que 0.\n");
        }
    } while (price <= 0);

    return price;
}

int askMinRating() {
    int rating;
    do {
        print("Ingrese la puntuacion minima del anfitrion (1-5): ");
        rating = readInt();
        if (rating < 1 || rating > 5) {
            printError("ERROR: La puntuacion debe estar en el rango de 1 a 5.\n");
        }
    } while (rating < 1 || rating > 5);

    return rating;
}


String askValidPaymentMethod() {
    char* input = new char[32];
    String method;
    bool valid = false;
    do {
        print("Metodo de pago (efectivo/tarjeta): ");
        readLine(input, 32);
        method = String(input);

        if (method == String("efectivo") || method == String("tarjeta")) {
            valid = true;
        } else {
            printError("ERROR: Solo se permite 'efectivo' o 'tarjeta'.\n");
        }
    } while (!valid);
    delete[] input;

    return method;
}

String askNotes() {
    char* notes = new char[1000];

    print("Notas adicionales (Enter para omitir): ");
    readLine(notes, 1000);

    if(notes[0] == '\0') {
        delete[] notes;
        return String("Sin anotaciones");
    }

    String result(notes);
    delete[] notes;
    return result;
}


void accommodationsInterface() {
    clearConsole();
    printTitle(" BUSQUEDA DE ALOJAMIENTOS ", '=');
    printDivider();
    space();

    Date checkInDate = askValidDate();
    int nights = askValidNights();

    if(!userGuest->checkAvailability(checkInDate, nights)) {
        printError("ERROR: Ya tienes una reservación en esas fechas\n");
        space();
        pause();
        return;
    }

    String municipality = askMunicipality();
    int filterOption = askFilterOption();

    unsigned long maxPrice = 999999999;
    int minRating = 0;

    if (filterOption == 1 || filterOption == 3)
        maxPrice = askMaxPrice();

    if (filterOption == 2 || filterOption == 3)
        minRating = askMinRating();

    List<Accommodation*> filteredList;
    for (int i = 0; i < accommodations.size(); ++i) {
        Accommodation* acc = *accommodations.get(i);

        if (acc->getMunicipality() == municipality &&
            acc->isAvailable(checkInDate, nights) &&
            acc->getPricePerNight() <= maxPrice &&
            acc->getHost()->getPuntuation() >= minRating) {
            filteredList.insertEnd(acc);
        }
    }

    if (filteredList.size() == 0) {
        printError("No se encontraron alojamientos con los criterios especificados\n");
        space();
        pause();
        return;
    }

    printTitle(" ALOJAMIENTOS DISPONIBLES ", '-');
    for (int i = 0; i < filteredList.size(); ++i) {
        print("\n["); print(String::toString(i + 1)); print("] ");
        (*filteredList.get(i))->viewDetails();
    }

    print("\nSelecciones un alojamiento para reservar(0 para cancelar): ");
    int selection;
    do {
        selection = readInt();
        if (selection < 0 || selection > filteredList.size()) {
            printError("ERROR: Seleccion invalida.\n");
        }
    } while (selection < 0 || selection > filteredList.size());

    if (selection == 0) return;

    Accommodation* chosen = *filteredList.get(selection - 1);
    String paymentMethod = askValidPaymentMethod();
    String notes = askNotes();

    unsigned int resId = reservationMaxID + 1;
    unsigned long totalCost = chosen->getPricePerNight() * nights;

    Reservation* newRes = new Reservation(
        resId, chosen, userGuest->getName(), checkInDate,
        nights, paymentMethod, checkInDate, totalCost, notes
    );

    chosen->setReservation(newRes);
    reservations.insertEnd(newRes);
    userGuest->addReservation(newRes);

    printSuccess("\nReservacion realizada con exito!\n");
    newRes->generateVoucher();

    space();
    pause();
}

// ----- view reservations -----

void guestReservationsInterface()
{
    clearConsole();
    printTitle(" RESERVACIONES ", '=');
    printDivider();
    space();

    userGuest->viewReservations();

    space();

    if(userGuest->getReservations().isEmpty()) {
        pause();
        return;
    }

    print("\nSeleccione su ID de reservacion si desea anularla (0 para cancelar): ");
    int selection;
    do {
        selection = readInt();
        if(selection < 0 || selection > userGuest->getReservations().size()) {
            printError("ERROR: ID de reservacion invalido.\n");
        }
    } while(selection < 0 || selection > userGuest->getReservations().size());

    if(selection == 0) {
        return;
    }

    Reservation* res = *userGuest->getReservations().get(selection - 1);

    print("\n¿Esta seguro que desea anular esta reservacion? (s/n): ");
    char* confirm = new char[2];
    readLine(confirm, 2);

    if(confirm[0] == 's' || confirm[0] == 'S') {
        for(unsigned int i = 0; i < reservations.size(); i++) {
            if((*reservations.get(i))->getId() == res->getId()) {
                reservations.deleteByPosition(i);
                break;
            }
        }

        userGuest->cancelReservation(res->getId());
        
        printSuccess("\nReservacion cancelada exitosamente!\n");
    }

    delete[] confirm;
    space();
    pause();
   
}

void viewGuestUserDetails()
{
    clearConsole();
    printTitle(" DATOS DEL USUARIO ", '=');
    printDivider();
    space();

    printInfo("Nombre           : ", userGuest->getName());
    printInfo("Documento        : ", userGuest->getDocument());
    printInfo("Antiguedad       : ", userGuest->getAntiquity());
    printInfo("Puntuación       : ", userGuest->getPuntuation());

    space();
    pause();
}


void guestProfile()
{

    int option {0};

    while (option != 4)
    {
        clearConsole();

        printTitle(String("Bienvenido ") + userGuest->getName(), '=');
        printDivider();

        space();

        print("1. Buscar alojamientos. \n");
        print("2. Ver reservaciones. \n");
        print("3. Ver datos de ususario. \n");
        print("4. Salir y Guardar.\n");

        space();

        int option {readInt()};

        switch (option)
        {
            case 1:
                accommodationsInterface();
                break;
            case 2:
                guestReservationsInterface();
                break;
            case 3:
                viewGuestUserDetails();
                break;
            case 4:
                return;
            default:
                printError("ERROR: Opcion invalida");
                break;
        }
    }

}

/// * ================ LOGIN ================

void login()
{
    printTitle(" UDEASTAY ", '=');
    printDivider('=');

    char* userName = new char[16];
    bool userFound {false};

    do
    {
        space();

        print("Ingrese su nombre de usario: ");

        if(!readLine(userName, 16))
        {
            printError("ERROR: El nombre de usuario excede el límite de caracteres\n");
            continue;
        }

        userHost = searchHostByName(userName);
        userGuest = searchGuestByName(userName);

        if(userHost)
        {
            userIsHost = true;
            userFound = true;
        }
        else if(userGuest)
        {
            userFound = true;
        }
        else
        {
            printError("ERROR: Usuario no encontrado\n");
        }

    }
    while(!userFound);


    bool isPassword {false};
    char* userDoc = new char[10];

    do
    {
        print("Ingrese su documento: ");

        if(!readLine(userDoc, 10))
        {
            printError("ERROR: La informacion ingresada excede el límite de caracteres(10)\n");
            continue;
        }

        if(userIsHost)
        {
            isPassword = (userHost->getDocument() == String(userDoc));
        }
        else
        {
            isPassword = (userGuest->getDocument() == String(userDoc));
        }

        if(!isPassword)
        {
            printError("ERROR: Credencial incorrecta.\n");
        }
        


    }
    while(!isPassword);


    delete[] userDoc;
    delete[] userName;

    clearConsole();

    if(userIsHost)
    {
        hostProfile();
    }
    else
    {
        guestProfile();
    }
}



int main()
{

    loadAccomodations(accommodations);
    loadReservations(reservations, accommodations, accommodationMaxID, reservationMaxID);
    loadHost(hosts, accommodations);
    loadGuest(guests, reservations);  
    

    login();


    saveAllData(accommodations, reservations, hosts, guests);


    cleanupMemory(accommodations, reservations, hosts, guests);


    return 0;

}
