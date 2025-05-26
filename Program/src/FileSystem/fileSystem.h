#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "../DataStructure/list.h"
#include "../DataStructure/string.h"
#include "../Actors/accommodation.h"
#include "../Actors/reservation.h"
#include "../Actors/host.h"
#include "../Actors/guest.h"


const String archiveAccomodations = "/home/evert/Documents/Academico/Informatica_2/UdeAStay/Program/src/accommodations.txt";
const String archiveReservations = "/home/evert/Documents/Academico/Informatica_2/UdeAStay/Program/src/reservations.txt";
const String archiveHost = "/home/evert/Documents/Academico/Informatica_2/UdeAStay/Program/src/hosts.txt";
const String archiveGuest = "/home/evert/Documents/Academico/Informatica_2/UdeAStay/Program/src/guests.txt";


void loadAccomodations(List<Accommodation*>& allAccommodations);
void loadReservations(List<Reservation*>& allReservations);
void loadHost(List<Host*>& allHost);
void loadGuest(List<Guest*>& allGuest);

void saveAccomodations();
void saveReservations();
void saveHost();
void saveGuest();



#endif // FILESYSTEM_H
