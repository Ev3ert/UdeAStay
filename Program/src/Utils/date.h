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

    bool operator !=(const Date &other) const
    {
        return !(*this == other);
    }

    bool operator >(const Date &other) const
    {
        return !(*this < other || *this == other);
    }

    bool operator <=(const Date &other) const
    {
        return (*this < other || *this == other);
    }

    bool operator >=(const Date &other) const
    {
        return !(*this < other);
    }


    /// * Methods

    // Check if the date is valid
    bool isValid() const
    {
        if(year == 0 || month < 1 || month > 12 || day < 1)
            return false;

        int maxDays = getDaysInMonth(month, year);

        return day <= maxDays;
    }

    String getFormatDate() const
    {
        static const String days[] = 
            { "Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
        static const String months[] = 
            { "Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
              "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

        return days[getWeekDay()] + ", " +
                   String::toString(day) + " de " +
                   String(months[month - 1]) + " de " +
                   String::toString(year);

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

    // Funtion to add days to the date
    Date addDays(int days) const
    {
        int d = day;
        int m = month;
        int y = year;

        while(days > 0)
        {
            int maxDays = getDaysInMonth(m, y);

            int remainingDays = maxDays - d;

            if(days <= remainingDays)
            {
                d += days;
                break;
            }
            else
            {
                days -= (remainingDays + 1); // +1 to move to the next month
                d = 1; // Reset day to 1
                m++;
                if(m > 12)
                {
                    m = 1;
                    y++;
                }
            }
        }

        return Date(d, m, y);
    }


    // Funtion to get the number of days in the month
    int getDaysInMonth(int month, int year) const
    {
        static const int daysInMonth[] = 
            { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        int maxDays = daysInMonth[month - 1];

        // Check for leap year
        if (month == 2 && ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)))
            maxDays = 29;

        return maxDays;
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
