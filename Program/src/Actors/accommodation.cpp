#include "accommodation.h"
#include "reservation.h"
#include "host.h"
#include "../Utils/date.h"
#include "../Utils/ConUtils.h"

/// * Constructors

Accommodation::Accommodation(unsigned int id, const String& name, const Host* host, 
                               const String& department, const String& type, 
                               const String& address, unsigned long pricePerNight, 
                               List<String>& amenities)
    : id(id), name(name), host(host), department(department), type(type), 
      address(address), pricePerNight(pricePerNight), amenities(amenities), 
      reservations() {}


/// * Methods
bool Accommodation::isAvailable(const Date& date, int days) const
{   
    if (days <= 0) return false;

    Date endDate = date.addDays(days);

    for (unsigned int i = 0; i < reservations.size(); i++)
    {
        // desreference the pointer to get the object address
        Reservation *reservation = *reservations.get(i);
        Date resStart = reservation->getStartDate();
        Date resEnd = resStart.addDays(reservation->getDays());

        // check if the reservation date is in the interval [date, date + days)
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

void Accommodation::viewDetails() const
{
    printDivider('-');
    printCentered(String("Alojamiento: ") + name);

    printInfo("Anfitrion        : ", host->getName());
    printInfo("Departamento     : ", department);
    printInfo("Direccion        : ", address);
    printInfo("Precio por noche : ", pricePerNight);
    printInfo("Amenidades       : ", amenities);
}


bool Accommodation::deleteReservation(unsigned int id)
{
    for (unsigned int i = 0; i < reservations.size(); i++)
    {
        Reservation *reservation = *reservations.get(i);
        if (reservation->getId() == id)
        {
            reservations.deleteByPosition(i);
            printSuccess("Reservación eliminada exitosamente\n");
            return true;
        }
    }
    
    return false;
    space();
}


// Getters
unsigned int Accommodation::getId() const
{
    return id;
}
const String& Accommodation::getName() const
{
    return name;
}
const Host* Accommodation::getHost() const
{
    return host;
}
const String& Accommodation::getDepartment() const
{
    return department;
}
const String& Accommodation::getType() const
{
    return type;
}
const String& Accommodation::getAddress() const
{
    return address;
}
const unsigned int Accommodation::getPricePerNight() const
{
    return pricePerNight;   
}
const List<String>& Accommodation::getAmenities() const
{
    return amenities;
}
const List<Reservation*>& Accommodation::getReservations() const
{
    return reservations;
}


// Setters

void Accommodation::SetReservation(Reservation* reservation)
{
    reservations.insertEnd(reservation);
}

