#include "reservation.h"
#include "accommodations.h"

Reservation::Reservation(unsigned int code, Accommodation *accommodation,
        const String &userName, const Date& startDate, 
        int days, const String& paymentMethod, const Date& paymentDate, unsigned long amount,
        const String& anotations)
        : code(code), accommodation(accommodation), userName(userName), startDate(startDate), 
        days(days), paymentMethod(paymentMethod), paymentDate(paymentDate),
        amount(amount), anotations(anotations) {}


/// * Methods
  
void Reservation::GenerateVoucher() 
    {
        printTitle("Voucher", '=');
        printDivider('=');
        space();

        printInfo("- Código: ", code);
        printInfo("- Alojamiento: ", accommodation->name.getRawData());
        printInfo("- Usuario: ", userName.getRawData());
        print("- \033[1;1mFecha de inicio: \033[0m");
        startDate.printDate();
        space();
        printInfo("- Días: ", days);
        printInfo("- Método de pago: ", paymentMethod.getRawData());
        print("- \033[1;1mFecha de pago: \033[0m");
        paymentDate.printDate();
        space();
        printInfo("- Monto: $", amount);
        printInfo("- Anotaciones: ", anotations.getRawData());

        space();
        
        printDivider('=');
    }
