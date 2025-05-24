#ifndef HOST_H
#define HOST_H

#include "../DataStructure/string.h"
#include "../DataStructure/list.h"

class Date;
class Accommodation;

class Host
{
private:
    /// * Propierties

    String Document;
    String name;
    int antiquity; // in months
    int puntuation; 

    List<Accommodation*> accommodations;

public:
    /// * Constructor

    Host(const String& name, const String& document, int antiquity, int puntuation);

    /// * Methods

    // add an accommodation to the list
    void addAccomodation(Accommodation *Accommodation);

    // remove an accomodation by their ID
    void removeAccomodation(unsigned int id);

    // cancel a reservation by their ID
    void cancelReservation(unsigned int id);

    // Prints all reservation from all accommodations
    void consultReservations();

    // Update de historic archive
    /// void updateHistoric(Date cutOffDate);

    const String& getDocument() const;
    const String& getName() const;
    int getAntiquity() const;
    int getPuntuation() const;

};


#endif // HOST_H
