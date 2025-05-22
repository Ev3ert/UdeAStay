#ifndef DATE_H
#define DATE_H

#include "../DataStructure/string.h"
#include <iostream>

class Date
{
private:
    int day;
    int month;
    int year;

public:

    /// * Constructors
    Date(int d, int m, int y) : day(d), month(m), year(y) {}

    /// * Operators
    bool operator<(const Date &other) const
    {
        if(year != other.year)
        {
            return year < other.year;
        }
        else if(month != other.month)
        {
            return month < other.month;
        }
        return day < other.day;
    }

    bool operator ==(const Date &other) const
    {
        return (day == other.day && month == other.month && year == other.year);
    }

    bool operator>(const Date &other) const
    {
        return !(*this < other || *this == other);
    }

    bool operator>=(const Date &other) const
    {
        return !(*this < other);
    }

    bool operator<=(const Date &other) const
    {
        return (*this < other || *this == other);
    }

    /// * Methods

    // Check if the date is valid
    bool isValid() const
    {
        if(year == 0 || month < 1 || month > 12 || day < 1)
            return false;


        int maxDays = getDaysInMonth(month, year);

        // Check for leap year
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
            maxDays = 29;

        return day <= maxDays;
    }

    // Print the date in a readable format
    void printDate() const
    {
        static const String days[] = 
            { "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
        static const String months[] = 
            { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
              "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};


        std::cout << (days[getWeekDay()] + ", " + String::toString(day) + " de " 
                    + months[month - 1] + " de " 
                    + String::toString(year)).getRawData();
    }

    // Funtion to get the day
    int getDay() const
    {
        return day;
    }

    // Funtion to get the month
    int getMonth() const
    {
        return month;
    }

    // Funtion to get the year
    int getYear() const
    {
        return year;
    }

    
    // Function to add days to this date returning a new date
    Date addDays(int days) const
    {
        
        int d = day;
        int m = month;
        int y = year;

        while(days > 0) {
            int maxDay = getDaysInMonth(m, y);

            int remaining = maxDay - d; // days left in the actual month

            if (days <= remaining) 
            {
                d += days;
                break;
            } 
            else 
            {
                days -= (remaining + 1); // +1 to move to the next month
                d = 1;
                m++;
                if (m > 12) {
                    m = 1;
                    y++;
                }
            }
        }

        return Date(d, m, y);
    }

    // Function to check if this date is in the interval [start, end]
    bool isInterval(const Date& start, const Date& end) const
    {
        if(start > end)
        {
            return false;
        }
        return (*this >= start && *this <= end);
    }

    // Function to get the number of days in a month
    int getDaysInMonth(int month, int year) const
    {
        static const int daysInMonth[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };

        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))) {
            return 29;
        }

        return daysInMonth[month - 1];
    }

    // Funtion to get the day of the week (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
    int getWeekDay() const
    {
        // i'dont know how this works, but it works
        
        int d = day;
        int m = month;
        int y = year;

        // Zeller's Congruence algorithm https://www.geeksforgeeks.org/zellers-congruence-find-day-date/
        if (m < 3) {
            m += 12;
            y -= 1;
        }


        int k = y % 100;
        int j = y / 100; 
        int h = (d + 13*(m + 1)/5 + k + k/4 + j/4 + 5*j) % 7;
        return (h + 6) % 7;
    }

};

#endif // DATE_H
