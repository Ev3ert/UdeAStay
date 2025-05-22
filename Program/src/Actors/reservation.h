#ifndef RESERVATION_H
#define RESERVATION_H

#include "../DataStructure/list.h"
#include "../DataStructure/string.h"
#include "../Utils/date.h"
#include "../Utils/ConUtils.h"

class Accommodation;

class Reservation
{
public:
    /// * Attributes

    unsigned int code;
    Accommodation *accommodation;
    String userName;
    Date startDate;
    int days;
    String paymentMethod;
    Date paymentDate;
    unsigned long amount;
    String anotations;


    /// * Constructors

   Reservation(unsigned int code, Accommodation *accommodation,
        const String &userName, const Date& startDate, 
        int days, const String& paymentMethod, const Date& paymentDate, unsigned long amount,
        const String& anotations);
    
    /// * Methods

    void GenerateVoucher();

};

#endif // RESERVATION_H
