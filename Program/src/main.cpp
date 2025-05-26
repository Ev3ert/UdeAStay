#include "DataStructure/list.h"
#include "DataStructure/string.h"
#include "Utils/ConUtils.h"
#include "Utils/date.h"
#include "Actors/accommodation.h"
#include "Actors/reservation.h"
#include "Actors/guest.h"
#include "Actors/host.h"
#include "FileSystem/fileSystem.h"



List<Accommodation*> accommodations;
List<Reservation*> reservations;
List<Host*> hosts;
List<Guest*> guests;



int main()
{

    loadAccomodations(accommodations);

    for(unsigned int i = 0; i < accommodations.size(); i++)
    {
        Accommodation *accommodation = *accommodations.get(i);
        accommodation->viewDetails();
    }
    

    return 0;

}
