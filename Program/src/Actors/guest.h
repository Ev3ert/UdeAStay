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

    Guest(const String& name, const String& document, int antiquity, int puntuation);


    /// * Methods
    
    void addReservation(Reservation* reservation);

    void cancelReservation(int id);
    
    // Funtion to check if the Guest dont have reservations in the interval [date, date + days]
    bool checkAvailability(Date date,int days);
};

#endif // GUEST_H




