#ifndef ACCOMODATION_H
#define ACCOMODATION_H

#include "../DataStructure/string.h"
#include "../DataStructure/list.h"

class Date;
class Host;
class Reservation;

class Accommodation
{
private:
    /// * Properties

    unsigned int id;
    String name;
    const Host* host; 
    String department;
    String type; // hotel, apartment, etc
    String address;
    unsigned long pricePerNight;
    List<String> amenities; 
    List<Reservation*> reservations;

public:
    /// * Constructors

    Accommodation(unsigned int id, const String& name, const Host* host, 
                const String& department, const String& type, 
                const String& address, unsigned long pricePerNight, 
                List<String>& amenities);
    
    /// * Methods
    
    // Check if the accommodation is available for the given date range
    bool isAvailable(const Date& startDate, int days) const;
    
    void viewDetails() const;

    // Getters
    unsigned int getId() const;
    const String& getName() const;
    const Host* getHost() const;
    const String& getDepartment() const;
    const String& getType() const;
    const String& getAddress() const;
    const List<String>& getAmenities() const;
    const List<Reservation*>& getReservations() const;

    // Setters
    void SetReservations(const List<Reservation*>& reservations);
    void SetReservation(Reservation* reservation);

};
#endif // ACCOMODATION_H
