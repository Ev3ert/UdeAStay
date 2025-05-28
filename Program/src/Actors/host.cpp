#include "host.h"
#include "accommodation.h"
#include "reservation.h"
#include "../Utils/ConUtils.h"
#include "../FileSystem/fileSystem.h"

/// * Constructors

Host::Host(const String& name, const String& document, int antiquity, int puntuation, const Date& cutOffDate)
    : name(name), document(document), antiquity(antiquity), puntuation(puntuation), cutOffDate(cutOffDate) {}


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

    printError(String("No se encontró el alojamiento con ID: ") + String::toString(id));
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

    printError(String("No se encontró la reservación con ID: ")
             + String::toString(id));
    space();
}

void Host::consultReservations(const Date& startRange, 
                             const Date& endRange, 
                             bool useDateFilter)
{
    if(accommodations.isEmpty())
    {
        printError("No hay alojamientos para mostrar.\n");
        return;
    }

    bool foundAny = false;
    for(unsigned int i = 0; i < accommodations.size(); i++)
    {
        Accommodation *accommodation = *accommodations.get(i);
        
        printTitle(String("Alojamiento ") + String::toString(i + 1), '-', 50);
        printDivider('-', 50);
        printInfo("Alojamiento: ", accommodation->getName());
        printCentered("---- Reservaciones ----", 50);

        List<Reservation*> reservations = accommodation->getReservations();

        if(reservations.isEmpty())
        {
            printError("No hay reservaciones para mostrar.\n");
            continue;
        }

        bool foundInAccommodation = false;
        for(unsigned int j = 0; j < reservations.size(); j++)
        {
            Reservation *reservation = *reservations.get(j);
            
            if(useDateFilter)
            {
                Date resDate = reservation->getStartDate();
                if(resDate >= startRange && resDate <= endRange)
                {
                    reservation->viewInfo();
                    foundInAccommodation = true;
                    foundAny = true;
                }
            }
            else
            {
                reservation->viewInfo();
                foundInAccommodation = true;
                foundAny = true;
            }
        }

        if(!foundInAccommodation && useDateFilter)
        {
            printError("No hay reservaciones en el rango de fechas especificado.\n");
        }
    }

    if(!foundAny)
    {
        printError("No se encontraron reservaciones.\n");
    }

    space();
}


void Host::updateHistoric(Date newCutOffDate, List<Reservation*>& globalReservations)
{
    List<Reservation*> historicReservations;

    for(unsigned int i = 0; i < accommodations.size(); i++)
    {
        Accommodation* accommodation = *accommodations.get(i);
        List<Reservation*> resList = accommodation->getReservations();

        for(int j = resList.size() - 1; j >= 0; --j)
        {
            Reservation* res = *resList.get(j);
            Date endDate = res->getStartDate().addDays(res->getDays() - 1);

            if(endDate < newCutOffDate)
            {
                historicReservations.insertEnd(res);

                // remove of global reservations
                for(int k = globalReservations.size() - 1; k >= 0; --k) {
                    if((*globalReservations.get(k))->getId() == res->getId()) {
                        globalReservations.deleteByPosition(k);
                        break;
                    }
                }

                resList.deleteByPosition(j);
            }
        }
    }

    saveHistoricReservations(historicReservations);

    cutOffDate = newCutOffDate;

    printSuccess("Histórico actualizado y reservaciones antiguas archivadas.\n");
}



// getters
const String& Host::getDocument() const
{
    return document;
}

const String& Host::getName() const
{
    return name;
}

int Host::getAntiquity() const
{
    return antiquity;
}

int Host::getPuntuation() const
{
    return puntuation;
}

const Date& Host::getCutOffDate() const
{
    return cutOffDate;
}

List<Accommodation*> Host::getAccommodations() const
{
    return accommodations;
}



// Setters

void Host::setAccommodations(const List<Accommodation*>& accommodations)
{
    this->accommodations = accommodations;
}




