#include "fileSystem.h"
#include "../Actors/accommodation.h"
#include "../Actors/reservation.h"
#include "../Actors/host.h"
#include "../Actors/guest.h"
#include "../DataStructure/list.h"
#include "../DataStructure/string.h"
#include "../Utils/ConUtils.h"
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

}
