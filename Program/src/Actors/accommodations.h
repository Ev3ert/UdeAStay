#ifndef ACCOMMODATIONS_H
#define ACCOMMODATIONS_H

#include "../DataStructure/list.h"
#include "../DataStructure/string.h"
#include "../Utils/date.h" 
#include "host.h"

class Reservation;

class Accommodation
{
public:
    /// * Attributes

    unsigned int code;
    String name;
    const Host *host;
    String department;
    String Type;
    String address;
    unsigned long pricePerNight;
    List<String> amenities;
    List<Reservation*> reservations;


    /// * Constructors 
    Accommodation(unsigned int code, const String& name, const Host* host, const String& department,
                  const String& Type, const String& address, unsigned long pricePerNight);

    /// * Methods
    bool isAvailable(Date date, int days);

    // void viewDetails() {}

};


#endif // ACCOMMODATIONS_H
