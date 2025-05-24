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

    void addAccomodation(Accommodation *Accommodation);

    void removeAccomodation(unsigned int id);

    void cancelReservation(unsigned int id);

    void consultReservations();

    /// void updateHistoric(Date cutOffDate);


};


#endif // HOST_H
