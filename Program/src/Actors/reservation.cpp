#include "reservation.h"
#include "accommodation.h"
#include "../Utils/ConUtils.h"


Reservation::Reservation(unsigned int id, const Accommodation* accommodation, const String& guestName,
                           const Date& startDate, int days, const String& paymentMethod,
                           const Date& paymentDate, unsigned long totalPrice, const String& anotations)
    : id(id), accommodation(accommodation), guestName(guestName), startDate(startDate),
      days(days), paymentMethod(paymentMethod), paymentDate(paymentDate),
      totalPrice(totalPrice), anotations(anotations) {}


/// * Methods

void Reservation::generateVoucher() const
{
    printTitle("Comprobante de reserva", '-');
    printInfo("ID de reserva: ", String::toString(id).getRawData());
    printInfo("Acomodación: ", accommodation->getName().getRawData());
    printInfo("Nombre del huésped: ", guestName.getRawData());
    printInfo("Fecha de inicio: ", startDate.getFormatDate().getRawData());
    printInfo("Fecha de fin: ", startDate.addDays(days - 1).getFormatDate().getRawData());
    printInfo("Días reservados: ", String::toString(days).getRawData());
    printInfo("Método de pago: ", paymentMethod.getRawData());
    printInfo("Fecha de pago: ", paymentDate.getFormatDate().getRawData());
    printInfo("Precio total: ", String::toString(totalPrice).getRawData());
    printInfo("Anotaciones: ", anotations.getRawData());

}

// Getters
const Date& Reservation::getStartDate() const
{
    return startDate;
}

int Reservation::getDays() const
{
    return days;
}
