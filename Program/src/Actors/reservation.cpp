#include "reservation.h"
#include "accommodation.h"
#include "../Utils/ConUtils.h"
#include "../Utils/metrics.h"

Reservation::Reservation(unsigned int id, Accommodation *accommodation, const String &guestName,
                         const Date &startDate, int days, const String &paymentMethod,
                         const Date &paymentDate, unsigned long totalPrice, const String &anotations)
    : id(id), accommodation(accommodation), guestName(guestName), startDate(startDate),
      days(days), paymentMethod(paymentMethod), paymentDate(paymentDate),
      totalPrice(totalPrice), anotations(anotations)
{
    Metrics::addMemory(sizeof(Reservation));
}

Reservation::~Reservation()
{
    Metrics::removeMemory(sizeof(Reservation));
}

/// * Methods

void Reservation::generateVoucher() const
{
    printTitle("COMPROBANTE DE RESERVA", '=', 60);
    space();

    printTitle("DETALLES DE LA RESERVA", '-', 60);
    printInfo("ID de reserva    : ", String::toString(id));
    printInfo("Acomodación      : ", accommodation->getName());
    printInfo("Nombre huésped   : ", guestName);
    space();

    printTitle("FECHAS", '-', 60);
    printInfo("Fecha inicio     : ", startDate.getFormatDate());
    printInfo("Fecha fin        : ", startDate.addDays(days - 1).getFormatDate());
    printInfo("Días reservados  : ", String::toString(days));
    space();

    printTitle("INFORMACIÓN DE PAGO", '-', 60);
    printInfo("Método de pago   : ", paymentMethod);
    printInfo("Fecha de pago    : ", paymentDate.getFormatDate());
    printInfo("Precio total     : $", String::toString(totalPrice));
    space();

    if (anotations.getRawData()[0] != '\0')
    {
        printTitle("ANOTACIONES", '-', 60);
        printInfo("", anotations);
        space();
    }

    printDivider('=', 60);
}

void Reservation::viewInfo() const
{
    printInfo("ID             : ", id);
    printInfo("Alojamiento    : ", accommodation->getName());
    printInfo("Fecha inicio   : ", startDate.getFormatDate());
    printInfo("Días           : ", days);
    printInfo("Precio total   : $", totalPrice);
    space();
}

// Getters

unsigned int Reservation::getId() const
{
    return id;
}

Accommodation *Reservation::getAccommodation() const
{
    return accommodation;
}

const String &Reservation::getGuestName() const
{
    return guestName;
}

const Date &Reservation::getStartDate() const
{
    return startDate;
}

int Reservation::getDays() const
{
    return days;
}

const String &Reservation::getPaymentMethod() const
{
    return paymentMethod;
}

const Date &Reservation::getPaymentDate() const
{
    return paymentDate;
}

unsigned long Reservation::getTotalPrice() const
{
    return totalPrice;
}

const String &Reservation::getAnotations() const
{
    return anotations;
}

// setters

void Reservation::setAccomodation(Accommodation *newAccommodation)
{
    accommodation = newAccommodation;
}
