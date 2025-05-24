#include "host.h"
#include "accommodation.h"
#include "reservation.h"
#include "../Utils/ConUtils.h"

/// * Constructors

Host::Host(const String& document, const String& name, int antiquity, int puntuation)
    : Document(document), name(name), antiquity(antiquity), puntuation(puntuation) {}


/// * Methods

void Host::addAccomodation(Accommodation *accommodation)
{
    accommodations.insertEnd(accommodation);
}

void Host::removeAccomodation(unsigned int id)
{
    for(unsigned int i = 0; i < accommodations.size(); i++)
    {
        Accommodation *accommodation = *accommodations.get(i);
        if(accommodation->getId() == id)
        {
            accommodations.deleteByPosition(i);
            printSuccess("Alojamiento eliminado exitosamente\n");
            return;
        }
    }

    printError((String("No se encontró el alojamiento con ID: ") + String::toString(id)).getRawData());
    space();
}

void Host::cancelReservation(unsigned int id)
{
    for(unsigned int i = 0; i < accommodations.size(); i++)
    {
        Accommodation *accommodation = *accommodations.get(i);
        
        if(accommodation->deleteReservation(id))
        {
            return;
        }
    }

    printError((String("No se encontró la reservación con ID: ")
             + String::toString(id)).getRawData());
    space();
}

void Host::consultReservations()
{
    if(accommodations.isEmpty())
    {
        printError("No hay alojamientos para mostrar. \n");
        return;
    }

    for(unsigned int i = 0; i < accommodations.size(); i++)
    {
        Accommodation *accommodation = *accommodations.get(i);
        
        printTitle((String("Alojamiento ") + String::toString(i + 1)).getRawData(), '-', 50);
        printDivider('-', 50);
        printInfo("Alojamiento: ", accommodation->getName());
        printCentered("---- Reservaciones ----", 50);

        List<Reservation*> reservations = accommodation->getReservations();

        if(reservations.isEmpty())
        {
            printError("No hay reservaciones para mostrar. \n");
            continue;
        }

        for(unsigned int j = 0; j < reservations.size(); j++)
        {
            Reservation *reservation = *reservations.get(j);
            reservation->viewInfo();
        }
    }
}




