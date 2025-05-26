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


void loadReservations(List<Reservation*>& allReservations)
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

        Date startDate(
            String::toInt(data.get(2)->split('/').get(0)->getRawData()), // Day
            String::toInt(data.get(2)->split('/').get(1)->getRawData()), // Month
            String::toInt(data.get(2)->split('/').get(2)->getRawData())  // Year
        );

        Date paymentDate(
            String::toInt(data.get(5)->split('/').get(0)->getRawData()), // Day
            String::toInt(data.get(5)->split('/').get(1)->getRawData()), // Month
            String::toInt(data.get(5)->split('/').get(2)->getRawData())  // Year
        );

        // Create new Reservation object in heap
        Reservation* newReservation = new Reservation(
            String::toInt(data.get(0)->getRawData()), // ID
            nullptr,                                  // Accommodation (will be set later)
            *data.get(1),                             // Guest name
            startDate,                                // Start date
            String::toInt(data.get(3)->getRawData()), // Days
            *data.get(4),                             // Payment method
            paymentDate,                              // Payment date
            String::toInt(data.get(6)->getRawData()), // Total price
            *data.get(7)                              // Annotations
        );

        allReservations.insertEnd(newReservation);
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
