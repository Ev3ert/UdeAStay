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

/*
This Script not is the maraville in performance, 
but it is easy to understand.
*/



void loadAccomodations(List<Accommodation*>& allAccommodations)
{
    std::ifstream accomArc(archiveAccomodations);    

    String line;
    List<String> data;

    if (!accomArc.is_open()) {
        printError("No se pudo abrir el archivo.\n");
        return;
    }

    while(String::getLine(accomArc, line))
    {
        data = line.split('|');
        
        List<String> amenities = data.get(6)->split(',');

        // Create new Accommodation object in heap
        Accommodation* newAccommodation = new Accommodation(
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

    accomArc.close();

}


void loadReservations(List<Reservation*>& allReservations, const List<Accommodation*>& allAccommodations)
{
    std::ifstream resArc(archiveReservations);

    String line;
    List<String> data;

    if (!resArc.is_open()) {
        printError("No se pudo abrir el archivo.\n");
        return;
    }

    while(String::getLine(resArc, line))
    {
        data = line.split('|');

        List<String> startSplit = data.get(3)->split('/');
        Date startDate(
            String::toInt(startSplit.get(0)->getRawData()),  // Day
            String::toInt(startSplit.get(1)->getRawData()),  // Month
            String::toInt(startSplit.get(2)->getRawData())   // Year
        );

        List<String> paymentSplit = data.get(6)->split('/');
        Date paymentDate(
            String::toInt(paymentSplit.get(0)->getRawData()), // Day
            String::toInt(paymentSplit.get(1)->getRawData()), // Month
            String::toInt(paymentSplit.get(2)->getRawData())  // Year
        );

        // Create new Reservation object in heap
        Reservation* newReservation = new Reservation(
            String::toInt(data.get(0)->getRawData()), // ID
            nullptr,                                  // Accommodation (will be set later)
            *data.get(2),                             // Guest name
            startDate,                                // Start date
            String::toInt(data.get(4)->getRawData()), // Days
            *data.get(5),                             // Payment method
            paymentDate,                              // Payment date
            String::toInt(data.get(7)->getRawData()), // Total price
            *data.get(8)                              // Annotations
        );

        allReservations.insertEnd(newReservation);


        // Set the accommodation for the reservation
        unsigned int accommodationId = String::toInt(data.get(1)->getRawData());
        for (unsigned int i = 0; i < allAccommodations.size(); i++)  
        {
            Accommodation* accommodation = *allAccommodations.get(i);
            if (accommodation->getId() == accommodationId)
            {
                newReservation->setAccomodation(accommodation);
                accommodation->setReservation(newReservation);
                break; // Found the accommodation, no need to continue
            }
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
        printError("No se pudo abrir el archivo.\n");
        return;
    }

    while(String::getLine(hostArc, line))
    {
        data = line.split('|');

        // Create new Host object in heap
        Host* newHost = new Host(
            *data.get(0),                             // Name
            *data.get(1),                             // Document
            String::toInt(data.get(2)->getRawData()), // Antiquity in months
            String::toInt(data.get(3)->getRawData())  // Punctuation
        );


        // Set the accommodations list for the host
        List<String> accommodationIds = data.get(4)->split(',');
        for (unsigned int i = 0; i < accommodationIds.size(); i++)
        {
            int id = String::toInt(*accommodationIds.get(i));
            for (unsigned int j = 0; j < accommodations.size(); j++)
            {
                Accommodation* accommodation = *accommodations.get(j);
                if (accommodation->getId() == id)
                {
                    newHost->addAccomodation(accommodation);
                    accommodation->setHost(newHost); // Set the host for the accommodation
                    break; // Found the accommodation, no need to continue
                }
            }
        }

        allHosts.insertEnd(newHost);
    }

    hostArc.close();
}

void loadGuest(List<Guest*>& allGuests, List<Reservation*>& allReservations)
{
    std::ifstream guestArc(archiveGuest);

    String line;
    List<String> data;

    if (!guestArc.is_open()) {
        printError("No se pudo abrir el archivo.\n");
        return;
    }

    while(String::getLine(guestArc, line))
    {
        data = line.split('|');

        // Create new Guest object in heap
        Guest* newGuest = new Guest(
            *data.get(0),                             // Name
            *data.get(1),                             // Document
            String::toInt(data.get(2)->getRawData()), // Antiquity
            String::toInt(data.get(3)->getRawData())  // Punctuation
        );

        allGuests.insertEnd(newGuest);

        // load reservations for the guest
        for (unsigned int i = 0; i < allReservations.size(); i++)
        {
            Reservation* reservation = *allReservations.get(i);
            if (reservation->getGuestName() == newGuest->getName())
            {
                newGuest->addReservation(reservation);
            }
        }
        

    }


    guestArc.close();
}


