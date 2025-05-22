#ifndef HOST_H
#define HOST_H

#include "../DataStructure/list.h"
#include "../DataStructure/string.h"

class Accommodation;

class Host
{
public:
    /// * Attributes
    String name;
    String document;
    int antiquity;
    int puntuation;

    List<Accommodation*> accommodations;


    /// * Constructors 

    Host(const String& name, const String& document, int antiquity, int puntuation);


    /// * Methods

    // void addAccommodation(accomodation){}

    // void removeAccommodation(id){}

    // void cancelReservation(id){}

    // void consumeReservation(id){}

    // void updateHistoric()({}
};


#endif // HOST_H
