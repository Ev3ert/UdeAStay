#ifndef GUEST_H
#define GUEST_H

#include "../DataStructure/string.h"

class Reservation;
class Date;

class Guest
{
private:
    /// * Properties

    String Document;
    String name;
    int antiquity; // in months
    int puntuation; // how can a guest be rated?
    List<Reservation*> reservations; 

public:
    /// * Constructors

    Guest(const String& document, const String& name, int antiquity, int puntuation);

    /// * Methods

    void addReservation(Reservation* reservation);

    void cancelReservation(unsigned int id);

    bool checkAvailability(Date date, int days) const;

    void viewReservations() const;

    // Getters

    const String& getDocument() const;
    const String& getName() const;
    int getAntiquity() const;
    int getPuntuation() const;

};


#endif // GUEST_H
