#ifndef RESERVATION_H
#define RESERVATION_H

#include "../DataStructure/string.h"
#include "../Utils/date.h"

class Accommodation;

class Reservation
{
private:
    /// * Properties

    unsigned int id;
    Accommodation *accommodation;
    String guestName;
    Date startDate;
    int days;
    String paymentMethod;
    Date paymentDate;
    unsigned long totalPrice;
    String anotations;

public:
    /// * Constructors

    Reservation(unsigned int id, Accommodation *accommodation, const String &guestName,
                const Date &startDate, int days, const String &paymentMethod,
                const Date &paymentDate, unsigned long totalPrice, const String &anotations);

    /// * Destructors

    ~Reservation();

    /// * Methods

    // Prints a voucher with reservation information
    void generateVoucher() const;

    // Show some information from teh resercation
    void viewInfo() const;

    // Getters
    unsigned int getId() const;
    Accommodation *getAccommodation() const;
    const String &getGuestName() const;
    const Date &getStartDate() const;
    int getDays() const;
    const String &getPaymentMethod() const;
    const Date &getPaymentDate() const;
    unsigned long getTotalPrice() const;
    const String &getAnotations() const;

    // setters
    void setAccomodation(Accommodation *newAccommodation);
};

#endif // RESERVATION_H
