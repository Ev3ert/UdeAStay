#ifndef HOST_H
#define HOST_H

#include "../DataStructure/string.h"
#include "../DataStructure/list.h"
#include "../Utils/date.h"

class Reservation;
class Accommodation;

class Host
{
private:
    /// * Propierties

    String name;
    String document;
    int antiquity; // in months
    int puntuation; 
    Date cutOffDate;

    List<Accommodation*> accommodations;

public:
    /// * Constructor

    Host(const String& name, const String& document, int antiquity, int puntuation, const Date& cutOffDate);

    /// * Methods

    // add an accommodation to the list
    void addAccomodation(Accommodation *Accommodation);

    // remove an accomodation by their ID
    void removeAccomodation(unsigned int id);

    // cancel a reservation by their ID
    void cancelReservation(unsigned int id);

    // Prints all reservation from all accommodations
    void consultReservations(const Date& startRange = Date(1,1,2024), 
                             const Date& endRange = Date(31,12,10000), 
                             bool useDateFilter = false);

    // Update de historic archive
    void updateHistoric(Date cutOffDate, List<Reservation*>& globalReservations);

    const String& getDocument() const;
    const String& getName() const;
    int getAntiquity() const;
    int getPuntuation() const;
    const Date& getCutOffDate() const;
    List<Accommodation*> getAccommodations() const;

    // Setters
    void setAccommodations(const List<Accommodation*>& accommodations);

};


#endif // HOST_H
