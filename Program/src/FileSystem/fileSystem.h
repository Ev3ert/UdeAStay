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


bool validateLineFields(const List<String>& data, unsigned int index, const String& fieldName);
Accommodation* findAccommodationById(const List<Accommodation*>& accommodations, int id);

String amenitiesListToString(const List<String>& amenities);
String dateToString(const Date& date);
String getHostAccommodationIds(const Host& host);


void loadAccomodations(List<Accommodation*>& allAccommodations);

void loadReservations(List<Reservation*>& allReservations,
     const List<Accommodation*>& allAccommodations, int &accomMaxID, int &resMaxID);

void loadHost(List<Host*>& allHosts, const List<Accommodation*>& accommodations);

void loadGuest(List<Guest*>& allGuests, const List<Reservation*>& allReservations);

void saveAccomodations(List<Accommodation*>& allAccommodations);
void saveReservations(List<Reservation*>& allReservations);
void saveHost(List<Host*>& allHosts);
void saveGuest(List<Guest*>& allGuests);
void saveAllData(const List<Accommodation*>& accommodations,
                 const List<Reservation*>& reservations,
                 const List<Host*>& hosts,
                 const List<Guest*>& guests);

void cleanupMemory(List<Accommodation*>& accommodations, 
                  List<Reservation*>& reservations,
                  List<Host*>& hosts, 
                  List<Guest*>& guests);





#endif // FILESYSTEM_H
