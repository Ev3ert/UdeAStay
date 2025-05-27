#include "guest.h"
#include "reservation.h"
#include "accommodation.h"
#include "../Utils/ConUtils.h"
#include "../DataStructure/string.h"

/// * Constructors

Guest::Guest(const String& document, const String& name, int antiquity, int puntuation)
    : document(document), name(name), antiquity(antiquity), puntuation(puntuation) {}


/// * Methods

void Guest::addReservation(Reservation* reservation)
{
    reservations.insertEnd(reservation);
}

void Guest::cancelReservation(unsigned int id)
{
    for (unsigned int i = 0; i < reservations.size(); i++)
    {
        Reservation* reservation = *reservations.get(i);
        if (reservation->getId() == id)
        {
            reservations.deleteByPosition(i);
            return;
        }
    }
}

bool Guest::checkAvailability(Date date, int days) const
{
    if (days <= 0) return false;

    Date endDate = date.addDays(days);

    for (unsigned int i = 0; i < reservations.size(); i++)
    {
        // desreference the pointer to get the object address
        Reservation *reservation = *reservations.get(i);
        Date resStart = reservation->getStartDate();
        Date resEnd = resStart.addDays(reservation->getDays());


        // TODO: rewrite this condition to be more readable
        if (!(endDate <= resStart || date >= resEnd))
        {
            return false;
        }
    }

    return true;
}


void Guest::viewReservations() const
{
    if (reservations.isEmpty())
    {
        printError("No hay reservas para mostrar.");
        return;
    }

    printTitle((String("Reservas de ") + name).getRawData(), '-', 40);
    
    for (unsigned int i = 0; i < reservations.size(); i++)
    {
        Reservation* reservation = *reservations.get(i);

        printTitle(String("Reserva #") + String::toString(i + 1), '-', 30);
        reservation->viewInfo();
    }
}

// getters
const String& Guest::getDocument() const
{
    return document;
}

const String& Guest::getName() const
{
    return name;
}

int Guest::getAntiquity() const
{
    return antiquity;
}

int Guest::getPuntuation() const
{
    return puntuation;
}
