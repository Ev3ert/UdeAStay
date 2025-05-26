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
    loadReservations(reservations);
    loadHost(hosts, accommodations);

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

    
    

    return 0;

}
