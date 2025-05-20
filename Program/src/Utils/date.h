#ifndef DATE_H
#define DATE_H

#include "../DataStructure/string.h"
#include <iostream>


class Date
{
private:
    unsigned int day;
    unsigned int month;
    unsigned int year;

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

    /// * Methods

    // Check if the date is valid
    bool isValid() const
    {
        if(year == 0 || month < 1 || month > 12 || day < 1)
            return false;

        // maximum days in a month
        static const int daysInMonth[] = 
            { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int maxDays = daysInMonth[month - 1];

        // Check for leap year
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
            maxDays = 29;

        return day <= maxDays;
    }


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

    int getDay() const
    {
        return day;
    }

    int getMonth() const
    {
        return month;
    }

    int getYear() const
    {
        return year;
    }

    // Funtion to get the day of the week (0 = Sunday, 1 = Monday, ..., 6 = Saturday)
    int getWeekDay() const
    {
        // i'dont know how this works, but it works

        int d = day;
        int m = month;
        int y = year;

        // Zeller's Congruence algorithm http://datagenetics.com/blog/november12019/index.html
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
