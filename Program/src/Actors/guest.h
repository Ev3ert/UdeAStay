#ifndef GUEST_H
#define GUEST_H

#include "../DataStructure/list.h"
#include "../DataStructure/string.h"
#include "../Utils/date.h"
#include "reservation.h"

class Guest
{
public:
    /// * Attributes

    String name;
    String document;
    int antiquity;
    int puntuation; // i dont know how a guest can have a puntuation
    List<Reservation*> Reservations;


    /// * Constructors

    Guest(const String& name, String& document, int antiquity, int puntuation)
        : name(name), document(document), antiquity(antiquity), puntuation(puntuation) {}


    /// * Methods
    
    void addReservation(Reservation* reservation){
        Reservations.insertEnd(reservation);
    }

    void cancelReservation(int id){
        for(unsigned int i = 0; i < Reservations.size(); i++)
        {   
            // desreference the pointer to get the object address
            Reservation *reservation = *Reservations.get(i);

            if(reservation->code == id)
            {
                Reservations.deleteByPosition(i);
                return;
            }
        }
    }
    
    // Funtion to check if the Guest dont have reservations in the interval [date, date + days]
    bool checkAvailability(Date date,int days)
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
};

#endif // GUEST_H




