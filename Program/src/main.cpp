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



int main()
{

    loadAccomodations(accommodations);
    loadReservations(reservations, accommodations);
    loadHost(hosts, accommodations);
    loadGuest(guests, reservations);  
    

    for(unsigned int i = 0; i < accommodations.size(); i++)
    {
        Accommodation *accommodation = *accommodations.get(i);
        accommodation->viewDetails();
    }

    pause();
    clearConsole();


    printTitle("loading reservations", '*', 50);

    for(unsigned int i = 0; i < reservations.size(); i++)
    {
        Reservation *reservation = *reservations.get(i);
        reservation->generateVoucher();
    }

    pause();
    clearConsole();

    printTitle("loading hosts", '*', 50);
    for(unsigned int i = 0; i < hosts.size(); i++)
    {
        Host *host = *hosts.get(i);
        printInfo("Host: ", host->getName());
        printInfo("Document: ", host->getDocument());
        printInfo("Antiquity: ", String::toString(host->getAntiquity()));
        printInfo("Puntuation: ", String::toString(host->getPuntuation()));

        host->consultReservations();
        space();
    }

    pause();
    clearConsole();
    printTitle("loading guests", '*', 50);

    for(unsigned int i = 0; i < guests.size(); i++)
    {
        Guest *guest = *guests.get(i);
        printInfo("Guest: ", guest->getName());
        printInfo("Document: ", guest->getDocument());
        printInfo("Antiquity: ", String::toString(guest->getAntiquity()));
        printInfo("Puntuation: ", String::toString(guest->getPuntuation()));

        guest->viewReservations();
        space();
    }

    pause();
    clearConsole();

    Host* host = new Host("Juancho polo", "893893289", 7, 9);
    hosts.insertEnd(host);

    List<String> amenities;
    amenities.insertEnd("le dan las buenas noches");

    Accommodation* newAccom = new Accommodation(999, "Hotel Nuevo", host, 
                                                   "Bogotá", "Hotel", "Calle 123", 
                                                   150000, amenities);

    accommodations.insertEnd(newAccom);
    host->addAccomodation(newAccom);

    saveAllData(accommodations, reservations, hosts, guests);


    cleanupMemory(accommodations, reservations, hosts, guests);


    return 0;

}
