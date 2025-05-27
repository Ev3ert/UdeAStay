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

void hostProfile()
{
    printTitle(String("Bienvenido ") + userHost->getName(), '=');
    printDivider();
    
}

void guestProfile()
{
    printTitle(String("Bienvenido ") + userGuest->getName(), '=');
    printDivider();


}


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
    loadReservations(reservations, accommodations);
    loadHost(hosts, accommodations);
    loadGuest(guests, reservations);  
    

    login();


    cleanupMemory(accommodations, reservations, hosts, guests);


    return 0;

}
