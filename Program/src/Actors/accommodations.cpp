#include "accommodations.h"
#include "reservation.h"

/// * Constructors

Accommodation::Accommodation(unsigned int code, const String &name, const Host *host,
                           const String &department, const String &Type,
                           const String &address, unsigned long pricePerNight)
    : code(code), name(name), host(host), department(department),
      Type(Type), address(address), pricePerNight(pricePerNight),
      amenities(), reservations() {}

      /// * Methods

bool Accommodation::isAvailable(Date date, int days)
{
    Date endDate = date.addDays(days);

    for (unsigned int i = 0; i < reservations.size(); i++)
    {
        // desreference the pointer to get the object address
        Reservation *reservation = *reservations.get(i);
        Date resStart = reservation->startDate;
        Date resEnd = resStart.addDays(reservation->days);

        // check if the reservation date is in the interval [date, date + days]
        // ! This is so much confusing, but the logic is:
        // If it is NOT the case that the new date ends before the reservations date
        // and it it NOT the case that the new date starts after the reservations date
        // then they collide
        // TODO: rewrite this condition to be more readable
        if (!(endDate <= resStart || date >= resEnd))
        {
            return false;
        }
    }

    return true;
}
