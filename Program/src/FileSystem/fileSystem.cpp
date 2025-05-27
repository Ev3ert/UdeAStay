#include "fileSystem.h"
#include "../Actors/accommodation.h"
#include "../Actors/reservation.h"
#include "../Actors/host.h"
#include "../Actors/guest.h"
#include "../DataStructure/list.h"
#include "../DataStructure/string.h"
#include "../Utils/ConUtils.h"
#include "../Utils/date.h"
#include <iostream>
#include <fstream>


bool validateLineFields(const List<String>& data, unsigned int index, const String& fieldName)
{
    if(data.size() != index)
    {
        printError(String("Lista incompleta en") + fieldName + ". Esperados "
             + String::toString(index) + ", encontrados: " 
             + String::toString(data.size()) + "\n");
        
        return false;
    }
    return true;
}


Accommodation* findAccommodationById(const List<Accommodation*>& accommodations, int id) {
    for (unsigned int i = 0; i < accommodations.size(); i++) 
    {
        Accommodation* accommodation = *accommodations.get(i);

        if (accommodation && accommodation->getId() == id) 
        {
            return accommodation;
        }
    }
    return nullptr;
}


String amenitiesListToString(const List<String>& amenities)
{
    String result = "";
    for(unsigned int i = 0; i < amenities.size(); i++)
    {
        if(i > 0)
        {
            result += ",";
        }
        result += *amenities.get(i);
    }
    return result;
    
}


String dateToString(const Date& date)
{
    return String::toString(date.getDay()) + "/" + 
            String::toString(date.getMonth()) + "/" +
            String::toString(date.getYear());
}

String getHostAccommodationIds(const Host& host)
{
    String result = "";
    List<Accommodation*> accommodation = host.getAccommodations();

    for(unsigned int i = 0; i < accommodation.size(); i++)
    {
        if(i > 0)
        {
            result += ",";
        }
        result += String::toString((*accommodation.get(i))->getId());
    }
    return result;
}


void loadAccomodations(List<Accommodation*>& allAccommodations)
{
    std::ifstream accomArc(archiveAccomodations);    

    String line;
    List<String> data;

    if (!accomArc.is_open()) {
        printError("No se pudo abrir el archivo de alojamientos.\n");
        return;
    }

    while(String::getLine(accomArc, line))
    {
        data = line.split('|');
        

        if (!validateLineFields(data, 7, "Alojamientos")) {
            continue;
        }


        List<String> amenities = data.get(6)->split(',');


        Accommodation* newAccommodation {nullptr};
        try
        {
            // Create new Accommodation object in heap
            newAccommodation = new Accommodation(
                String::toInt(data.get(0)->getRawData()), // ID
                *data.get(1),                             // Name
                nullptr,                                  // Host (will be set later)
                *data.get(2),                            // Department
                *data.get(3),                            // Type
                *data.get(4),                            // Address
                String::toInt(data.get(5)->getRawData()), // Price per night
                amenities                                 // Amenities list
            );

            allAccommodations.insertEnd(newAccommodation);
        }
        catch(...)
        {
            if(newAccommodation != nullptr)
            {
                delete newAccommodation; 
            }
            printError("Error al crear el alojamiento\n");
        }
    }

    accomArc.close();

}


void loadReservations(List<Reservation*>& allReservations, const List<Accommodation*>& allAccommodations)
{
    std::ifstream resArc(archiveReservations);

    String line;
    List<String> data;

    if (!resArc.is_open()) {
        printError("No se pudo abrir el archivo de reservas.\n");
        return;
    }

    while(String::getLine(resArc, line))
    {
        if(line.size() == 0) continue; 

        data = line.split('|');

        if (!validateLineFields(data, 9, "Reservaciones"))
        {
            continue;
        }


        List<String> startDateSplit = data.get(3)->split('/');
        List<String> paymentDateSplit = data.get(6)->split('/');

        if (startDateSplit.size() != 3 || paymentDateSplit.size() != 3) {
            printError("Fecha de inicio o fecha de pago inválida en la reserva.\n");
            continue;
        }

        Date startDate(
            String::toInt(startDateSplit.get(0)->getRawData()),  // Day
            String::toInt(startDateSplit.get(1)->getRawData()),  // Month
            String::toInt(startDateSplit.get(2)->getRawData())   // Year
        );

        Date paymentDate(
            String::toInt(paymentDateSplit.get(0)->getRawData()), // Day
            String::toInt(paymentDateSplit.get(1)->getRawData()), // Month
            String::toInt(paymentDateSplit.get(2)->getRawData())  // Year
        );


        Accommodation* accommodation = findAccommodationById(allAccommodations, 
            String::toInt(data.get(1)->getRawData()));

        if (accommodation == nullptr) 
        {
            printError(String("Alojamiento no encontrado para la reserva con ID: ") 
                + data.get(0)->getRawData() + "\n");
            continue; // Skip this reservation if accommodation is not found
        }

        Reservation* newReservation = nullptr;

        try
        {
            // Create new Reservation object in heap
            newReservation = new Reservation(
                String::toInt(data.get(0)->getRawData()), // ID
                accommodation,                           // Accommodation 
                *data.get(2),                             // Guest name
                startDate,                                // Start date
                String::toInt(data.get(4)->getRawData()), // Days
                *data.get(5),                             // Payment method
                paymentDate,                              // Payment date
                String::toInt(data.get(7)->getRawData()), // Total price
                *data.get(8)                              // Annotations
            );

            allReservations.insertEnd(newReservation);

            accommodation->setReservation(newReservation);
        }
        catch(...)
        {
            if(newReservation != nullptr)
            {
                delete newReservation; 
            }
            printError("Error al crear la reserva\n");
            continue; // Skip this reservation if an error occurs
        }
        
    }

    resArc.close();
}


void loadHost(List<Host*>& allHosts, const List<Accommodation*>& accommodations)
{
    std::ifstream hostArc(archiveHost);

    String line;
    List<String> data;


    if (!hostArc.is_open()) {
        printError("No se pudo abrir el archivo Anfitriones.\n");
        return;
    }

    while(String::getLine(hostArc, line))
    {
        if (line.size() == 0) continue;

        data = line.split('|');

        if(!validateLineFields(data, 5, "Anfitriones"))
        {
            continue;
        }

        Host* newHost = nullptr;
        try
        {
            newHost = new Host(
                *data.get(0),                             // Name
                *data.get(1),                             // Document
                String::toInt(data.get(2)->getRawData()), // Antiquity in months
                String::toInt(data.get(3)->getRawData())  // Punctuation
            );

            List<String> accommodationIds = data.get(4)->split(',');

            for (unsigned int i = 0; i < accommodationIds.size(); i++)
            {
                int id = String::toInt(*accommodationIds.get(i));

                
                Accommodation* accommodation = findAccommodationById(accommodations, id);
                if (accommodation) {
                    newHost->addAccomodation(accommodation);
                    accommodation->setHost(newHost);
                }
            }

            allHosts.insertEnd(newHost);
        }
        catch(...)
        {
            if(newHost)
            {
                delete newHost;
            }
            printError("Error creando host\n");
        }
     
    }

    hostArc.close();
}


void loadGuest(List<Guest*>& allGuests, const List<Reservation*>& allReservations)
{
    std::ifstream guestArc(archiveGuest);

    String line;
    List<String> data;

    if (!guestArc.is_open()) {
        printError("No se pudo abrir el archivo huesped.\n");
        return;
    }

    while(String::getLine(guestArc, line))
    {
        if(line.size() == 0) continue;


        data = line.split('|');
        
        if(!validateLineFields(data, 4, "Huesped"))
        {
            continue;
        }

        Guest *newGuest = nullptr;
        try
        {
            // Create new Guest object in heap
            newGuest = new Guest(
                *data.get(0),                             // Name
                *data.get(1),                             // Document
                String::toInt(data.get(2)->getRawData()), // Antiquity
                String::toInt(data.get(3)->getRawData())  // Punctuation
            );

            // load reservations for the guest
            for (unsigned int i = 0; i < allReservations.size(); i++)
            {
                Reservation* reservation = *allReservations.get(i);
                if (reservation) 
                {
                    const String& guestName = reservation->getGuestName();
                    const String& newGuestName = newGuest->getName();
                    
                    if (guestName == newGuestName)
                    {
                        newGuest->addReservation(reservation);
                    }
                }
            }


            allGuests.insertEnd(newGuest);


        }
        catch(...)
        {
            if (newGuest) {
                delete newGuest;
            }
            printError("Error creando huésped\n");
        }
    }

    guestArc.close();
}


void saveAccommodations(const List<Accommodation*>& allAccommodations) {
    std::ofstream accomFile(archiveAccomodations);
    
    if (!accomFile.is_open()) {
        printError("No se pudo abrir el archivo de alojamientos para escritura.\n");
        return;
    }

    for (unsigned int i = 0; i < allAccommodations.size(); i++) {
        Accommodation* accommodation = *allAccommodations.get(i);
        if (!accommodation) continue; // skip nullptr
        
        // Format: ID|Name|Department|Type|Address|PricePerNight|Amenities
        accomFile << accommodation->getId() << "|"
                  << accommodation->getName().getRawData() << "|"
                  << accommodation->getDepartment().getRawData() << "|"
                  << accommodation->getType().getRawData() << "|"
                  << accommodation->getAddress().getRawData() << "|"
                  << accommodation->getPricePerNight() << "|"
                  << amenitiesListToString(accommodation->getAmenities()).getRawData();
        
        // only add a line if not is the last element
        if (i < allAccommodations.size() - 1) {
            accomFile << "\n";
        }
    }
    
    accomFile.close();
    
    if (accomFile.good()) {
        printSuccess("Alojamientos guardadas exitosamente.\n");
    } else {
        printError("Error al guardar alojamientos.\n");
    }
}


void saveReservations(const List<Reservation*>& allReservations) {
    std::ofstream resFile(archiveReservations);
    
    if (!resFile.is_open()) {
        printError("No se pudo abrir el archivo de reservaciones para escritura.\n");
        return;
    }

    for (unsigned int i = 0; i < allReservations.size(); i++) {
        Reservation* reservation = *allReservations.get(i);
        if (!reservation || !reservation->getAccommodation()) continue; 
        
        // Format: ID|AccommodationID|GuestName|StartDate|Days|PaymentMethod|PaymentDate|TotalPrice|Annotations
        resFile << reservation->getId() << "|"
                << reservation->getAccommodation()->getId() << "|"
                << reservation->getGuestName().getRawData() << "|"
                << dateToString(reservation->getStartDate()).getRawData() << "|"
                << reservation->getDays() << "|"
                << reservation->getPaymentMethod().getRawData() << "|"
                << dateToString(reservation->getPaymentDate()).getRawData() << "|"
                << reservation->getTotalPrice() << "|"
                << reservation->getAnotations().getRawData();
        
        // only add a line if not is the last element
        if (i < allReservations.size() - 1) {
            resFile << "\n";
        }
    }
    
    resFile.close();
    
    if (resFile.good()) {
        printSuccess("Reservaciones guardadas exitosamente.\n");
    } else {
        printError("Error al guardar reservaciones.\n");
    }
}


void saveHosts(const List<Host*>& allHosts) {
    std::ofstream hostFile(archiveHost);
    
    if (!hostFile.is_open()) {
        printError("No se pudo abrir el archivo de hosts para escritura.\n");
        return;
    }

    for (unsigned int i = 0; i < allHosts.size(); i++) {
        Host* host = *allHosts.get(i);
        if (!host) continue;
        
        // Format: Name|Document|Antiquity|Punctuation|AccommodationIDs
        hostFile << host->getName().getRawData() << "|"
                 << host->getDocument().getRawData() << "|"
                 << host->getAntiquity() << "|"
                 << host->getPuntuation() << "|"
                 << getHostAccommodationIds(*host).getRawData();
        
        // only add a line if not is the last element
        if (i < allHosts.size() - 1) {
            hostFile << "\n";
        }
    }
    
    hostFile.close();
    
    if (hostFile.good()) {
        printSuccess("Hosts guardados exitosamente.\n");
    } else {
        printError("Error al guardar hosts.\n");
    }
}


void saveGuests(const List<Guest*>& allGuests) {
    std::ofstream guestFile(archiveGuest);
    
    if (!guestFile.is_open()) {
        printError("No se pudo abrir el archivo de huéspedes para escritura.\n");
        return;
    }

    for (unsigned int i = 0; i < allGuests.size(); i++) {
        Guest* guest = *allGuests.get(i);
        if (!guest) continue; 
        
        // Format: Name|Document|Antiquity|Punctuation
        guestFile << guest->getName().getRawData() << "|"
                  << guest->getDocument().getRawData() << "|"
                  << guest->getAntiquity() << "|"
                  << guest->getPuntuation();
        
        // only add a line if not is the last element
        if (i < allGuests.size() - 1) {
            guestFile << "\n";
        }
    }
    
    guestFile.close();
    
    if (guestFile.good()) {
        printSuccess("Huéspedes guardados exitosamente.\n");
    } else {
        printError("Error al guardar huéspedes.\n");
    }
}


void saveAllData(const List<Accommodation*>& accommodations,
                 const List<Reservation*>& reservations,
                 const List<Host*>& hosts,
                 const List<Guest*>& guests) {
    
    print("Guardando datos...\n");
    
    saveAccommodations(accommodations);
    saveHosts(hosts);           
    saveReservations(reservations);  
    saveGuests(guests);         
    
    printSuccess("Todos los datos han sido guardados exitosamente.\n");
}



void cleanupMemory(List<Accommodation*>& accommodations, 
                  List<Reservation*>& reservations,
                  List<Host*>& hosts, 
                  List<Guest*>& guests)
{

    for (unsigned int i = 0; i < accommodations.size(); i++) {
        delete *accommodations.get(i);
    }
    accommodations.clear();


    for (unsigned int i = 0; i < reservations.size(); i++) {
        delete *reservations.get(i);
    }
    reservations.clear();


    for (unsigned int i = 0; i < hosts.size(); i++) {
        delete *hosts.get(i);
    }
    hosts.clear();

  
    for (unsigned int i = 0; i < guests.size(); i++) {
        delete *guests.get(i);
    }
    guests.clear();
}
