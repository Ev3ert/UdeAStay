#ifndef GUEST_H
#define GUEST_H

#include "../DataStructure/string.h"

class Reservation;
class Date;

class Guest
{
private:
    /// * Properties

    String name;
    String document;
    int antiquity; // in months
    int puntuation; // how can a guest be rated?
    List<Reservation*> reservations; 

public:
    /// * Constructors

    Guest(const String& name, const String& document, int antiquity, int puntuation);

    /// * Methods

    // Add reservatuions to the list
    void addReservation(Reservation* reservation);

    // Remove reservations from the list by their ID
    void cancelReservation(unsigned int id);

    // Check if you can reserve in a date range
    bool checkAvailability(Date date, int days) const;

    // Prints all reservations from this Guest
    void viewReservations() const;


    // Getters

    const String& getDocument() const;
    const String& getName() const;
    int getAntiquity() const;
    int getPuntuation() const;

};


#endif // GUEST_H
