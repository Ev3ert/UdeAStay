#include "guest.h"

/// * Constructors

Guest::Guest(const String &name, const String &document, int antiquity, int puntuation)
    : name(name), document(document), antiquity(antiquity), puntuation(puntuation) {}

/// * Methods

void Guest::addReservation(Reservation *reservation)
{
    Reservations.insertEnd(reservation);
}

void Guest::cancelReservation(int id)
{
    for (unsigned int i = 0; i < Reservations.size(); i++)
    {
        // desreference the pointer to get the object address
        Reservation *reservation = *Reservations.get(i);

        if (reservation->code == id)
        {
            Reservations.deleteByPosition(i);
            return;
        }
    }
}

bool Guest::checkAvailability(Date date, int days)
{   
        Date endDate = date.addDays(days);

        for(unsigned int i = 0; i < Reservations.size(); i++)
        {
            Reservation *reservation = *Reservations.get(i);
            Date resStart = reservation->startDate;
            Date resEnd = resStart.addDays(reservation->days);


            if(!(endDate <= resStart || date >= resEnd))
            {
                return false;
            }
        }

        return true;
    }
